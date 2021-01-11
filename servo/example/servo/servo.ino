/*************************************************** 
  Robot Arm w/ i2c, Wire.h & Adafruit PWM.

 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN  130 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  1100 // this is the 'maximum' pulse length count (out of 4096)

// Degrees of freedom that the arm has
const uint8_t dof = 6;

// Servo sequence counter
uint8_t servonum = 0;

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

class Servo 
{ 
  // Access specifier 
  private: 
    // Data Members 
    
    String joint; //Joint name [base/ elbow/ wrist/ claw]
    int upper_limit; //Limit of movement
    int lower_limit;
    
  public:
    int number; //Sequence number from base 
    Servo(int number, int upper_limit, int lower_limit, String joint)
    {
      this->number = number;
      this->upper_limit = constrain(upper_limit, 0, 180);
      this->lower_limit = constrain(lower_limit, 0, 180);
      this->joint = joint;
    }

    // Member Functions() 
    void move(int degrees) 
    { 
      uint16_t pulselen = map(degrees, lower_limit, upper_limit, SERVOMIN, SERVOMAX);
      pwm.setPWM(number, 0, pulselen);
      delay(2000);
    } 

    void center()
    {
      uint16_t pulselen = map(upper_limit/2, lower_limit, upper_limit, SERVOMIN, SERVOMAX);
      pwm.setPWM(number, 0, pulselen);
      delay(2000);
    }

    void zero(){
      uint16_t pulselen = map(lower_limit, lower_limit, upper_limit, SERVOMIN, SERVOMAX);
      pwm.setPWM(number, 0, pulselen);
      delay(2000);
    }
}; 
class Arm
{
   private: 
    // Data Members 
    String name;
    
  public:
    Servo servos[dof] = {Servo(0, 180, 75, ""), Servo(0, 180, 0, ""), Servo(0, 180, 0, ""),Servo(0, 180, 0, ""), Servo(0, 180, 0, ""), Servo(0, 180, 0, "")}; //Joint name [base/ elbow/ wrist/ claw]
 
    Arm()
    {
      for(int x = 0; x>dof ; x++){
        
        int limit = 0;
        
        if (x == 0){ 
          name = "base";
        }
        else if (x == dof) {
          name = "claw";
          limit = 75;
        } 
        else if (x == dof-1) {
          name = "wrist";
        }
        else{
          name = "elbow";
        }
        
        Servo y = Servo(0, 180, limit, name);
        servos[x] = y;
      }
    }
    
};

void setup() {
  Serial.begin(9600);
  
  inputString.reserve(200); // reserve 200 bytes for the inputString:
  
  Serial.println("8 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(10);
}


void loop() {
    // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
Servo s1 = Servo(0, 180, 75, "claw");
Servo s2 = Servo(1, 180, 0, "wrist");
Servo s3 = Servo(2, 180, 0, "roll");
Servo s4 = Servo(3, 180, 0, "elbow");
Servo s5 = Servo(4, 180, 0, "shoulder");
Servo s6 = Servo(5, 180, 0, "base");

s6.center();
s1.zero();
s2.zero(); 
s2.center();
s1.center();
s6.zero();

}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
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
