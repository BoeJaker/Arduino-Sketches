#include "DigiKeyboard.h"
#include <EEPROM.h>

int passIndex = 0;
String passwords[] = {"none", "0123456789", "adalovelace"};

void setup() {
   delay(10);
   pinMode(0, INPUT); 
   pinMode(2, INPUT);
   pinMode(1, OUTPUT); 
   digitalWrite(1, HIGH);
   passIndex = EEPROM.read(0);
   DigiKeyboard.sendKeyStroke(KEY_SPACE, MOD_CONTROL_LEFT);
//   DigiKeyboard.delay(1000);
}

void loop() {
   if (digitalRead(0) == HIGH){
    digitalWrite(1, LOW);
    DigiKeyboard.sendKeyStroke(0);
  
    // Type out this string letter by letter on the computer (assumes US-style
    // keyboard)
    DigiKeyboard.println(passwords[passIndex]);
    DigiKeyboard.delay(10000);
    digitalWrite(1, HIGH);
  }
  while (digitalRead(2) == HIGH){
    digitalWrite(1, HIGH);
    passIndex++;
    if (passIndex >= 3){
      passIndex=0;
    }
    
//    DigiKeyboard.sendKeyStroke(0);
//    DigiKeyboard.println(passwords[passIndex]);
    EEPROM.write(0,passIndex);
    DigiKeyboard.delay(5000);
    digitalWrite(1, LOW);
  }
  // It's better to use DigiKeyboard.delay() over the regular Arduino delay()
  // if doing keyboard stuff because it keeps talking to the computer to make
  // sure the computer knows the keyboard is alive and connected
  while (digitalRead(0) == HIGH){
    DigiKeyboard.delay(1);
    if (digitalRead(2) == HIGH){
      break;
      
      
    }
  }
//  DigiKeyboard.delay(100);






}
