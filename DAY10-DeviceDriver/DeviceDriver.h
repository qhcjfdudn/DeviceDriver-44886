#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;

private:
    int readFromDevice(long address);
    void throwWhenSomeReadValueDifferent(int  values[5]);
    void readFromDevice5Times(int values[5], long address);
};