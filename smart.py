import serial, json
import urllib2, ssl, time
serialdev = None

if ssl._create_unverified_context:
	ctx = ssl._create_unverified_context()
else:
	ctx = None

req = urllib2.Request('https://postnl.smartsensors.me/api/v1/handler.php')
req.add_header('Content-Type','application/json')

while True:
	if serialdev:
		serialdev.close()

	try:
		serialdev = serial.Serial(
			port='/dev/ttyACM1', baudrate=115200, parity=serial.PARITY_NONE,
			stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS)
	except:
		print "openerr"
		time.sleep(3)
		continue

	buf = ""

	while True:
		try:
			c = serialdev.read(1)
		except:
			print "readerr"
			break

		if c == "\n":
			a = buf.strip().split(":")
			if len(a) != 2:
				buf = ""
				continue
			k = a[0]
			v = float(a[1])
			data = json.dumps({"action":"update", "uuid":"0xDEADBEEF", k:v})
			print data
			send(data)
			response = urllib2.urlopen(req, data, context=ctx)
			buf = ""
		else:
			buf += c

