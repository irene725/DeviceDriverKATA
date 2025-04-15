#include "device_driver.h"

#include "flash_memory_device.h"
#include "gmock/gmock.h"
using namespace testing;
class FlashMemoryDeviceMock : public FlashMemoryDevice {
 public:
  MOCK_METHOD(unsigned char, read, (long), (override));
  MOCK_METHOD(void, write, (long, unsigned char), (override));
};

TEST(DeviceDriverTest, ReadIsCalledFiveTimes) {
  FlashMemoryDeviceMock deviceMock;
  EXPECT_CALL(deviceMock, read).Times(5);

  DeviceDriver driver(&deviceMock);
  long address = 0x4;
  driver.read(address);
}

TEST(DeviceDriverTest, ThrowsExceptionIfReadReturnsDifferentValuesInFiveCalls) {
  FlashMemoryDeviceMock deviceMock;
  DeviceDriver driver(&deviceMock);
  long address = 0x4;
  EXPECT_CALL(deviceMock, read(address))
      .WillOnce(Return(5))
      .WillRepeatedly(Return(10));

  EXPECT_THROW({ driver.read(address); }, ReadFailException);
}
