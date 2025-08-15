/*
 * GAGHL_AVR_I2C.c
 *
 * Created: 8/15/2025 5:21:50 PM
 *  Author: GAGHL
 */ 

#define F_CPU 8000000UL

#include "GAGHL_AVR_I2C.h"


void i2c_init(uint16_t freq){
	// Prescaler set for 1
	TWSR = 0x00;
	
	TWBR = ((F_CPU / (freq * 1000)) - 16) / 2;
	 // Enable I2C
	TWCR = (1 << TWEN);
}


//		___
// SDA:    \_____
//		______
// SCL:		  \__
void i2c_start(){
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
}


//			  ___
// SDA:	_____/	
//			_____
// SCL: ___/
void i2c_stop(){
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

uint8_t i2c_write(uint8_t Data){
	TWDR = Data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	
	uint8_t status = TWSR & 0xF8;
	//0x18: Master Transmit - SLA+W transmitted, ACK received
	//0x28: Master Transmit - Data transmitted, ACK received
	//0x40: Master Receive  - SLA+R transmitted, ACK received
	//0x50: Master Receive  - Data received, ACK returned
	if (status != 0x18 && status != 0x28 && status != 0x40 && status != 0x50) return 0;
	return 1;
}

uint8_t i2c_read_ack() {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

uint8_t i2c_read_no_ack() {
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

void i2c_set_MCU_address(uint8_t Address) {
	TWAR = (Address << 1);
	TWCR = (1 << TWEN) | (1 << TWEA); // Enable + ACK
}


void i2c_writeByte(uint8_t Slave_Address, uint8_t Data) {
	i2c_start();
	i2c_write(Slave_Address << 1);
	i2c_write(Data);
	i2c_stop();
}

uint8_t i2c_readByte(uint8_t Slave_Address) {
	
	uint8_t data;
	
	i2c_start();
	i2c_write((Slave_Address << 1) | 1);
	data = i2c_read_no_ack();
	i2c_stop();
	
	return data;
}

uint8_t i2c_pagewrite(uint8_t Slave_Address, char* str) {
	i2c_start();
	i2c_write(Slave_Address << 1);
	
	while(*str != '\0'){
		if (!i2c_write(*str)) return 0;
		str++;
	}
	
	i2c_stop();
	return 1;
}

void i2c_pageread(uint8_t Slave_Address, char* buffer, uint8_t length) {
	i2c_start();
	i2c_write((Slave_Address << 1) | 1);
	
	for(uint8_t i = 0; i < length; i++) {
		if(i == length - 1) {
			buffer[i] = i2c_read_no_ack();
		} else {
			buffer[i] = i2c_read_ack();
		}
	}
	
	if(length > 0) {
		buffer[length - 1] = '\0';
	}
	
	i2c_stop();
}