#include <Wire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>


#define ONE_WIRE_BUS 8

LiquidCrystal_I2C lcd(0x27,16,2);  

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const byte pHpin = A3;
float Po;
int vacio;
int medio;
int lleno;

void setup() {
  
  Serial.begin(115200);
  sensors.begin();
  pinMode(2,INPUT);
  pinMode(3,INPUT);


  lcd.init();
  
  lcd.backlight();

  lcd.print("Estado de tanque");

}

void loop() {
    medio = digitalRead(2);
    lleno = digitalRead(3);

  lcd.setCursor(0, 1);

   if(lleno==1 && medio ==1)
   {
    lcd.print("10 lts lleno");
    
    }

    if (medio==1 && lleno == 0)
    {
      lcd.print("Cap. a 5 lts");
      
    }
  
  if(medio == 0 && lleno == 0)
  {
    lcd.print("Tanque Vacio");
    
  }
  
    sensors.requestTemperatures();

float tempC = sensors.getTempCByIndex(0);
    

    Po = (1023 - analogRead(pHpin)) / 73.07;

    String a = String(tempC,2);
    String b = String(Po,2);
    //Serial.print(a+"/"+b);
    Serial.print(String(a));
    Serial.print(String("D"));
    Serial.println(String(b));
    

   /*
    Serial.print(tempC );
    Serial.print(",");
    Serial.print(Po,2);
   */ 
    delay(1000);
}
