#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int result = readDevice5Times(address);

    return result;
}

int DeviceDriver::readDevice5Times(long address)
{
    int values[] = {-1, -1, -1, -1, -1};
    for (int i = 0; i < 5; ++i)
        values[i] = (int)(m_hardware->read(address));

    for (int i = 0; i < 5 - 1; ++i) {
        if (values[i] != values[i + 1]) {
            // exception
        }
    }

    return values[0];
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}