#include <iostream>

#include "DeviceDriver.h"

using std::cout;
using std::endl;

class ReadFailException : public std::exception {};

class WriteFailException : public std::exception {

};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
	// TODO: implement this method properly
	int result = readFromDevice(address);

	return result;
}

int DeviceDriver::readFromDevice(long address)
{
	int readValues[] = { -1, -1, -1, -1, -1 };
	readFromDevice5Times(readValues, address);

	throwWhenSomeReadValueDifferent(readValues);

	return readValues[0];
}
void DeviceDriver::readFromDevice5Times(int readValues[5], long address) {
	for (int i = 0; i < 5; ++i)
		readValues[i] = (int)(m_hardware->read(address));
}
void DeviceDriver::throwWhenSomeReadValueDifferent(int readValues[5])
{
	for (int i = 0; i < 5 - 1; ++i)
		if (readValues[i] != readValues[i + 1])
			throw ReadFailException();
}

void DeviceDriver::write(long address, int data)
{
	int readValue = (int)(m_hardware->read(address));

	if (readValue != READ_EMPTY_VALUE)
		throw WriteFailException();

	m_hardware->write(address, (unsigned char)data);
}