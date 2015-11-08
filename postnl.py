#!/usr/bin/env python

import serial
import datetime
import sys
import time
import string
import json, urllib2, ssl, httplib

if hasattr(ssl, '_create_unverified_context'):
    ctx = ssl._create_unverified_context()
else:
    ctx = None

req = urllib2.Request('https://postnl.smartsensors.me/api/package')
req.add_header('Content-Type','application/json')

def run(dev):
        last_submit = time.time()
        buf = {}
	while 1:
		print "reconnecting to", dev
                try:
                    s = serial.Serial(dev, 115200)
                    _ = s.readline()
                except OSError:
                    print "device not available"
                    time.sleep(2)
                    continue
		while 1:
			try:
				l = s.readline()
                                now = time.time()
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
                        #print ll
                        buf[now] = ll[0] +":" + ll[1]
                        if last_submit + 10 < now and len(buf) > 0:
                            print buf
                            data = json.dumps({"uuid":"0xDEADBEEF",
                                "lat":"48.858093",
                                "lng":"2.294694",
                                "V":"yuri_01",
                                "usb_serial":buf})
                            #print data
                            try:
                                response = urllib2.urlopen(req, data, context=ctx)
                                print "sent report"
                            except httplib.BadStatusLine:
                                print line
                                print "fail to send, bad statusline"
                            except:
                                print "general error?"
                            buf.clear()
                            last_submit = now

			#time.sleep(2)

if __name__ == "__main__":
	if len(sys.argv) < 2:
		print "Missing argument serial device"
		print "Example usage: python fijnstof.py /dev/ttyUSB0"
		sys.exit(1)

	dev = sys.argv[1]
	while 1:
                run(dev)




