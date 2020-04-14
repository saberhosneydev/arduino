#include <LiquidCrystal.h>
int stp = 0;
int counter = 0;
int cond = 1;
//LCD pin to Arduino
const int pin_RS = 8;
const int pin_EN = 9;
const int pin_d4 = 4;
const int pin_d5 = 5;
const int pin_d6 = 6;
const int pin_d7 = 7;
const int pin_BL = 10;
LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);
void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Enter Step Numb");
  lcd.setCursor(0, 1);
  lcd.print("Up/Down:");
  lcd.setCursor(8, 1);
  lcd.print(stp);

}
void clearLCD() {
  for (int i = 8; i < 15; ++i)
  {
    lcd.setCursor(i, 1);
    lcd.print(" ");
    lcd.setCursor(8, 1);
  }
}

void selectStep(){
  int x;
  while (true) {
    delay(133);
    x = analogRead(0);
    lcd.setCursor(8, 1);
    //Right
    if (x < 60) {
      lcd.print ("Right ");
    }
    // Up
    else if (x < 200) {
      clearLCD();
      stp+=1;
      lcd.print (stp);
    }
    //Down
    else if (x < 400) {
      clearLCD();
      if((stp-=1) < 0){
        stp = 0;
      }
      lcd.print (stp);
    }
    // Left
    else if (x < 600) {
      lcd.print ("Left  ");
    }
    else if(x < 800){
      if (stp == 0)
      {
        lcd.print("Invalid");
      }else {
        cond = 0;
        break;
        
      }
    }
  }
}
void loop() {
  //Buttons
  if (cond == 1)
  {
    selectStep();
  }else {
    lcd.setCursor(0, 0);
    lcd.print("Step up/down: ");
    lcd.print(stp);
    lcd.setCursor(0, 1);
    lcd.print("Number: ");
    lcd.setCursor(9, 1);
    lcd.print(counter);
    delay(133);
    int button = analogRead(0);
    if(button < 200){
      counter += stp;
    }else if (button < 400) {
      counter -= stp;
    }

  }

}
