#include "gmock/gmock.h"

#include "../DAY10-DeviceDriver/DeviceDriver.cpp"
#include "../DAY10-DeviceDriver/FlashMemoryDevice.h"

using namespace testing;

class MockFlashMemory : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriver, ��ġ��_�ݵ��_5ȸ_read_����) {
	MockFlashMemory mk;
	DeviceDriver d{ &mk };

	EXPECT_CALL(mk, read)
		.Times(5)
		.WillRepeatedly(Return(10));

	EXPECT_EQ(10, d.read(0x00));
}