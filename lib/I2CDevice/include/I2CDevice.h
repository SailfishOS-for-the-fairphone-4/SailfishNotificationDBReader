/*
 * I2cDevice.h
 *
 * Created: 2023-11-15
 *
 * Author: Jordan Ramirez
 */

#ifndef __I2CDEVICE_H__
#define __I2CDEVICE_H__

#include <fcntl.h>
#include <i2c/smbus.h>
#include <iostream>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

#include <vector>

#include <cstdint>

#include <array>
#include <string>
#include <unistd.h> //Posix syscalls

struct I2CRegister
{
public:
    explicit I2CRegister(uint8_t registerToRead)
    : _registerToRead(registerToRead)
    { }

    uint8_t &GetResult()
    {
        return _result;
    }

    const uint8_t& GetRegisterToRead() const
    {
        return _registerToRead;
    }

private:
    uint8_t _registerToRead;
    uint8_t _result{};
};

class I2CDevice {
private:
    int i2c_adapter_number;
    int i2c_address;

    int file;
    std::string filename;

public:
    /**
     * @brief Constructor for the I2cDevice class.
     *
     * This constructor initializes an object of the I2cDevice class with the specified I2C adapter number and device address.
     * It opens the corresponding I2C device file, sets the I2C address, and prepares the device for communication.
     *
     * @param adapter_number The I2C adapter number to which the device is connected.
     * @param i2c_address The I2C address of the device.
     *
     * @note The constructor automatically sets up the I2C device by opening the corresponding file,
     * setting the I2C address using ioctl, and printing diagnostic information.
     *
     * @see I2cDevice
     */
    I2CDevice(int adapter_number, int i2c_address);

    /**
     * @brief Destructor for the I2cDevice class.
     *
     * This destructor closes the file associated with the I2C device when an object of the I2cDevice class is destroyed.
     *
     * @note The destructor ensures that the I2C device file is properly closed, releasing system resources.
     *
     * @see I2cDevice
     */
    ~I2CDevice();

    /**
     * @brief Reads data from the I2C device.
     *
     * This function reads data from the I2C device using a series of I2C write and read operations.
     *
     * @param registers Vector of registers to read.
     *
     * @return 0 on success, -1 on write error, -2 on read error.
     *
     * @note The function performs a sequence of I2C write and read operations to fetch the specified amount of data.
     * If any of these operations fail, an error code is returned. The error codes are as follows:
     * - 0: Operation completed successfully.
     * - -1: Write error occurred during the I2C write operation.
     * - -2: Read error occurred during the I2C read operation.
     *
     * @warning It is important to handle errors appropriately based on the returned error code.
     *
     * @see I2cDevice
     */
    int GetData(std::vector<I2CRegister>& registers);

    /**
     * @brief Sends data to the I2C device.
     *
     * This function sends data to the I2C device using a single I2C write operation.
     *
     * @param data Vector of data to send.
     *
     * @return 0 on success, -1 on write error.
     *
     * @note The function performs a single I2C write operation to send the specified data to the device.
     * If the write operation fails, an error code is returned. The error codes are as follows:
     * - 0: Operation completed successfully.
     * - -1: Write error occurred during the I2C write operation.
     *
     * @warning It is important to handle errors appropriately based on the returned error code.
     *
     * @see I2cDevice
     */
    int SendData(const std::vector<uint8_t>& data);
}; // I2cDevice

#endif //__I2CDEVICE_H__