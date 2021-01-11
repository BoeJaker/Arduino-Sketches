/*************************************************** 
  Robot Arm w/ i2c, Wire.h & Adafruit PWM.

 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// Servo names/numbers
// #define BAS_SERVO 0
// #define SHL_SERVO 1
// #define ELB_SERVO 2
// #define WRI_SERVO 3
// #define WRO_SERVO 4
// #define GRI_SERVO 5

//Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  110 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  1100 // this is the 'maximum' pulse length count (out of 4096)

// Degrees of freedom that the arm has
uint8_t dof = 6;

// Servo sequence counter
uint8_t servonum = 0;

class Servo 
{ 
    // Access specifier 
    private: 
      // Data Members 
      int number; //Sequence number from base 
      String joint; //Joint name [base/ elbow/ wrist/ claw]
      int upper_limit = 180; //Limit of movement
      int lower_limit = 0;
      
    public:
      Servo(int number, String joint, int upper_limit, int lower_limit)
      {
        this->number = number;
        this->joint = joint;
        this->upper_limit = upper_limit;
        this->lower_limit = lower_limit;
      }

      // Member Functions() 
      void move(int degrees) 
      { 
        uint16_t pulselen = map(degrees, 0, 180, SERVOMIN, SERVOMAX);
        pwm.setPWM(servonum, 0, pulselen);
      } 

      void center()
      {
        uint16_t pulselen = map(90, 0, 180, SERVOMIN, SERVOMAX);
        pwm.setPWM(servonum, 0, pulselen);
      }

      void zero(){
        uint16_t pulselen = map(lower_limit, 0, 180, SERVOMIN, SERVOMAX);
        pwm.setPWM(servonum, 0, pulselen);
      }
}; 

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(10);

  while( servonum <= dof){
    int degrees = 0;
    uint16_t pulselen = map(degrees, 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(servonum, 0, pulselen);
    servonum++;
    delay(500);
  } 
}

// you can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000000;  // convert to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

void loop() {
  while( servonum <= dof){
    int degrees = 0;
    uint16_t pulselen = map(degrees, 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(servonum, 0, pulselen);
    servonum++;
    delay(500);
  } 
//  if (servonum > dof) servonum = 0;
//  
//  // Drive each servo one at a time
//  Serial.println(servonum);
//  
//  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
//    pwm.setPWM(servonum, 180, pulselen);
//  }
//
//  delay(500);
//  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
//    pwm.setPWM(servonum, 0, pulselen);
//  }
//
//  delay(500);
//
//  int degrees = 0;
//  uint16_t pulselen = map(degrees, 0, 180, SERVOMIN, SERVOMAX);
//  pwm.setPWM(servonum, 0, pulselen);
//
//  delay(500);
//  
//  servonum ++;
//  if (servonum > dof) servonum = 0;
}
