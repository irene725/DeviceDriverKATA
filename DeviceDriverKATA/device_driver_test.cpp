#include "device_driver.h"

#include "flash_memory_device.h"
#include "gmock/gmock.h"
using namespace testing;
class FlashMemoryDeviceMock : public FlashMemoryDevice {
 public:
  MOCK_METHOD(unsigned char, read, (long), (override));
  MOCK_METHOD(void, write, (long, unsigned char), (override));
};

class DeviceDriverTestFixture : public Test {
 public:
  FlashMemoryDeviceMock deviceMock;
  DeviceDriver driver;
  long address = 0x4;
  unsigned char data = 10;
  DeviceDriverTestFixture() : driver(&deviceMock) {}
};

TEST_F(DeviceDriverTestFixture, ReadIsCalledFiveTimes) {
  EXPECT_CALL(deviceMock, read).Times(5);

  driver.read(address);
}

TEST_F(DeviceDriverTestFixture,
       ThrowsExceptionIfReadReturnsDifferentValuesInFiveCalls) {
  EXPECT_CALL(deviceMock, read(address))
      .WillOnce(Return(5))
      .WillRepeatedly(Return(data));

  EXPECT_THROW({ driver.read(address); }, ReadFailException);
}

TEST_F(DeviceDriverTestFixture, CheckRead) {
  EXPECT_CALL(deviceMock, read(address)).WillRepeatedly(Return(data));

  EXPECT_EQ(driver.read(address), data);
}

TEST_F(DeviceDriverTestFixture, ThrowsExceptionIfWriteIsImpossible) {
  EXPECT_CALL(deviceMock, read(address)).WillRepeatedly(Return(0x5));
  EXPECT_THROW({ driver.write(address, data); }, WriteFailException);
}
TEST_F(DeviceDriverTestFixture, CheckWriteIsPossible) {
  unsigned char data = 1;
  EXPECT_CALL(deviceMock, read(address)).WillRepeatedly(Return(0xFF));
  EXPECT_CALL(deviceMock, write(address, data)).Times(1);

  driver.write(address, data);
}