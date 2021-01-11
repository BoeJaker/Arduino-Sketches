int menu_location = 1; // 0 - 10
int key_location[2] = {0, 0};
String newString = "";
String serialText = "";
int menu_debounce = 0;

int buttonRead[5] = {0, 0, 0, 0, 0};
int debounce = 10000;

void menu_case(byte menu_position){
  switch(menu_position){
  case 1: logout(); break; // Logout
  case 2: Serial.println(generate_password()); break; // Generate new
  case 3: new_password(); break;// Type new
  case 4: recall_password(); break;// Recall
  default: int a = 0; break;// Wait for input
  }
}

String keyboard_menu(){
  byte b = button_read();
  constrain(key_location[0]--,1,characters+1);
  if ( b = 1){ key_location[0]--; } // Changes character
  else if (b = 2){ key_location[0]++; }
  else if (b = 3){ newString+=letters[key_location[0]]; key_location[1]++ ;}
  else if (b = 4){ key_location[1]++ ;} //Moves cursor
  else if (b = 5){ key_location[1]-- ;};
  if (key_location[0] == characters+1){
    key_location[0], key_location[1] = 0;
    return newString;
  }
  return;
}
byte button_read(){
  for (byte i=0; i<sizeof menuPins/sizeof menuPins[0]; i++) {
    if (digitalRead(menuPins[i]) == LOW){ buttonRead[i]++ ; }
    else{buttonRead[i]-- ;};
    buttonRead[i] = constrain(buttonRead[i],0,debounce);
//    Serial.println(buttonRead[i]);
  }
  for (int i=0; i<sizeof buttonRead/sizeof buttonRead[0]; i++) {
    if (buttonRead[i] >= debounce){  ; return i+1;}
  }
  return 0;
}
void loop() {  
    menu_location = constrain(menu_location, 1, MENU_ITEMS+1);
    byte b = button_read();    
    if (menu_debounce == 0){
      if ( b == 1){menu_location-- ; menu_location = constrain(menu_location,1,MENU_ITEMS+1); Serial.println(menu_location); menu_debounce = debounce*2;}
      else if (b == 2){ menu_location++ ; menu_location = constrain(menu_location,1,MENU_ITEMS+1); Serial.println(menu_location); menu_debounce = debounce*2;}
      else if (b == 3){ menu_case(menu_location); menu_debounce = debounce*2;};
    } else {menu_debounce = constrain(menu_debounce--,0,debounce*2);}
    while (Serial.available() > 0) {
      // read the incoming byte:
      char incomingByte = (char)Serial.read();
      serialText+=incomingByte;
    }
    if (serialText.length() > 1){
      //Process text
      Serial.println(serialText);
      serialText="";  
    }
}
