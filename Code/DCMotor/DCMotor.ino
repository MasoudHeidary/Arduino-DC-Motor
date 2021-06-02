#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// ------------------------------------------------------------------------------------------------------------------CONF
// Keypad configurations

const int RowNum = 4;
const int ColNum = 3;

char Keys[RowNum][ColNum] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte PinRow[RowNum] = { 3,2,1,0 };
byte PinCol[ColNum] = { 4,5,6 };

Keypad keypad = Keypad( makeKeymap(Keys), PinRow, PinCol, RowNum, ColNum);

// END Keypad configurations

// LCD Configuration
  LiquidCrystal_I2C lcd(0x20, 16, 2);
// END LCD Configuraiton

// Motor Conf
  const byte MotorPin = 10;
// END Motor Conf

// ------------------------------------------------------------------------------------------------------------------SETUP


void setup(){

  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print("enter from 0-100%");
  lcd.setCursor(0,1);
  lcd.print("clear input: #");
}

// ------------------------------------------------------------------------------------------------------------------LOOP

char Key = 0;
int InputSpeed = 0;   //0-100%
int MotorSpeed = 0;   //0-255

void loop(){

  Key = keypad.getKey();
  if( Key )
    ReadKey(Key);

  MotorSpeed = map(InputSpeed, 0, 100, 0, 255);
  analogWrite(MotorPin, MotorSpeed);
}

// ------------------------------------------------------------------------------------------------------------------FUNCTIONS

int NewInputSpeed = 0;

void ReadKey(char Key){
  if( Key == '#' ){
    NewInputSpeed = 0;
  }
  else{
  NewInputSpeed  = InputSpeed*10 + int(Key) - 48;
  if( NewInputSpeed > 100 or NewInputSpeed < 0 )
    return;
  }

  InputSpeed = NewInputSpeed;
  lcdUpdate();
}

void lcdUpdate(){
  lcd.clear();
  lcd.print(InputSpeed);
  lcd.print("%");
}
