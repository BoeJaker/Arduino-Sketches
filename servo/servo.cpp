#include "Arduino.h"
#include "servo.h"

//Initialisation
servo::servo(int number,  String joint, int upper_limit, int lower_limit)
{
	return
}

//Member Functions
void servo::move(int degrees) 
{
	uint16_t pulselen = map(degrees, 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(servonum, 0, pulselen);
}
void servo::center()
{
	uint16_t pulselen = map(90, 0, 180, SERVOMIN, SERVOMAX);
 	pwm.setPWM(servonum, 0, pulselen);
}
void servo::zero()
{
	 uint16_t pulselen = map(lower_limit, 0, 180, SERVOMIN, SERVOMAX);
     pwm.setPWM(servonum, 0, pulselen);
}

// class Servo 
// { 
//     // Access specifier 
//     public: 
  
//     // Data Members 
//     int number; //Sequence number from base 
//     String joint; //Joint name [base/ elbow/ wrist/ claw]
//     int upper_limit = 180; //Limit of movement
//     int lower_limit = 0;
    

//     // Member Functions() 
//     void move(int degrees) 
//     { 
//       uint16_t pulselen = map(degrees, 0, 180, SERVOMIN, SERVOMAX);
//       pwm.setPWM(servonum, 0, pulselen);
//     } 

//     void center()
//     {
//       uint16_t pulselen = map(90, 0, 180, SERVOMIN, SERVOMAX);
//       pwm.setPWM(servonum, 0, pulselen);
//     }

//     void zero(){
//       uint16_t pulselen = map(lower_limit, 0, 180, SERVOMIN, SERVOMAX);
//       pwm.setPWM(servonum, 0, pulselen);
//     }
// }; 
