/*********************

Arduino Uno
Adafruit LCD RGB display
Motor sheld V2   For use with the Adafruit Motor Shield v2  	http://www.adafruit.com/products/1438

**********************/

// include the library code:
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>       
#include <Adafruit_MotorShield.h>                 //Motor Shield V2
#include "utility/Adafruit_PWMServoDriver.h"      //Motor Shield V2
// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x63); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *xmotor  = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *ymotor  = AFMS.getStepper(200, 2);

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

void setup() {
  // Debugging output
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);


  AFMS.begin();  // create with the default frequency 1.6KHz

  xmotor->setSpeed(100);  // 10 rpm  
  ymotor->setSpeed(200);  // 10 rpm  

  // Print a message to the LCD. We track how long it takes since
  // this library has been optimized a bit and we're proud of it :)
  int time = millis();
  lcd.setCursor(0,0);
  lcd.print("Hello, world!");
  time = millis() - time;
  lcd.setCursor(0, 1);
  Serial.print("Took "); Serial.print(time); Serial.println(" ms");
  lcd.setBacklight(WHITE);
}

uint8_t i=0;
void loop() {
    
  uint8_t buttons = lcd.readButtons();
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):

  if (buttons) {
    lcd.clear();
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(buttons);
  
    lcd.setCursor(0,0);
    if (buttons & BUTTON_UP) {
      lcd.print("UP");
      lcd.setBacklight(RED);
      xmotor->step(100, FORWARD, SINGLE);
      xmotor->release();
 
    }
    if (buttons & BUTTON_DOWN) {
      lcd.print("DOWN ");
      lcd.setBacklight(YELLOW);
      xmotor->step(100, BACKWARD, SINGLE);
      ymotor->release(); 
    }
    if (buttons & BUTTON_LEFT) {
      lcd.print("LEFT ");
      lcd.setBacklight(GREEN);
      ymotor->step(100, FORWARD, SINGLE); 
      ymotor->release();
     }
    if (buttons & BUTTON_RIGHT) {
      lcd.print("RIGHT ");
      lcd.setBacklight(TEAL);
      ymotor->step(100, BACKWARD, SINGLE);
      ymotor->release();
    }
    if (buttons & BUTTON_SELECT) {
      lcd.print("Select");
      lcd.setBacklight(VIOLET);
      ymotor->release();
      xmotor->release();
    }
    if (buttons == 18) {
      lcd.print("Right and Left");
      lcd.setBacklight(VIOLET);
      ymotor->release();
      xmotor->release();
    }
  }
}
