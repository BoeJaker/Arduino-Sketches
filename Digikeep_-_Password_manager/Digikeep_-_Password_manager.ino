// A password generator and store
//

#include "Keyboard.h";
#include <EEPROM.h>;

#include "AESLib.h"
AESLib aesLib;

#define LEFT 2
#define RIGHT 1
#define PWRD_INDEX 0

const char *letters = "abcdefghijklmnopqrstuvwxyz0123456789";
char * randString;

char cleartext[256];
char ciphertext[512];

// AES Encryption Key
byte aes_key[] = { 0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30 };
// General initialization vector (use your own)
byte aes_iv[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


// Generate IV (once)
void aes_init() {
 encrypt("AAAAAAAAAA", aes_iv); // workaround for incorrect B64 functionality on first run... initing b64 is not enough
}

String encrypt(char * msg, byte iv[]) {  
  int msgLen = strlen(msg);
  Serial.print("msglen = "); Serial.println(msgLen);
  char encrypted[4 * msgLen]; // AHA! needs to be large, 2x is not enough
  aesLib.encrypt64(msg, encrypted, aes_key, iv);
  Serial.print("encrypted = "); Serial.println(encrypted);
  return String(encrypted);
}

String decrypt(char * msg, byte iv[]) {
  unsigned long ms = micros();
  int msgLen = strlen(msg);
  char decrypted[msgLen/2]; // half may be enough
  aesLib.decrypt64(msg, decrypted, aes_key, iv);
  return String(decrypted);
}

/* non-blocking wait function */
void wait(unsigned long milliseconds) {
  unsigned long timeout = millis() + milliseconds;
  while (millis() < timeout) {
    yield();
  }
}
//

String generate_password(){
  randomSeed(analogRead(0)); //Fully randomizes generator
  for (byte i=1; i <= 10; i++){    
    randString += letters[random(36)];
  }
  sprintf(cleartext, randString);
  String encrypted = encrypt(cleartext, aes_iv);
  sprintf(ciphertext, "%s", encrypted.c_str());
  String decrypted = decrypt(ciphertext, aes_iv);
  return encrypted+" "+decrypted;
}

void set_pin(){

}
void pin_auth(){

}

void eprom_enc(){ //EEPROM Hash and write
  
}
String eprom_dec(){ //EEPROM Decrypt and read
  
}

void setup() {
   aes_init();
   pinMode(RIGHT, INPUT); 
   pinMode(LEFT, INPUT);
   Keyboard.begin();
   delay(1000);
   Keyboard.println(generate_password());
}

void loop() {
  int dbounce = 0;
   Keyboard.write(0);
   if (digitalRead(LEFT) == HIGH){
    while (digitalRead(LEFT) == HIGH){
      dbounce++;
    }
    if (dbounce >= 100){
      digitalWrite(1, LOW);
      EEPROM.get(int(EEPROM.read(PWRD_INDEX)), randString);
      Keyboard.println(randString);
      delay(10000);
      digitalWrite(1, HIGH);
    }
    else { //Increments password number slection
      EEPROM.write(PWRD_INDEX,EEPROM.read(PWRD_INDEX)+1);
      if(EEPROM.read(PWRD_INDEX) > EEPROM.read(1)){
         EEPROM.write(PWRD_INDEX,2);
      }
    }
    dbounce=0;
  }
  
  if (digitalRead(RIGHT) == HIGH){
    while (digitalRead(RIGHT) == HIGH){
      dbounce--;
    }
    if (dbounce <= -100){
      EEPROM.write(1, EEPROM.read(1)+1);//Increments password count
      EEPROM.put(EEPROM.read(1), generate_password());
    }
    dbounce=0;
  }
}
