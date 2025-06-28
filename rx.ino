#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>

// ThingSpeak Settings
String apiKey = "YQGJDQ59M8HJP43B";
const char *server = "http://api.thingspeak.com/update";

// WiFi Settings
const char* ssid = "SRC 24G";
const char* password = "src@internet";

// LCD I2C address (commonly 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define BUZZER_PIN 13 // Buzzer pin

void setup() {
  Serial.begin(9600);      // UART from Arduino
  Serial2.begin(9600);     // Optional: use Serial2 if RX0 is busy

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  lcd.begin();
  lcd.backlight();
  lcd.print("Connecting WiFi");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.print(".");
  }

  lcd.clear();
  lcd.print("WiFi Connected!");
  delay(1000);
  lcd.clear();
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    data.trim();

    // Expected format: tval,hval,lval,pval
    int tval, hval, lval;
    float pval;

    int sep1 = data.indexOf(',');
    int sep2 = data.indexOf(',', sep1 + 1);
    int sep3 = data.indexOf(',', sep2 + 1);

    if (sep1 > 0 && sep2 > sep1 && sep3 > sep2) {
      tval = data.substring(0, sep1).toInt();
      hval = data.substring(sep1 + 1, sep2).toInt();
      lval = data.substring(sep2 + 1, sep3).toInt();
      pval = data.substring(sep3 + 1).toFloat();

      // Print to LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("T:" + String(tval) + " H:" + String(hval));
      lcd.setCursor(0, 1);
      lcd.print("L:" + String(lval) + " P:" + String(pval));

      // Send to ThingSpeak
      sendToThingSpeak(tval, hval, lval, pval);

      // Activate buzzer if abnormal
      if (tval > 37 || hval > 80 || pval > 1018) {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(300);
        digitalWrite(BUZZER_PIN, LOW);
      }
    }
  }

  delay(5000);  // match delay with Arduino
}

void sendToThingSpeak(int t, int h, int l, float p) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = server + String("?api_key=") + apiKey +
                 "&field1=" + String(t) +
                 "&field2=" + String(h) +
                 "&field3=" + String(l) +
                 "&field4=" + String(p);

    http.begin(url);
    int httpCode = http.GET();
    http.end();
  }
}
