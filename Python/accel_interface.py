from wavebender import *
from math import cos
import sys
import time
import AduinoSerial

class accel_interface(object):
    def __init__(self):

    def get_gyro_data(self, axis = 'all'):
        global gyro_list
        if axis is 'x':
            return gyro_list[0]
        if axis is 'y':
            return gyro_list[1]
        if axis is 'z':
            return gyro_list[2]
        if axis is 'all':
            return gyro_list

    def get_accel_data(self, axis = 'all'):
        global accel_list
        if axis is 'x':
            return accel_list[0]
        if axis is 'y':
            return accel_list[1]
        if axis is 'z':
            return accel_list[2]
        if axis is 'all':
            return accel_list

    def vol(self):
        return get_accel_data(axis = 'x')
    def pitch(self):
        return get_accel_data(axis = 'y')
    def adj_filter(self):
        return get_accel_data(axis = 'z')

def main():
    

if __name__ is '__main__':
    main()
