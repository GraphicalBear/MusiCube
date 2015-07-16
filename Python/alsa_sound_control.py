import time
import serial
import random
from pygame import mixer

mixer.init()

running = True
elapsed_time = 0
next_value = 25

serialPort = serial.Serial(port = '/dev/ttyUSB0', baudrate = 115200)

def play_song():
    # picker = random.randint(2, 4)
    global serialPort
    picker = 2
    if picker is 2:
        file_path = '/home/pi/Music/Still_Alive.mp3'
    if picker is 3:
        file_path = '/home/pi/Music/Mario_Theme.mp3'
    if picker is 4:
        file_path = '/home/pi/Music/Tetris_Theme.mp3'
    mixer.music.load(file_path)
    mixer.music.play()
    serialPort.write(bytes([picker]))

serialPort.flushInput()
serialPort.flushOutput()

for x in range(10):
    serialPort.write(bytes([0]))

serialPort.write(bytes([1]))

elapsed_time = time.time()

while running:
    if serialPort.inWaiting() > 0:
        next_value = serialPort.readline()
        print next_value
        try:
            next_value = int(next_value)
        except TypeError:
            next_value = 0
    if abs(next_value) > 1000:
        elapsed_time = time.time()
        serialPort.write(bytes([1]))
    else:
        if elapsed_time - time.time() >= 25:
            play_song()
            serialPort.write(bytes([0]))
