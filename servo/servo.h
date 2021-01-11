#ifndef servo_h
#define servo_h


#include "Arduino.h"
class Servo 
{ 
    // Access specifier 
    public: 
    // Initializer & Data Members 
    servo(int number,  String joint, int upper_limit, int lower_limit);
    int servonum = 0;
    // Member Functions() 
    void move(int degrees); 
    void center();
    void zero();
}; 

#endif