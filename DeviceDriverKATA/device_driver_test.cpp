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
      .WillRepeatedly(Return(10));

  EXPECT_THROW({ driver.read(address); }, ReadFailException);
}
