import json
import urllib2, ssl, time

if ssl._create_unverified_context:
	ctx = ssl._create_unverified_context()
else:
	ctx = None

#req = urllib2.Request('https://postnl.smartsensors.me/api/v1/handler.php')
req = urllib2.Request('https://postnl.smartsensors.me/api/package')
req.add_header('Content-Type','application/json')

while True:


                data = json.dumps({"action":"update", "uuid":"0xDEADBEEF"})
                print data
#                send(data)
                response = urllib2.urlopen(req, data, context=ctx)
                print response
                time.sleep(5)


#json object:
#    {
#            'uuid': 336445767, // device unique id
#            'lat': 1.3424353, // latitude
#            'lng': 1.53534, //longitude
#            'v': '1.23.4', // version of client app
#            'usb_serial': {"1969-12-22 23:03:33.432":"pressure:995.54","1969-12-22 23:03:33.436":"temperature:22.57"} // "1969-12-22 23:03:33.432" - time shift in a package per measurement, pressure:995.54 - serial measurement : value
#            'db_sounds': {"1969-12-22 23:03:33.432": 30, "1969-12-22 23:03:36.432": 28} // // "1969-12-22 23:03:33.432" - time shift in a package per measurement,30 - value in dB
#            }
