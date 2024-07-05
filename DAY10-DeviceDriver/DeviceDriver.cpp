#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int values[] = {-1, -1, -1, -1, -1};
    for (int i = 0; i < 5; ++i)
        values[i] = (int)(m_hardware->read(address));

    return values[0];
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}