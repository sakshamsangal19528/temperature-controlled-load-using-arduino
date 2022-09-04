#include <OneWire.h>
#include <DallasTemperature.h>
#include<LiquidCrystal_I2C_Hangul.h>

LiquidCrystal_I2C_Hangul Lcd(0x27, 16, 2);


const int TEMP_THRESHOLD_UPPER = 45; // upper threshold of temperature, change to your desire value

const int SENSOR_PIN    = 2; // Arduino pin connected to DS18B20 sensor's DQ pin
const int RELAY_FAN_PIN = A1; // Arduino pin connected to relay which connected to fan
const int RELAY_LOAD_PIN = A0;
OneWire oneWire(SENSOR_PIN);         // setup a oneWire instance
DallasTemperature sensors(&oneWire); // pass oneWire to DallasTemperature library

float temperature;    // temperature in Celsius

void setup()
{
  Serial.begin(9600); // initialize serial
  sensors.begin();    // initialize the sensor
  Lcd.init();
  //Wire.begin(2,0);
  Lcd.backlight();
  Lcd.clear();
  Lcd.setCursor(0,0);
  Lcd.print("Temp. Controlled");
  Lcd.setCursor(0,1);
  Lcd.print("      Load    ");
  pinMode(RELAY_FAN_PIN, OUTPUT); // initialize digital pin as an output
  pinMode(RELAY_LOAD_PIN, OUTPUT);
  digitalWrite(RELAY_FAN_PIN, LOW);
  digitalWrite(RELAY_LOAD_PIN, LOW);
  delay(2000);
     
}

void loop()
{
Lcd.clear();
   // lcd.backlight();
  sensors.requestTemperatures();             // send the command to get temperatures
  temperature = sensors.getTempCByIndex(0);  // read temperature in Celsius
   Lcd.setCursor(0,0);
 Serial.println("Temperature:    ");
  Serial.println(temperature);
  Lcd.print("Temp. : ");
  Lcd.setCursor(8,0);
   Lcd.print(temperature);
    Lcd.setCursor(13,0);
 Lcd.print((char)223);
   Lcd.setCursor(14,0);
   Lcd.print("C");
   
  if(temperature > TEMP_THRESHOLD_UPPER){
    Serial.println("The fan is turned on");
    Serial.println("The load is turned off");
     Lcd.setCursor(0,1);
   Lcd.print("Fan On, Load Off");
    digitalWrite(RELAY_FAN_PIN, HIGH); // turn on
     digitalWrite(RELAY_LOAD_PIN, LOW);
     
  } else
  {
    Serial.println("The fan is turned off");
    Serial.println("The load is turned on");
     Lcd.setCursor(0,1);
   Lcd.print("Fan Off, Load On");
    digitalWrite(RELAY_FAN_PIN, LOW); // turn off
        digitalWrite(RELAY_LOAD_PIN, HIGH);
  }

  //delay(500);
}
