#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <idDHT11.h>

/* idDHT11 */
int idDHT11pin = 5; //Digital pin for comunications
int idDHT11intNumber = 3; //interrupt number (must be the one that use the previus defined pin (see table above)
void dht11_wrapper(); // must be declared before the lib initialization
idDHT11 DHT11(idDHT11pin, idDHT11intNumber, dht11_irq);

/* BMP180 */
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

/* moisture sensor interupt routine */
void dht11_irq() {
  DHT11.isrCallback();
}

void setup(void) 
{
  Serial.begin(115200); // maybe we don't need this?
  if(!bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  // For IRQ idDHT11   
  pinMode(1, INPUT);
}

void loop(void) 
{
  /* BMP180 */ 
  sensors_event_t event;
  bmp.getEvent(&event);
 
  if (event.pressure)
  {
    Serial.print("Pressure: ");
    Serial.print(event.pressure);
    Serial.println(" hPa");
    
    float temperature;
    bmp.getTemperature(&temperature);
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

//    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    // This is an estime for haarlem, it will vary.
    float seaLevelPressure = 1018.0;
    Serial.print("Altitude: "); 
    Serial.print(bmp.pressureToAltitude(seaLevelPressure,
                                        event.pressure,
                                        temperature)); 
    Serial.println(" m");
  }

  /* Microphone. Just analog value */
  Serial.print("Sound: ");
  Serial.print(analogRead(A2));
  Serial.println(" Andre");
  
  /* idDHT11*/
  DHT11.acquire();
  while (DHT11.acquiring());
  
  int result = DHT11.getStatus();
  Serial.print("Humidity: ");
  Serial.print(DHT11.getHumidity(), 2);
  Serial.println(" %");

  Serial.print("Temperature: ");
  Serial.print(DHT11.getCelsius(), 2);
  Serial.println(" C");

  Serial.print("Temperature: ");
  Serial.print(DHT11.getFahrenheit(), 2);
  Serial.println(" F");

  Serial.print("Temperature: ");
  Serial.print(DHT11.getKelvin(), 2);
  Serial.println(" K");

  Serial.print("Dew Point: ");
  Serial.print(DHT11.getDewPoint());
  Serial.println(" C");

  Serial.print("Dew Point Slow: ");
  Serial.print(DHT11.getDewPointSlow());
  Serial.println(" C");

  delay(1000);
}
