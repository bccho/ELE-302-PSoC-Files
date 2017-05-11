/***************************************************************************
  This is a library for the LSM9DS0 Accelerometer and magnentometer/compass

  Designed specifically to work with the Adafruit LSM9DS0 Breakouts

  These sensors use I2C to communicate, 2 pins are required to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Kevin Townsend for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/
#include <accel.h>
#include <device.h>
#include <stdio.h>

/*-----------------------------------------------------------------*/

//static void setupAccel(lsm9ds0AccelRange_t range);
//static void setupGyro(lsm9ds0GyroScale_t scale);
void readAccel(double *accelData);
void readGyro(double *gyroData);
static void write8(int type, uint8_t reg, uint8_t value);
static uint8_t read8(int type, uint8_t reg);
static uint8_t readBuffer(int type, uint8_t reg, uint8_t len, uint8_t *buffer);

/*-----------------------------------------------------------------*/

static char strbuffer[100];

static double accelMgLsb;
static double gyroDpsDigit;

#define AVG_BUF_LEN 10
static int zeroed = 0;
static int bufPos = 0;
static double accelValsBuf[AVG_BUF_LEN][3];
static double gyroValsBuf[AVG_BUF_LEN][3];
static double accelOffset[3];
static double gyroOffset[3];
static double accelValAvg[3];
static double gyroValAvg[3];
static const int NUM_ZERO_READINGS = 10;

/*-----------------------------------------------------------------*/



/***************************************************************************
 PUBLIC FUNCTIONS
 ***************************************************************************/
 

int Accel_init() {
    uint8_t id = read8(XMTYPE, LSM9DS0_REGISTER_WHO_AM_I_XM);
//    sprintf(strbuffer, "XM whoami: 0x%2x\n", id);
//    UART_PutString(strbuffer);
    if (id != LSM9DS0_XM_ID) return 0;

    id = read8(GYROTYPE, LSM9DS0_REGISTER_WHO_AM_I_G);
//    sprintf(strbuffer, "G whoami: 0x%2x\n", id);
//    UART_PutString(strbuffer);
    if (id != LSM9DS0_G_ID) return 0;

	// Accelerometer Settings
//    // Enable FIFO
//	write8(XMTYPE, LSM9DS0_REGISTER_CTRL_REG0_XM, 0x40);
    // 1600Hz, enable XYZ
	write8(XMTYPE, LSM9DS0_REGISTER_CTRL_REG1_XM, 0xA7);
    // 773Hz anti-alias filter, +-2g range
	write8(XMTYPE, LSM9DS0_REGISTER_CTRL_REG2_XM, 0x00);
//    // 50Hz anti-alias filter, +-2g range
//	write8(XMTYPE, LSM9DS0_REGISTER_CTRL_REG2_XM, 0xC0);
//    // Enable filters
//	write8(XMTYPE, LSM9DS0_REGISTER_CTRL_REG7_XM, 0x20);
//    // Enable FIFO stream mode
//	write8(XMTYPE, LSM9DS0_REGISTER_FIFO_CTRL_REG, 0x40);
    
    accelMgLsb = LSM9DS0_ACCEL_MG_LSB_2G;
	
    
    // Gyro Settings
    // 760Hz, 30 cutoff, enable XYZ
	write8(GYROTYPE, LSM9DS0_REGISTER_CTRL_REG1_G, 0xCF);
    // Set high pass filter for 7.2Hz
    write8(GYROTYPE, LSM9DS0_REGISTER_CTRL_REG2_G, 0x00);
    // Set scale to +-245dps, self-test off, little endian data
    write8(GYROTYPE, LSM9DS0_REGISTER_CTRL_REG4_G, 0x00);
//    // Enable FIFO and high-pass filter
//    write8(GYROTYPE, LSM9DS0_REGISTER_CTRL_REG5_G, 0x52);
//    // Enable stream mode for FIFO
//    write8(GYROTYPE, LSM9DS0_REGISTER_FIFO_CTRL_REG_G, 0x40);
    
    gyroDpsDigit = LSM9DS0_GYRO_DPS_DIGIT_245DPS;
//
//	/*
//	for (uint8_t i=0; i<0x30; i++) {
//		Serial.print("$"); Serial.print(i, HEX);
//		Serial.print(" = 0x"); 
//		Serial.println(read8(XMTYPE, i), HEX);
//	}
//	*/
//
	// Set default ranges for the various sensors  
//	setupAccel(LSM9DS0_ACCELRANGE_2G);
//	setupGyro(LSM9DS0_GYROSCALE_245DPS);

    return 1;
}

