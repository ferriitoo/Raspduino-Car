#!/usr/bin/python
# -*- coding: iso-8859-1 -*-
import time
import serial

arduinoPort = serial.Serial('/dev/ttyACM0', 9600)
arduinoPort.write(" ")


