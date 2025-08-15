/*
 * GAGHL_AVR_I2C.h
 *
 * Created: 8/15/2025 5:21:56 PM
 *  Author: GAGHL
 */ 

/*
 * Description:
 * This library provides functions for I2C (TWI) communication on AVR microcontrollers.
 * It supports master mode initialization, byte-level and page-level read/write operations,
 * and allows setting the MCU's own slave address.
 *
 * All timings are based on F_CPU (CPU clock) and the frequency provided to i2c_init() in kHz.
 */


#ifndef GAGHL_AVR_I2C_H_
#define GAGHL_AVR_I2C_H_

#include <avr/io.h>

/**
 * @brief Initializes the I2C (TWI) peripheral of the AVR microcontroller.
 *
 * This function sets the bit rate register and prescaler for the desired I2C clock frequency.
 *
 * @param freq Desired I2C clock frequency in kilohertz (kHz).
 *
 * Example usage:
 * @code
 * i2c_init(100); // Initialize I2C at 100 kHz
 * @endcode
 */
void i2c_init(uint16_t freq);

/**
 * @brief Sends a START condition on the I2C bus.
 *
 * This function generates a START condition to initiate communication with a slave device.
 *
 * Example usage:
 * @code
 * i2c_start();
 * @endcode
 */
void i2c_start(void);

/**
 * @brief Sends a STOP condition on the I2C bus.
 *
 * This function ends the I2C communication by generating a STOP condition.
 *
 * Example usage:
 * @code
 * i2c_stop();
 * @endcode
 */
void i2c_stop(void);

/**
 * @brief Writes a single byte to the I2C bus.
 *
 * @param Data The byte to transmit.
 * @return uint8_t Returns 1 if the transmission was acknowledged, 0 if there was an error.
 *
 * Example usage:
 * @code
 * if (i2c_write(0x55)) { ... } // check for ACK
 * @endcode
 */
uint8_t i2c_write(uint8_t Data);

/**
 * @brief Reads a byte from the I2C bus and sends an ACK.
 *
 * @return uint8_t The received byte.
 *
 * Example usage:
 * @code
 * uint8_t data = i2c_read_ack();
 * @endcode
 */
uint8_t i2c_read_ack(void);

/**
 * @brief Reads a byte from the I2C bus without sending an ACK.
 *
 * @return uint8_t The received byte.
 *
 * Example usage:
 * @code
 * uint8_t last_byte = i2c_read_no_ack();
 * @endcode
 */
uint8_t i2c_read_no_ack(void);

/**
 * @brief Sets the microcontroller's own I2C address.
 *
 * @param Address The 7-bit address to assign to this MCU as a slave.
 *
 * Example usage:
 * @code
 * i2c_set_MCU_address(0x42);
 * @endcode
 */
void i2c_set_MCU_address(uint8_t Address);


/**
 * @brief Writes a single byte to a specific slave device.
 *
 * @param Slave_Address 7-bit address of the target slave device.
 * @param Data The byte to send.
 *
 * Example usage:
 * @code
 * i2c_writeByte(0x10, 0xAA);
 * @endcode
 */
void i2c_writeByte(uint8_t Slave_Address, uint8_t Data);


/**
 * @brief Reads a single byte from a specific slave device.
 *
 * @param Slave_Address 7-bit address of the target slave device.
 * @return uint8_t The byte read from the slave.
 *
 * Example usage:
 * @code
 * uint8_t data = i2c_readByte(0x10);
 * @endcode
 */
uint8_t i2c_readByte(uint8_t Slave_Address);


/**
 * @brief Writes a string or buffer of bytes to a slave device (page write).
 *
 * @param Slave_Address 7-bit address of the target slave device.
 * @param str Pointer to the string or buffer to transmit. Must be null-terminated if sending a string.
 * @return uint8_t Returns 1 if all bytes were successfully written, 0 if any transmission failed.
 *
 * Example usage:
 * @code
 * char message[] = "Hello";
 * i2c_pagewrite(0x10, message);
 * @endcode
 */
uint8_t i2c_pagewrite(uint8_t Slave_Address, char* str);

/**
 * @brief Reads multiple bytes from a slave device (page read).
 *
 * @param Slave_Address 7-bit address of the target slave device.
 * @param buffer Pointer to the buffer where received data will be stored.
 * @param length Number of bytes to read.
 *
 * Note: If reading textual data, the last byte is automatically set to '\0' to terminate the string.
 *
 * Example usage:
 * @code
 * char buffer[10];
 * i2c_pageread(0x10, buffer, 5);
 * @endcode
 */
void i2c_pageread(uint8_t Slave_Address, char* buffer, uint8_t length);

#endif /* GAGHL_AVR_I2C_H_ */