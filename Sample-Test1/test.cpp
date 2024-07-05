#include "gmock/gmock.h"

#include "../DAY10-DeviceDriver/DeviceDriver.cpp"
#include "../DAY10-DeviceDriver/FlashMemoryDevice.h"

using namespace testing;

class MockFlashMemory : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriver, 장치는_반드시_5회_read_수행) {
	MockFlashMemory mk;
	DeviceDriver d{ &mk };

	EXPECT_CALL(mk, read)
		.Times(5)
		.WillRepeatedly(Return(10));

	EXPECT_EQ(10, d.read(0x00));
}