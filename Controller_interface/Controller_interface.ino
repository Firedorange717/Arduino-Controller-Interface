#include <Wire.h>

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//  Controller Version 0.2
//  OCTOBER 27 2019
//

//Constants (aka wont change)
const int left = 4;
const int leftMiddle = 5;
const int rightMiddle = 2;
const int right = 3;

const int ledPin =  13;

//Variables (aka will change)
int leftState = 0;
int  leftMiddleState = 0;
int  rightMiddleState = 0;
int  rightState = 0;

void setup() {
  //Setup Pin Modes
  pinMode(left, INPUT_PULLUP);
  pinMode(leftMiddle, INPUT_PULLUP);
  pinMode(rightMiddle, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);

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
  display.println(F("Ver. 0.2"));
  display.drawRect(0,0,128,64,SSD1306_WHITE);
  display.display();      // Show initial text
  delay(2000);

  
}

void loop() {
  //Button States
  leftState = digitalRead(left);
  leftMiddleState = digitalRead(leftMiddle);
  rightMiddleState = digitalRead(rightMiddle);
  rightState = digitalRead(right);


  if (leftState == LOW){
      
      testdrawtriangle();
      display.display();
    }
  else if(leftMiddleState == LOW){
      
      testdrawroundrect();
      display.display();
    }
  else if(rightMiddleState == LOW){
      
      testdrawstyles();
      display.display();
    }
  else if(rightState == LOW){
      
      testdrawchar();
      display.display();
    }
  else {
      display.clearDisplay();
      
      display.setTextSize(1);             // Normal 1:1 pixel scale
      display.setTextColor(SSD1306_WHITE);        // Draw white text
      display.setCursor(25,32);             // Start at top-left corner
      display.println(F("Press a Button"));
      display.display();
    } 
}

void testdrawtriangle(void) {
  display.clearDisplay();

  for(int16_t i=0; i<max(display.width(),display.height())/2; i+=5) {
    display.drawTriangle(
      display.width()/2  , display.height()/2-i,
      display.width()/2-i, display.height()/2+i,
      display.width()/2+i, display.height()/2+i, SSD1306_WHITE);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testdrawroundrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2-2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i,
      display.height()/4, SSD1306_WHITE);
    display.display();
    delay(1);
  }

  delay(2000);
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
  delay(2000);
}

void testdrawchar(void) {
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  for(int16_t i=0; i<256; i++) {
    if(i == '\n') display.write(' ');
    else          display.write(i);
  }
}
