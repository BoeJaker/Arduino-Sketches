String generate_password(){
  String randString;
  for (byte i=1; i <= 10; i++){    
    randString += letters[random(36)];
  }
//  sprintf(cleartext, randString);
//  String encrypted = encrypt(cleartext, aes_iv);
//  sprintf(ciphertext, "%s", encrypted.c_str());
//  String decrypted = decrypt(ciphertext, aes_iv);
  Keyboard.print(randString);
  return randString;
}
String new_password(){
  
}
void save_password(){
  
}
String recall_password(){
  
}
