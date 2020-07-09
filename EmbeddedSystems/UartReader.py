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
    r = ser.readlines()
    if len(r) > 0:
        for line in r:
            if line.startswith(bytes('Poti'.encode('UTF-8'))):
                print(line)


time = 0.7

try:

    while False:

        ser.write(bytes('11'.encode('UTF-8')))
        sleep(time)
        read()

        ser.write(bytes('21'.encode('UTF-8')))
        sleep(time)
        read()

        ser.write(bytes('31'.encode('UTF-8')))
        sleep(time)
        read()

        ser.write(bytes('41'.encode('UTF-8')))
        sleep(time)
        read()

        ser.write(bytes('10'.encode('UTF-8')))
        sleep(time)
        read()

        ser.write(bytes('20'.encode('UTF-8')))
        sleep(time)
        read()

        ser.write(bytes('30'.encode('UTF-8')))
        sleep(time)
        read()

        ser.write(bytes('40'.encode('UTF-8')))
        sleep(time)
        read()

    while True:
        read()
        sleep(0.5)

except KeyboardInterrupt:
    ser.close()
    print("\nExit\n");
