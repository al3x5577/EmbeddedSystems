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

try:
    ser.write(bytes(
        'Hallo Welt!!!!!!!! Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetu'.encode(
            'UTF-8')))

    while True:
        #print(bytes([0x2a]))
        #ser.write(bytes([0x2a]))
        sleep(0.5)
        r = ser.readline()
        if len(r) > 0:
            print(r)
except KeyboardInterrupt:
    ser.close()
    print("\nExit\n");
