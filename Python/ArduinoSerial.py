import serial
import struct
import select

serialPort = None
dataIn = [None]*8
index = 0
gyro_list = [1]*3
accel_list = [1]*3
leds_list = [255]*12
mode = 1
i = 0

def SerialInit():
	global serialPort
	serialPort = serial.Serial(port='/dev/cu.wchusbserial1430', baudrate=115200);

def SerialClose():
	global serialPort
	serialPort.flushOutput()
	serialPort.close()

def switchMode(newMode):
	global mode
	mode = newMode

def setLEDs(newLEDs):
	global leds_list
	leds_list = newLEDs

def setLED(led, value):
	global leds_list
	leds_list[led] = value

def WriteToSerial():
	global serialPort
	global leds_list
	global mode
	serialPort.write(struct.pack('B', 0))
	serialPort.write(struct.pack('B', mode))
	for x in range (0, len(leds_list) - 1):
		serialPort.write(struct.pack('B', leds_list(x)))

def ReadFromSerial():
	global serialPort
	global index
	global accel_list
	global gyro_list
	nextByte = struct.unpack('B', serialPort.read(1))[0]
	if nextByte is 0:
		index = 0
	dataIn[index] = nextByte
	index += 1;
	if index is 8:
		mode = dataIn[1]
		for x in range (2, 3):
			gyro_list[x - 2] = dataIn[x]
		for x in range (5, 7):
			accel_list[x - 5] = dataIn[x]
	 	index = 0

def MainLoop():
	while True:
		ReadFromSerial()


def main():
	MainLoop()

SerialInit()
while True:
	ReadFromSerial()

	#print(serialPort.readline())
	#serialPort.write("3")
	print str(i) + str(dataIn)
	i+= 1


if __name__ is '__main__':
	main()