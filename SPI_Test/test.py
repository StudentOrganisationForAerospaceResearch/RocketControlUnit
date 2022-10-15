import spidev
from time import sleep

spi = spidev.SpiDev()
spi.open(bus, device)

# Settings (for example)
spi.max_speed_hz = 5000
spi.mode = 0b01

to_send = [0x01, 0x02, 0x03]
spi.xfer(to_send)

writebytes(0x11)
readbytes(2)
