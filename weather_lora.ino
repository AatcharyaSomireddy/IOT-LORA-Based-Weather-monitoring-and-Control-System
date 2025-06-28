
#include <LiquidCrystal.h>
#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#include <Adafruit_BMP085.h>


Adafruit_BMP085 bmp;
#define DHT11_PIN A1
#define ldr A0
#define buz A2

const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int cnt=0;
void setup() {

Serial.begin(9600);
delay(200);
pinMode(buz,OUTPUT);
lcd.begin(16, 2);
lcd.print("   WELCOME");

delay(200);
bmp.begin();

}

void loop() {
 
int lval=100-analogRead(ldr)/10.23;
DHT.read(DHT11_PIN);
int tval=DHT.temperature;
int hval=DHT.humidity;

float pval=bmp.readPressure()/1000;

lcd.clear();
lcd.print("T:"+String(tval) + " H:"+String(hval));
lcd.setCursor(0,1);
lcd.print("L:"+String(lval)+ "  P:"+ String(pval));

  Serial.println(String(tval)+ ","+String(hval)+ ","+String(lval)+ ","+String(pval));


if(tval>37 || hval>80 || pval>1018)
{
  digitalWrite(buz,1);
  delay(300);
  digitalWrite(buz,0);
}

delay(5000);
}
