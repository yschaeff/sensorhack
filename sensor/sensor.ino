#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <idDHT11.h>

/* Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3.3V DC
*/
   
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
int idDHT11pin = 2; //Digital pin for comunications
int idDHT11intNumber = 0; //interrupt number (must be the one that use the previus defined pin (see table above)

//declaration
void dht11_wrapper(); // must be declared before the lib initialization

// Lib instantiate
idDHT11 DHT11(idDHT11pin,idDHT11intNumber,dht11_wrapper);

void displaySensorDetails(void)
{
  sensor_t sensor;
  bmp.getSensor(&sensor);
  delay(500);
}

void setup(void) 
{
  Serial.begin(115200);
  if(!bmp.begin()) {
    Serial.print("error");
    while(1);
  }
 // Serial.println("online");
  delay(1000);
}

void dht11_wrapper() {
  DHT11.isrCallback();
}

void loop(void) 
{
  sensors_event_t event;
  bmp.getEvent(&event);
 
  if (event.pressure) {
    Serial.print("pressure:");
    Serial.println(float(event.pressure));
  
    float temperature;
    bmp.getTemperature(&temperature);
    Serial.print("temperature:");
    Serial.println(temperature);

    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    Serial.print("altitude:"); 
    Serial.println(bmp.pressureToAltitude(seaLevelPressure, event.pressure, temperature)); 
  }
  
 
  DHT11.acquire();
  while (DHT11.acquiring());

  if (DHT11.getStatus() == IDDHTLIB_OK)
  {
    Serial.print("humidity:");
    Serial.println(DHT11.getHumidity(), 2);

    Serial.print("temperature2:");
    Serial.println(DHT11.getCelsius(), 2);

    Serial.print("dewpoint:");
    Serial.println(DHT11.getDewPoint());

    Serial.print("dewpoint_slow:");
    Serial.println(DHT11.getDewPointSlow()); 
  }

  delay(3000);
}
