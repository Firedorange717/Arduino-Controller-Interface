#include <Wire.h>

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//  Controller Version 0.3
//  NOVEMBER 3 2019
//

//Constants (aka wont change)
const int back = 4;
const int down = 5;
const int up = 2;
const int enter = 3;


//Variables (aka will change)
int backState = 0;
int  downState = 0;
int  upState = 0;
int  enterState = 0;

void setup() {
  //Setup Pin Modes
  pinMode(back, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(up, INPUT_PULLUP);
  pinMode(enter, INPUT_PULLUP);

  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(35, 20);
  display.println(F("Controller"));
  display.setCursor(42, 35);
  display.println(F("Ver. 0.3"));
  display.drawRect(0,0,128,64,SSD1306_WHITE);
  display.display();      // Show initial text
  delay(2000);

  
}

void loop() {
  //Button States
  backState = digitalRead(back);
  downState = digitalRead(down);
  upState = digitalRead(up);
  enterState = digitalRead(enter);


  if (backState == LOW){
      display.clearDisplay();

      
      display.display();
    }
  else if(downState == LOW){
      display.clearDisplay();
      testdrawstyles();
      display.display();
    }
  else if(upState == LOW){
       display.clearDisplay();
      
      display.display();
    }
  else if(enterState == LOW){
      display.clearDisplay();
      
      display.display();
    }
  else {
      display.clearDisplay();
      
      display.setTextSize(1);             // Normal 1:1 pixel scale
      display.setTextColor(SSD1306_BLACK,SSD1306_WHITE);        // Draw white text
      display.setCursor(0,0);             // Start at top-left corner
      display.println(F("Motor Direction"));
      display.display();
    } 
}

void testdrawstyles(void) {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Hello, world!"));

  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.println(3.141592);

  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.print(F("0x")); display.println(0xDEADBEEF, HEX);

  display.display();
  delay(4000);
}
