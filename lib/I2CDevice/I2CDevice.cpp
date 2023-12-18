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

I2CDevice::I2CDevice(int adapter_number, int i2c_address)
        : i2c_adapter_number(adapter_number)
        , i2c_address(i2c_address)
{

    filename = std::string("/dev/i2c-") + std::to_string(i2c_adapter_number);
    file = open(filename.c_str(), O_RDWR);

    if (file < 0)
        throw std::runtime_error("File access error: " + std::to_string(file));

    int error_no = ioctl(file, I2C_SLAVE, i2c_address);
    if (error_no < 0) /* ERROR HANDLING; you can check errno to see what went wrong */
        throw std::runtime_error("IOCTL Error: " + std::to_string(error_no));

    // Device is now initialezed, can only be done on creation of a device object.
}

I2CDevice::~I2CDevice()
{
    close(file);
}

int I2CDevice::SendData(const std::vector<uint8_t>& data)
{
    uint16_t payloadSize = data.size();
    std::vector<uint8_t> dataToSend;

    for (size_t i = 0; i < sizeof(payloadSize); i++)
        dataToSend.emplace_back(((uint8_t*)&payloadSize)[i]);

    dataToSend.insert(dataToSend.end(), data.begin(),data.end());

    i2c_msg message {
        .addr = (__u16)i2c_address,
        .flags = I2C_M_STOP,
        .len = (__u16)dataToSend.size(),
        .buf = (__u8*)dataToSend.data()
    };

    i2c_rdwr_ioctl_data transaction{
        .msgs = &message,
        .nmsgs = 1
    };

    if (ioctl(file, I2C_RDWR, &transaction) < 0)
        throw std::runtime_error("Failed to write data to I2C device");

    return 0;
}

int I2CDevice::GetData(std::vector<I2CRegister>& registers)
{
    /* Using I2C Read, equivalent of i2c_smbus_read_byte(file) */
    for (auto& reg : registers)
    {
        if (write(file, &reg.GetRegisterToRead(), 1) != 1)
            return -1;

        if (read(file, &reg.GetResult(), 1) != 1) /* ERROR HANDLING: i2c transaction failed */
            return -2;
    }

    return 0;
}