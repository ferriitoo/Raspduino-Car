#!/usr/bin/python
# -*- coding: iso-8859-1 -*-
import time
import serial
import pibrella

arduinoPort = serial.Serial('/dev/ttyACM0', 9600)

arduinoPort.write('s')
pibrella.light.amber.on()

