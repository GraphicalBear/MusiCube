import time
import serial
import random
from pygame import mixer

mixer.init()


running = True
elapsed_time = 0
next_value = 25

serialPort = serial.Serial(port = '', baudrate = 115200,).open()

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
    serialPort.write(picker)

serialPort.flushInput()
serialPort.flushOutput()

for x in range(10):
    serialPort.write(0)

serialPort.write(1)

elapsed_time = time.time()

while running:
    if serialPort.inWaiting() > 0:
        next_value = serialPort.readline()
    if next_value < 20 or next_value > 30:
        elapsed_time = time.time()
        serialPort.write(1)
    if next_value >= 20 and next_value <= 30:
        if elapsed_time - time.time() >= 25:
            play_song()
            serialPort.write(0)

# os.startfile('filepath')
#
# if y_axis > 130:
#     os.system('amixer set Master 5+')
# if y_axis > 100 and y_axis < 120:
#     os.system('amixer set Master 5-')
# if x_axis > 20 and x_axis < 30 and y_axis > 120 and y_axis < 130 and z_axis > 220 and z_axis < 230:
