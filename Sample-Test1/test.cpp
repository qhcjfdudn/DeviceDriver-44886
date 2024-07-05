#include "gmock/gmock.h"

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
	const int EMPTY_VALUE = 0xFF;
};

TEST_F(DeviceDriverFixture, read_장치는_반드시_5회_read_수행) {
	//arrage
	EXPECT_CALL(mk, read)
		.Times(5);

	//action
	d.read(0x00);

	//assert
	//PASS
}
TEST_F(DeviceDriverFixture, read_5회_모두_같은_값일_때_리턴) {
	//arrage

	EXPECT_CALL(mk, read)
		.WillRepeatedly(Return(DEFAULT_VALUE));

	//action
	int actual = d.read(0x00);

	//assert
	EXPECT_EQ(10, actual);
}
TEST_F(DeviceDriverFixture, read_5회_중_다른_값이_있을_때) {
	//arrage
	EXPECT_CALL(mk, read)
		.WillOnce(Return(DIFFERENT_VALUE_FROM_DEFAULT))
		.WillRepeatedly(Return(DEFAULT_VALUE));

	//action
	//assert
	EXPECT_THROW(d.read(0x00), std::exception);
}
TEST_F(DeviceDriverFixture, write_read_비어_있으면_쓰기_실행) {
	//arrage
	EXPECT_CALL(mk, read)
		.Times(1)
		.WillRepeatedly(Return(EMPTY_VALUE));

	EXPECT_CALL(mk, write)
		.Times(1);

	//action
	d.write(0x00, DEFAULT_VALUE);

	//assert
	// PASS
}
TEST_F(DeviceDriverFixture, write_read_비어_있지_않으면_exception) {
	//arrage
	EXPECT_CALL(mk, read)
		.WillRepeatedly(Return(DEFAULT_VALUE));

	EXPECT_CALL(mk, write)
		.Times(0);

	//action
	//assert
	EXPECT_THROW({
		d.write(0x00, DEFAULT_VALUE);
		}, std::exception);
}