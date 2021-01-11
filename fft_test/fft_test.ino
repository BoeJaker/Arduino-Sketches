#include <fix_fft.h>

#include <SoftwareSerial.h>

char im[128];
char data[128]; 
int static i = 0;

void setup(){
  Serial.begin(115200);
  pinMode(0, INPUT);
}

void loop(){
 static long tt;
 int val;
  
  if (millis() > tt){
     if (i < 128){
       val = analogRead(0);
       data[i] = val;
       im[i] = 0;
       i++;   
       
     }
     else{
       //this could be done with the fix_fftr function without the im array.
       fix_fft(data,im,7,0);
       for (i=3; i< 64;i++){
          Serial.println(data[i], 1); 
       }
     }
   
   tt = millis();
  }
}
