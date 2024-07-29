
#include <Wire.h>              // include Arduino wire library (required for I2C devices)
#include <Adafruit_GFX.h>      // include Adafruit graphics library
#include <Adafruit_SSD1306.h>  // include Adafruit SSD1306 OLED display driver

// define SSD1306 OLED reset at NodeMCU D1 (GPIO5)
#define OLED_RESET    D1
// initialize Adafruit display library
Adafruit_SSD1306 display(OLED_RESET);

void setup()
{
  Serial.begin(9600);  // open serial port
  delay(1000);         // wait a second
  // set I2C pins [SDA = GPIO4 (D2), SCL = GPIO0 (D3)], default clock is 100kHz
  Wire.begin(4, 0);
  // initialize the SSD1306 OLED display with I2C address = 0x3D
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);

  // clear the display buffer.
  display.clearDisplay();

  display.setTextSize(1);   // text size = 1
  display.setTextColor(WHITE, BLACK);  // set text color to white and black background
  display.setCursor(15, 0);            // move cursor to position (15, 0) pixel
  display.print("LM35 TEMPERATURE:");
  display.display();        // update the display
  display.setTextSize(2);   // text size = 2
}

int tKelvin, tCelsius, tFahrenheit;
// main loop
void loop()
{
  // read analog voltage and convert it to tenths °C ( = millivolts)
  tCelsius = analogRead(A0) * 3300/1024;

  tKelvin     = tCelsius + 2732;       // convert tenths °C to tenths Kelvin
  tFahrenheit = tCelsius * 9/5 + 320 ; // convert tenths °C to tenths °Fahrenheit

  // print temperature in degree Celsius
  display.setCursor(23, 10);
  if (tCelsius >= 1000) {    // if temperature >= 100.0 °C
    display.printf("%03u.%1u C", tCelsius / 10, tCelsius % 10);
    Serial.printf("Temperature = %03u.%1u°C\r\n", tCelsius / 10, tCelsius % 10);
  }
  else {
    display.printf(" %02u.%1u C", tCelsius / 10, tCelsius % 10);
    Serial.printf("Temperature =  %02u.%1u°C\r\n", tCelsius / 10, tCelsius % 10);
  }

  // print temperature in degree Fahrenheit
  display.setCursor(23, 30);
  if (tFahrenheit >= 1000) {     // if temperature >= 100.0 °F
    display.printf("%03u.%1u F", tFahrenheit / 10, tFahrenheit % 10);
    Serial.printf("            = %03u.%1u°F\r\n", tFahrenheit / 10, tFahrenheit % 10);
  }
  else {
    display.printf(" %02u.%1u F", tFahrenheit / 10, tFahrenheit % 10);
    Serial.printf("            =  %2u.%1u°F\r\n", tFahrenheit / 10, tFahrenheit % 10);
  }
  
  // print temperature in Kelvin
  display.setCursor(23, 50);
  display.printf("%03u.%1u K", tKelvin / 10, tKelvin % 10);
  Serial.printf("            = %03u.%1u K\r\n\r\n", tKelvin / 10, tKelvin % 10);

  // print degree symbols ( ° )
  display.drawCircle(88, 12, 2, WHITE);
  display.drawCircle(88, 32, 2, WHITE);

  // update the display
  display.display();

  delay(1000);  // wait a second
}

// end of code.
