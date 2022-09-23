#include <LiquidCrystal_I2C.h>
#include<OneWire.h>
#include<DallasTemperature.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
float temp = {0};
int oneWireBus = 2;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);
int RELAY_FAN_PIN = A0;
int RELAY_LOAD_PIN = A1;
int TEMPERATURE_LIMIT = 31;
void setup() {
  pinMode(RELAY_FAN_PIN, OUTPUT);
  pinMode(RELAY_LOAD_PIN, OUTPUT);
  digitalWrite(RELAY_FAN_PIN, LOW);
  digitalWrite(RELAY_LOAD_PIN, LOW);
  Serial.begin(9600);
  lcd.begin();
  sensors.begin();
  lcd.backlight();
  delay(2000);
  
  
}
void loop() {
  sensors.requestTemperatures();
  temp=sensors.getTempCByIndex(0);
  Serial.print("Temperature is : ");
  Serial.println(temp);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp. : ");
  lcd.setCursor(8,0);
  lcd.print(temp);
  lcd.setCursor(13,0);
  lcd.print((char)223);
  lcd.print("C");

  if(temp>TEMPERATURE_LIMIT)
    {
    lcd.setCursor(0,1);
    lcd.print("FAN ON, LOAD OFF");
    digitalWrite(RELAY_FAN_PIN,HIGH);
    digitalWrite(RELAY_LOAD_PIN,LOW);
      }
    else
     {
    lcd.setCursor(0,1);
    lcd.print("FAN OFF, LOAD ON");
    digitalWrite(RELAY_FAN_PIN,LOW);
    digitalWrite(RELAY_LOAD_PIN,HIGH);    
      }
  delay(500);
  

}
