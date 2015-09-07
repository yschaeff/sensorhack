#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

/* Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3.3V DC
*/
   
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

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
  delay(1000);
}
