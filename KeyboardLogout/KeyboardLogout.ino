#include "Keyboard.h"
#include "AESLib.h"

AESLib aesLib;

#define OSX 0
#define WINDOWS 1
#define UBUNTU 2
#define MENU_ITEMS 3

int menuPins[] = {2, 3, 6, 9, 10};
const char *letters = "abcdefghijklmnopqrstuvwxyz0123456789";
const int characters = sizeof letters/sizeof letters[0];

char cleartext[256];
char ciphertext[512];

// AES Encryption Key
byte aes_key[] = { 0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30 };
// General initialization vector (use your own)
byte aes_iv[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void setup() {
  delay(1000);
  for (int i=0; i<sizeof menuPins/sizeof menuPins[0]; i++) {
    pinMode(menuPins[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
  delay(1000);
  Keyboard.begin();
  delay(1000);
  randomSeed(analogRead(0)); //Fully randomizes generator
}
