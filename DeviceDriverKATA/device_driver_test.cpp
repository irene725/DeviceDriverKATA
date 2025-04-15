#include "device_driver.h"

#include "flash_memory_device.h"
#include "gmock/gmock.h"

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
