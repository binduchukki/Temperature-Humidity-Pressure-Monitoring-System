#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP085 bmp;

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  dht.begin();
  bmp.begin();
  lcd.init();
  lcd.backlight();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1);
  }

  display.clearDisplay();
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  float pressure = bmp.readPressure() / 100.0;

  if (isnan(temp) || isnan(hum)) return;

  // LCD (SHORT)
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp, 1);
  lcd.print("C ");
  lcd.print("H:");
  lcd.print(hum, 0);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("P:");
  lcd.print(pressure, 0);
  lcd.print("hPa");

  // OLED
  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Weather");

  display.setTextSize(3);
  display.setCursor(0, 12);
  display.print(temp, 1);
  display.println("C");

  display.setTextSize(1);
  display.setCursor(0, 45);

  
  if (temp > 35) {
    display.println("Weather is hot,");
    display.println("carry water");
  } 
  else if (temp < 18) {
    display.println("Weather is cold,");
    display.println("wear jacket");
  } 
  else {
    display.println("Weather is normal");
  }

  display.display();

  delay(2000);
}
