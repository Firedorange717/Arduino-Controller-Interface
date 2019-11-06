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

//Button States
int backState = 0;
int  downState = 0;
int  upState = 0;
int  enterState = 0;

//Page number
int page = 0;
int max_page = 1;

//Pointer location
int pointer_x = 5;
int pointer_y = 16;



void setup() {
  //Setup Pin Modes
  pinMode(back, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(up, INPUT_PULLUP);
  pinMode(enter, INPUT_PULLUP);

  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(35, 20);
  display.println(F("Controller"));
  display.setCursor(42, 35);
  display.println(F("Ver. 0.3"));
  display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
  display.display();      // Show initial text
  delay(1000);


}

void loop() {
  //Button States
  backState = digitalRead(back);
  downState = digitalRead(down);
  upState = digitalRead(up);
  enterState = digitalRead(enter);

  //Display correct page
  if (page == 0) {
    page_0();
  }
  else if (page == 1) {
    page_1();
  }

  //*******Back Button press*******
  if (backState == LOW) {
    display.display();
  }

  //*******Down Button press*******
  else if (downState == LOW) {
    //Moves Pointer down
    if (page == max_page) {
      if (pointer_y < 52) {
        pointer_y += 12;
        delay(100);
      }
    }
    else {
      if (pointer_y < 64) {
        pointer_y += 12;
        delay(100);
      }
    }
    if (pointer_y == 64) {
      if (page != max_page) {
        page += 1;
        pointer_y = 16;
      }
    }
    display.display();
  }

  //******Up Button press*******
  else if (upState == LOW) {
    //Moves Pointer up
    if (pointer_y != 16 || page != 0) {
      if (pointer_y > 2) {
        pointer_y -= 12;
        delay(150);
      }
    }
    if (pointer_y == 4 && page > 0) {
      page -= 1;
      pointer_y = 52;
    }
    display.display();
  }

  //*******Enter Button press********
  else if (enterState == LOW) {
    display.display();
  }
}

void page_0(void) {
  display.clearDisplay();

  //Draw Pointer
  display.setCursor(pointer_x, pointer_y);
  display.println("->");

  //Page Number
  display.setCursor(92, 0);
  display.println("Page 0");

  //Header
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); //Inverts text color
  display.setCursor(20, 0);
  display.println(F("MAIN MENU"));

  //Divider
  display.drawLine(0, 11, 128, 11, SSD1306_WHITE);

  //Menu Contents
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(25, 16);
  display.println(F("Item #1"));
  display.setCursor(25, 28);
  display.println(F("Item #2"));
  display.setCursor(25, 40);
  display.println(F("Item #3"));
  display.setCursor(25, 52);
  display.println(F("Item #4"));
  display.display();

}

void page_1(void) {
  display.clearDisplay();

  //Draw Pointer
  display.setCursor(pointer_x, pointer_y);
  display.println("->");

  //Page Number
  display.setCursor(92, 0);
  display.println("Page 1");

  //Header
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); //Inverts text color
  display.setCursor(20, 0);
  display.println(F("MAIN MENU"));

  //Divider
  display.drawLine(0, 11, 128, 11, SSD1306_WHITE);

  //Menu Contents
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(25, 16);
  display.println(F("Item #5"));
  display.setCursor(25, 28);
  display.println(F("Item #6"));
  display.setCursor(25, 40);
  display.println(F("Item #7"));
  display.setCursor(25, 52);
  display.println(F("Item #8"));
  display.display();

}
