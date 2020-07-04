import serial

ser = serial.Serial(
    port='/dev/tty.usbserial-14210',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=0
)

print("Connected to: " + ser.portstr + "\n")

try:
    while True:
        r = ser.read()
        print (r)
except KeyboardInterrupt:
    ser.close()
    print("\nExit\n");