void Accel_refresh() {
    readAccel(accelValsBuf[bufPos]);
    readGyro(gyroValsBuf[bufPos]);
    bufPos = (bufPos + 1) % AVG_BUF_LEN;
    if (zeroed != 1 && bufPos == 0) {
        static int count;
        count++;
        int i, j;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < AVG_BUF_LEN; j++) {
                accelOffset[i] += accelValsBuf[j][i];
                gyroOffset[i] += gyroValsBuf[j][i];
            }
            if (count >= NUM_ZERO_READINGS) {
                accelOffset[i] /= (AVG_BUF_LEN * NUM_ZERO_READINGS);
                gyroOffset[i] /= (AVG_BUF_LEN * NUM_ZERO_READINGS);
                zeroed = 1;
                if (i == 2) {
                    sprintf(strbuffer, "Offsets: %8.3f, %8.3f, %8.3f, %8.3f, %8.3f, %8.3f\n", 
                            accelOffset[0], accelOffset[1], accelOffset[2], 
                            gyroOffset[0], gyroOffset[1], gyroOffset[2]);
                    UART_PutString(strbuffer);
                }
            }
        }
    }
    else if (zeroed == 1) {
        int i, j;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < AVG_BUF_LEN; j++) {
                accelValAvg[i] += accelValsBuf[j][i];
                gyroValAvg[i] += gyroValsBuf[j][i];
            }
            accelValAvg[i] /= AVG_BUF_LEN;
            gyroValAvg[i] /= AVG_BUF_LEN;
            accelValAvg[i] -= accelOffset[i];
            gyroValAvg[i] -= gyroOffset[i];
        }
//        sprintf(strbuffer, "%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f\n", 
//                accelValAvg[0], accelValAvg[1], accelValAvg[2], 
//                gyroValAvg[0], gyroValAvg[1], gyroValAvg[2]);
        sprintf(strbuffer, "%2.1f,%2.1f,%2.1f\n", 
                accelValAvg[0], accelValAvg[1], accelValAvg[2]);
        UART_PutString(strbuffer);
    }
}    

void Accel_getAccel(double *accelData) {
    accelData[0] = accelValAvg[0];
    accelData[1] = accelValAvg[1];
    accelData[2] = accelValAvg[2];
}
    
    
void Accel_getGyro(double *gyroData) {
    gyroData[0] = gyroValAvg[0];
    gyroData[1] = gyroValAvg[1];
    gyroData[2] = gyroValAvg[2];
}




/***************************************************************************
 PRIVATE FUNCTIONS
 ***************************************************************************/

void readAccel(double *accelData) {
	// Read the accelerometer
	uint8_t buffer[6];
	readBuffer(XMTYPE, 
        I2C_AUTO_INCREMENT | LSM9DS0_REGISTER_OUT_X_L_A, 
		6, buffer);

	uint8_t xlo = buffer[0];
	int16_t xhi = buffer[1];
	uint8_t ylo = buffer[2];
	int16_t yhi = buffer[3];
	uint8_t zlo = buffer[4];
	int16_t zhi = buffer[5];

	// Shift values to create properly formed integer (low byte first)
	xhi <<= 8; xhi |= xlo;
	yhi <<= 8; yhi |= ylo;
	zhi <<= 8; zhi |= zlo;
	
    accelData[0] = xhi * accelMgLsb;
    accelData[1] = yhi * accelMgLsb;
    accelData[2] = zhi * accelMgLsb;
}

