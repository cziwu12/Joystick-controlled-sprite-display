#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int LCD_LENGTH = 2; 
const int LCD_WIDTH = 16; 
int xPin = A0;
int yPin = A1;
int xVal;
int yVal;
int cursorX = 0;
int cursorY = 0;
int preCursorX;
int preCursorY;
int baseFrame = 1;
int walkingState;
unsigned long is500ms;
bool joystickPressed = false; 

byte idleChar1[] = {
  B00110,
  B01110,
  B00100,
  B01110,
  B10101,
  B00100,
  B01010,
  B10001
};

byte idleChar2[] = {
  B01100,
  B01110,
  B00100,
  B01110,
  B10101,
  B00100,
  B01010,
  B10001
};

byte walkingAni1[] = {
  B00110,
  B01110,
  B00100,
  B01110,
  B11101,
  B00100,
  B01011,
  B11001
};

byte walkingAni2[] = {
  B00110,
  B01110,
  B00100,
  B01111,
  B10101,
  B00100,
  B01010,
  B10011
};

byte walkingAni3[] = {
  B01100,
  B01110,
  B00100,
  B01110,
  B10111,
  B00100,
  B11010,
  B10011
};

byte walkingAni4[] = {
  B01100,
  B01110,
  B00100,
  B11110,
  B10101,
  B00100,
  B01010,
  B11001
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, idleChar1);
  lcd.createChar(1, walkingAni1);
  lcd.createChar(2, walkingAni2);
  lcd.createChar(3, walkingAni3);
  lcd.createChar(4, walkingAni4);
  lcd.createChar(5, idleChar2);
  lcd.setCursor(0, 0);
  lcd.write(5);

}

void loop() {
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
  
  unsigned long currentMillis = millis(); 

  Serial.print(currentMillis);
  Serial.print(" X: ");
  Serial.print(xVal);
  Serial.print(" | Y: ");
  Serial.println(yVal);

  if (xVal < 312 || xVal > 712 || yVal < 312 || yVal > 712 ) {
    if (joystickPressed == false) {
      joystickPressed = true;
      is500ms = currentMillis + 500;
      moveCharacter(currentMillis);
    }
    else if (currentMillis >= is500ms && joystickPressed == true) {
      moveCharacter(currentMillis);
    }
  }
  else {
    if (joystickPressed == true) {
      lcd.setCursor(preCursorX, preCursorY);
      lcd.print(" ");
      lcd.setCursor(preCursorX, preCursorY);
      if (baseFrame == 3) {
        lcd.write(5);
      }
      else {
        lcd.write(0);
      }
      joystickPressed = false;
    }
    is500ms = 0;       
  } 
}

void moveCharacter(unsigned long currentMillis) {
  if (xVal < 312) {
    cursorX--;
    baseFrame = 1;
  }
  else if (xVal > 712) {
    cursorX++;
    baseFrame = 3;
  }
  if (yVal < 312) {
    cursorY--;
  }
  else if (yVal > 712) {
    cursorY++;
  }

  walkingState = (walkingState + 1) % 2;

  if (cursorX < 0) cursorX = 0;
  if (cursorX >= LCD_WIDTH) cursorX = LCD_WIDTH - 1;
  if (cursorY < 0) cursorY = 0;
  if (cursorY >= LCD_LENGTH) cursorY = LCD_LENGTH - 1;
      
  lcd.setCursor(preCursorX, preCursorY);
  lcd.print(" ");
  lcd.setCursor(cursorX, cursorY);
  lcd.write(baseFrame + walkingState);
  preCursorX = cursorX;
  preCursorY = cursorY;

  is500ms = currentMillis + 200;
}


