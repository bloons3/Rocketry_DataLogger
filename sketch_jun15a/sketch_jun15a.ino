// Pressure @ Ground level in Pascals
//default is 101325 Pascal

#include <Adafruit_BMP085.h>
#include <SoftwareSerial.h>
#include <Wire.h>

SoftwareSerial soft(3, 2); //RX,TX
Adafruit_BMP085 bmp;

int temp_C;
unsigned long pressure_Pa;
int alt_M;

long daily_Pressure;

void setup()
{
  /*Serial.begin(9600);
    Serial.println("USB SERIAL!");*/
  soft.begin(9600);
  pinMode(13, OUTPUT);
  if (!bmp.begin()) {
    //Serial.println("Could not find a valid BMP085 sensor, check wiring!");

    while (1) {

      digitalWrite(13, HIGH);
      delay(250);
      digitalWrite(13, LOW);
      delay(100);


    }
  }
  //Serial.println("BMP180 online!");

  daily_Pressure = bmp.readPressure();

  //Serial.println("Pressure Set!");
  //Serial.println("Time in Milliseconds, Temperature degC, Pressure in Pascals, Altitude in Meters");
  soft.println("milliseconds, deg_Centigrade, pascals, meters");



}

// Time in Milliseconds, Temperature, Pressure, Altitude
void loop()
{

  temp_C = bmp.readTemperature();
  pressure_Pa = bmp.readPressure();
  alt_M = bmp.readAltitude(daily_Pressure);

  //Serial.println(millis(), DEC);//time


  soft.print(millis(), DEC);//time
  soft.print(",");
  soft.print(temp_C, DEC);//temp
  soft.print(",");
  soft.print(pressure_Pa, DEC);//pressure
  soft.print(",");
  soft.println(alt_M, DEC);//alt
  digitalWrite(13, LOW);
  delay(500);
  digitalWrite(13, HIGH);
}

