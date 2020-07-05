from time import sleep

import serial

ser = serial.Serial(
    port='/dev/tty.usbserial-14430',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=0
)

print("Connected to: " + ser.portstr + "\n")

try:

    while True:
        #print(bytes([0x2a]))
        #ser.write(bytes([0x2a]))
        sleep(0.05)
        r = ser.readline()
        if len(r) > 0:
            print(r)
except KeyboardInterrupt:
    ser.close()
    print("\nExit\n");
