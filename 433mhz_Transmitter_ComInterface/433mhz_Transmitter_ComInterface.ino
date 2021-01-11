/*
  Example for different sending methods
  
  https://github.com/sui77/rc-switch/
  
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

char* inputString;         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete


void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println("ok");
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(4);

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);
  
  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);
  
  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(15);
  
}

char* parse(char* command){
  char channel = command[0];
  char socket = command[1];
  char state = command[2];
  char* buf;
  String rc_command = "";
  if (channel == '1'){
    rc_command += '0';
    rc_command += 'F';
    rc_command += 'F';
    rc_command += 'F';
  }
  else if (channel == '2'){
    rc_command += 'F';
    rc_command += '0';
    rc_command += 'F';
    rc_command += 'F';;
  }
  else if (channel == '3'){
    rc_command += 'F';
    rc_command += 'F';
    rc_command += '0';
    rc_command += 'F';
  }
  else if (channel == '4'){
    rc_command += 'F';
    rc_command += 'F';
    rc_command += 'F';
    rc_command += '0';
  }
  
  if (socket == '1'){
    rc_command += '0';
    rc_command += 'F';
    rc_command += 'F';
    rc_command += 'F';
  }
  else if (socket == '2'){
    rc_command += 'F';
    rc_command += '0';
    rc_command += 'F';
    rc_command += 'F';
  }
  else if (socket == '3'){
    rc_command += 'F';
    rc_command += 'F';
    rc_command += '0';
    rc_command += 'F';
  }
  else if (socket == '4'){
    rc_command += 'F';
    rc_command += 'F';
    rc_command += 'F';
    rc_command += '0';
  }
  
  if (state == '0'){
    rc_command += 'F';
    rc_command += 'F';
    rc_command += 'F';
    rc_command += '0';
  }
  else if (state == '1'){
    rc_command += 'F';
    rc_command += 'F';
    rc_command += 'F';
    rc_command += 'F';
  }
  rc_command.toCharArray(buf, 12);
  return buf;
}

void loop() {

  /* Same switch as above, but tri-state code */ 
  if ( stringComplete = true ){
    Serial.println(inputString);
  }
  mySwitch.sendTriState(parse(inputString));
/* Same switch as above, but tri-state code */ 
  mySwitch.sendTriState("0FFF0FFFFFFF");
  delay(1000);  
  mySwitch.sendTriState("0FFF0FFFFFF0");
  delay(1000);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
