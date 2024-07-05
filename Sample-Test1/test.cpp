﻿#include "gmock/gmock.h"

#include "../DAY10-DeviceDriver/DeviceDriver.cpp"
#include "../DAY10-DeviceDriver/FlashMemoryDevice.h"

using namespace testing;

class MockFlashMemory : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class DeviceDriverFixture :public testing::Test {
public:
	MockFlashMemory mk;
	DeviceDriver d{ &mk };

	const int DEFAULT_VALUE = 10;
	const int DIFFERENT_VALUE_FROM_DEFAULT = DEFAULT_VALUE + 1;
};

TEST_F(DeviceDriverFixture, 장치는_반드시_5회_read_수행) {
	//arrage
	EXPECT_CALL(mk, read)
		.Times(5);

	//action
	d.read(0x00);

	//assert
}
TEST_F(DeviceDriverFixture, 5회_모두_같은_값일_때_리턴) {
	//arrage

	EXPECT_CALL(mk, read)
		.WillRepeatedly(Return(DEFAULT_VALUE));

	//action
	int actual = d.read(0x00);

	//assert
	EXPECT_EQ(10, actual);
}
TEST_F(DeviceDriverFixture, 다른_값이_있을_때) {
	//arrage
	EXPECT_CALL(mk, read)
		.WillOnce(Return(DIFFERENT_VALUE_FROM_DEFAULT))
		.WillRepeatedly(Return(DEFAULT_VALUE));

	//action
	//assert
	EXPECT_THROW(d.read(0x00), std::runtime_error);
}