#!/usr/bin/env python

import serial
import datetime
import sys
import time
import string

def run(dev):
	while 1:
		print "reconnecting to", dev
                try:
                    s = serial.Serial(dev, 115200)
                except OSError:
                    print "device not available"
                    time.sleep(2)
                    continue
		while 1:
			try:
				l = s.readline()
			#	print "read: ", l
			except OSError:
				print "read err"
				time.sleep(1)
				break;
			except serial.serialutil.SerialException:
				break;
                        
                        ll = l.split(":")
                        if len(ll) != 3:
                            print "parse err"
                            continue
                        ll = map(string.strip, ll)
                        print ll 

			#time.sleep(2)

if __name__ == "__main__":
	if len(sys.argv) < 2:
		print "Missing argument serial device"
		print "Example usage: python fijnstof.py /dev/ttyUSB0"
		sys.exit(1)

	dev = sys.argv[1]
	while 1:
                run(dev)