void readGyro(double *gyroData) {
	// Read gyro
	uint8_t buffer[6];
	readBuffer(GYROTYPE, 
		I2C_AUTO_INCREMENT | LSM9DS0_REGISTER_OUT_X_L_G, 
		6, buffer);

	uint8_t xlo = buffer[0];
	int16_t xhi = buffer[1];
	uint8_t ylo = buffer[2];
	int16_t yhi = buffer[3];
	uint8_t zlo = buffer[4];
	int16_t zhi = buffer[5];

	// Shift values to create properly formed integer (low byte first)
	xhi <<= 8; xhi |= xlo;
	yhi <<= 8; yhi |= ylo;
	zhi <<= 8; zhi |= zlo;

	gyroData[0] = xhi * gyroDpsDigit;
	gyroData[1] = yhi * gyroDpsDigit;
	gyroData[2] = zhi * gyroDpsDigit;
}

//static void setupAccel(lsm9ds0AccelRange_t range) {
//	uint8_t reg = read8(XMTYPE, LSM9DS0_REGISTER_CTRL_REG2_XM);
//	reg &= ~(0b00111000);
//	reg |= range;
//	write8(XMTYPE, LSM9DS0_REGISTER_CTRL_REG2_XM, reg);
//
//	switch (range){
//    	case LSM9DS0_ACCELRANGE_2G:
//    		accelMgLsb = LSM9DS0_ACCEL_MG_LSB_2G;
//    		break;
//    	case LSM9DS0_ACCELRANGE_4G:
//    		accelMgLsb = LSM9DS0_ACCEL_MG_LSB_4G;
//    		break;
//    	case LSM9DS0_ACCELRANGE_6G:
//    		accelMgLsb = LSM9DS0_ACCEL_MG_LSB_6G;
//    		break;
//    	case LSM9DS0_ACCELRANGE_8G:
//    		accelMgLsb = LSM9DS0_ACCEL_MG_LSB_8G;
//    		break;    
//    	case LSM9DS0_ACCELRANGE_16G:
//    		accelMgLsb =LSM9DS0_ACCEL_MG_LSB_16G;
//    		break;
//	}
//}
//
//
//static void setupGyro(lsm9ds0GyroScale_t scale) {
//	uint8_t reg = read8(GYROTYPE, LSM9DS0_REGISTER_CTRL_REG4_G);
//	reg &= ~(0b00110000);
//	reg |= scale;
//	write8(GYROTYPE, LSM9DS0_REGISTER_CTRL_REG4_G, reg);
//
//	switch(scale){
//    	case LSM9DS0_GYROSCALE_245DPS:
//    		gyroDpsDigit = LSM9DS0_GYRO_DPS_DIGIT_245DPS;
//    		break;
//    	case LSM9DS0_GYROSCALE_500DPS:
//    		gyroDpsDigit = LSM9DS0_GYRO_DPS_DIGIT_500DPS;
//    		break;
//    	case LSM9DS0_GYROSCALE_2000DPS:
//    		gyroDpsDigit = LSM9DS0_GYRO_DPS_DIGIT_2000DPS;
//    		break;
//	}
//}


static void write8(int type, uint8_t reg, uint8_t value) {
    uint8_t address;

    if (type == GYROTYPE) {
        address = LSM9DS0_ADDRESS_GYRO;
    } else {
        address = LSM9DS0_ADDRESS_ACCELMAG;
    }
    I2C_MasterSendStart(address, I2C_WRITE);
    I2C_MasterWriteByte(reg);
    I2C_MasterWriteByte(value);
    I2C_MasterSendStop();
}

static uint8_t read8(int type, uint8_t reg) {
    uint8_t value;

    readBuffer(type, reg, 1, &value);

    return value;
}

static uint8_t readBuffer(int type, uint8_t reg, uint8_t len, uint8_t *buffer) {
    uint8_t address;

    if (type == GYROTYPE) {
        address = LSM9DS0_ADDRESS_GYRO;
    } else {
        address = LSM9DS0_ADDRESS_ACCELMAG;
    }
    
    I2C_MasterSendStart(address, I2C_WRITE);
    I2C_MasterWriteByte(reg);
    
    I2C_MasterSendRestart(address, I2C_READ);
    int i;
    for (i = 0; i < len-1; i++) {
        buffer[i] = I2C_MasterReadByte(I2C_SEND_ACK);
    }
    buffer[len-1] = I2C_MasterReadByte(I2C_SEND_NACK);
    I2C_MasterSendStop();

    return len;
}