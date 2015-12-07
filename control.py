import usb1
import time
import random

# open the device
context = usb1.USBContext()
handle = context.openByVendorIDAndProductID(0x1337, 0x1337)
print handle

cnt = 0
while 1:
  inten = [0]*6
  inten[cnt >> 8] = cnt&0xFF
  inten[((cnt >> 8)+1)%3 + 3] = cnt&0xFF

  handle.bulkWrite(1, ''.join(map(chr, inten)))
  time.sleep(0.01)
  cnt += 4
  if cnt >= 0x300:
    cnt = 0

