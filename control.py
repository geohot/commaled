import usb1
import time
import random

# open the device
context = usb1.USBContext()
handle = context.openByVendorIDAndProductID(0x1337, 0x1337)
print handle

inten = [0]*6
while 1:
  inten = [random.randint(0, 255) for x in range(6)]
  handle.bulkWrite(1, ''.join(map(chr, inten)))
  time.sleep(0.2)

