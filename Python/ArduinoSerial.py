import serial
import struct
import select

serialPort = None
dataIn = [None]*8
arduino_mode = None
index = 0
gyro_list = 1
accel_list = [1]*3
leds_list = [[1 for x in range(4)] for x in range(2)] 
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

def setMode(newMode):
	global mode
	mode = newMode

def setLEDs(newLEDs):
	global leds_list
	leds_list = newLEDs

def setLED(led, r, g, b):
	global leds_list
	leds_list[led][0] = r
	leds_list[led][1] = g
	leds_list[led][2] = b

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
	global arduino_mode
	if (serialPort.inWaiting() >= 6):
		for (int i = 0; i < 6; i++):
			nextByte = struct.unpack('B', serialPort.read(1))[0]
			if nextByte is 0:
				index = 0
			dataIn[index] = nextByte
			index+= 1
		arduino_mode = dataIn[1]
		gyro = dataIn[2]
		for x in range (3, 5):
			accel_list[x - 3] = dataIn[x]
		serialPort.flushInput()

def UpdateLEDs():
	print "do stuff"

def main():
	global arduino_mode
	SerialInit()
	setMode(2)
	while arduino_mode is not 2:
		ReadFromSerial()

	while True:
		ReadFromSerial()
		UpdateLEDs()
		WriteToSerial()






if __name__ is '__main__':
	main()