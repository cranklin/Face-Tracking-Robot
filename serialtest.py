import serial

ser = serial.Serial(port='/dev/tty.usbmodemfd111',baudrate=19200,timeout=0)
#ser.write("90x90y")
ser.write("0")
