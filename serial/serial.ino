char incomingByte = "";
String serialText = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();
      serialText+=incomingByte;
    }
    if (sizeof serialText >= 1){
      Serial.println(serialText);
      serialText="";  
    }
}
