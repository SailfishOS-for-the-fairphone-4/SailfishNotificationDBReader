/*
 * I2cDevice.cpp
 *
 * Created: 2023-11-15
 *
 * Author: Jordan Ramirez
 *
 * Description:
 * Implementation file for the I2cDevice class. This class provides an interface for interacting with
 * I2C devices on a Linux system. It includes a constructor for device initialization, a destructor
 * for cleanup, and methods for sending and receiving data over the I2C bus.
 */

#include <I2CDevice.h>

I2cDevice::I2cDevice(int adapter_number, int i2c_address)
        : i2c_adapter_number(adapter_number)
        , i2c_address(i2c_address) {

    filename = std::string("/dev/i2c-") + std::to_string(i2c_adapter_number);
    std::cout << "Filename: " << filename << std::endl;
    file = open(filename.c_str(), O_RDWR);

    if (file < 0) {
        std::cout << "File acces error: " << file << std::endl;
        exit(file);
    }

    int error_no = ioctl(file, I2C_SLAVE, i2c_address);
    if (error_no < 0) {
        /* ERROR HANDLING; you can check errno to see what went wrong */
        exit(error_no);
    }

    // Device is now initialezed, can only be done on creation of a device object.
}

I2cDevice::~I2cDevice() {
    close(file);
}

int I2cDevice::sentData(const int * data, std::size_t size) {
    /*
     * Using I2C Write, equivalent of
     * i2c_smbus_write_word_data(file, reg, 0x6543)
     */
    if (write(file, data, size) != size) {
        return -1;
    }

    return 0;
}

int I2cDevice::getData(int * data, std::size_t size) {
    /* Using I2C Read, equivalent of i2c_smbus_read_byte(file) */
    for (int i = 0; i < size; ++i) {
        if (write(file, data + i, 1) != 1) {
            std::cout << "Write error i2c" << std::endl;
            return -1;
        }
        std::cout << "Getting data in getData(): " << std::to_string(data[i]) << std::endl;
        if (read(file, data + i, 1) != 1) {
            /* ERROR HANDLING: i2c transaction failed */
            std::cout << "Read error i2c" << std::endl;
            return -2;
        }
    }
    return 0;
}