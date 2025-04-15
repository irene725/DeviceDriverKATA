#include "device_driver.h"
#include "exception"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware)
    : m_hardware(hardware) {}

int DeviceDriver::read(long address) {
  // TODO: implement this method properly
  int result = (m_hardware->read(address));
  for (int i = 0; i < 4; i++) {
    int temp = (m_hardware->read(address));
    if (temp != result) throw ReadFailException();
  }
  return result;
}

void DeviceDriver::write(long address, int data) {
  // TODO: implement this method
  if (read(address) != 0xFF) throw WriteFailException();
  m_hardware->write(address, (unsigned char)data);
}