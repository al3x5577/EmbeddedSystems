from time import sleep

import serial

ser = serial.Serial(
    port='/dev/tty.usbserial-14230',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=0
)

print("Connected to: " + ser.portstr + "\n")


def read():
    r = ser.readline()
    if len(r) > 0:
        print(r)


try:

    while True:

        ser.write(bytes('11'.encode('UTF-8')))
        sleep(0.5)
        read()

        ser.write(bytes('21'.encode('UTF-8')))
        sleep(0.5)
        read()

        ser.write(bytes('31'.encode('UTF-8')))
        sleep(0.5)
        read()

        ser.write(bytes('41'.encode('UTF-8')))
        sleep(0.5)
        read()

        ser.write(bytes('10'.encode('UTF-8')))
        sleep(0.5)
        read()

        ser.write(bytes('20'.encode('UTF-8')))
        sleep(0.5)
        read()

        ser.write(bytes('30'.encode('UTF-8')))
        sleep(0.5)
        read()

        ser.write(bytes('40'.encode('UTF-8')))
        sleep(0.5)
        read()


except KeyboardInterrupt:
    ser.close()
    print("\nExit\n");
