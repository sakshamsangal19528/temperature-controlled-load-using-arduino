#include <OneWire.h> //C:\Users\saksh\Documents\Arduino\libraries
#include <DallasTemperature.h> //C:\Users\saksh\Documents\Arduino\libraries
#include <LiquidCrystal_I2C_Hangul.h> //C:\Users\saksh\Documents\Arduino\libraries
LiquidCrystal_I2C_Hangul lcd(0x3F, 16, 2);


const int TEMP_THRESHOLD_UPPER = 45; // upper threshold of temperature, change to your desire value
//const int TEMP_THRESHOLD_LOWER = 30; // just adding, might need this if not... remove this later

const int SENSOR_PIN    = 2; // arduino pin connected to DS18B20 sensors DQ (data in/out) pin
const int RELAY_FAN_PIN = A1; // arduino pin connected to relay which connected to fan to controll fan
const int RELAY_LOAD_PIN = A0;
int buzzerPin = 8;
OneWire oneWire(SENSOR_PIN);         // setup a oneWire instance
DallasTemperature sensors(&oneWire); // pass oneWire to dallas temperature library

float temperature;    // temperature in Celsius

void setup()
{
  Serial.begin(9600); // initialize serial
  sensors.begin();    // initialize the sensor
  lcd.init();         // initialize the LCD
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp. Controlled");
  lcd.setCursor(0,1);
  lcd.print("      Load    ");
  pinMode(RELAY_FAN_PIN, OUTPUT); // initialize digital pin as an output
  pinMode(RELAY_LOAD_PIN, OUTPUT);
  digitalWrite(RELAY_FAN_PIN, LOW);
  digitalWrite(RELAY_LOAD_PIN, LOW);
  delay(2000);
 }

void loop()
{
 lcd.clear();
  sensors.requestTemperatures();             // send the command to get temperatures
  temperature = sensors.getTempCByIndex(0);  // read temperature in Celsius
   lcd.setCursor(0,0);
 Serial.println("Temperature:    ");
  Serial.println(temperature);
  lcd.print("Temp. : ");
  lcd.setCursor(8,0);
   lcd.print(temperature);
    lcd.setCursor(13,0);
 lcd.print((char)223);
   lcd.setCursor(14,0);
   lcd.print("C");
   
  if(temperature > TEMP_THRESHOLD_UPPER){
    Serial.println("The fan is turned on");
    Serial.println("The load is turned off");
     lcd.setCursor(0,1);
   lcd.print("Fan On, Load Off");
    digitalWrite(RELAY_FAN_PIN, HIGH); // turn onn the fan
     digitalWrite(RELAY_LOAD_PIN, LOW); //turn off the bulb
     } 
        else //if(temperature < TEMP_THRESHOLD_LOWER){
    Serial.println("The fan is turned off");
    Serial.println("The load is turned on");
     lcd.setCursor(0,1);
   lcd.print("Fan Off, Load On");
    digitalWrite(RELAY_FAN_PIN, LOW); // turn off the fan 
        digitalWrite(RELAY_LOAD_PIN, HIGH);//turn onn the bulb
        digitalWrite (buzzerPin, LOW);
  }
