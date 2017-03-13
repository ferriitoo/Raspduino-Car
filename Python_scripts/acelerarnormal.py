#!/usr/bin/python
# -*- coding: iso-8859-1 -*-
import time
import serial
import pibrella
import time

arduinoPort = serial.Serial('/dev/ttyACM0', 9600)
arduinoPort.write('d')
#pibrella.buzzer.success()
#pibrella.light.green.pulse(1, 1, 1, 1)
#time.sleep(2000)
