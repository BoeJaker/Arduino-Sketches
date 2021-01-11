/*

 Main project file
 Processes user input via pins and buttons or interrupt sensors converts input into menu action i.e. forward, back, left, right ect
 Displays selected pattern and color on neopixel strings
 Best practice guide at bottom

*/


// Neopixel Setup
  #include <Adafruit_NeoPixel.h>
  #ifdef __AVR__
    #include <avr/power.h>
  #endif
  
  #define NUM_LEDS 17
  
  #define BRIGHTNESS 100
  
  #define LED_PIN 10 //23 for mega 10 for pro mini
  
  #define BRIGHTNESS_PIN 11
  
  #define BUTTON_A_PIN 12 // 9 is an interrupt 1/2
  
  #define BUTTON_B_PIN 13 // 10 is an interrupt 2/2
  

//  
//Static Variables
//--------------------
//

    Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

    byte wheel_pos = 0; //Color wheel position
  
    byte menu_position[] = {
     1,1
    };
    
    byte max_level[] = {
     4,4
    };
    byte level = 0;
    
    byte last_pos[3];
  
  
  //Options
  //--------------------
    byte color[] = {
      255, 255, 255
    };
    
    byte tint[] = {
      255, 0, 255
    };
    
    byte animation_speed = 3; //higher is slower
  
    int c, c2 = 0;

    byte start = 0;
    
union byte2array {
  byte array[3];
 uint32_t integer;
};


//
// Main Program
//================================================================================
/*LOOP DESCRIPTION
 * Check menu positon array state
 * Check input if selected
 * Advance animation 1 frame
 * Set leds accordingly
 * Check controls - if changed set menu pos or setting
 * Repeat
 */

  void setup() {
    Serial.begin(9600);

    strip.setBrightness(BRIGHTNESS);
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    rainbowCycle(animation_speed);
    animation_speed = 30;

    
}

void loop() {

  //Battery level check
  strip.setBrightness(BRIGHTNESS); // Set brightness
//  byte2array rgb_converter; // Original - this might break option3 below?
  
  // Main Menu 
  //==================================================================================================================
    switch (menu_position[0]){ 
      case 1: // Option 1: White - Adjustable color temperature & tint(todo)
        fullWhite(color_temperature);
        color_temperature = incrementer(color_temperature);
      break;
         
      case 2: // Option 2: Rainbow white - Casts a white light from rainbow colored pixels
        wheel_pos = rainbowCycleTwo(animation_speed, wheel_pos);
      break;

      case 3: // Option 3: Color Selector - Allows the user to select a static color
        wheel_pos = incrementer(wheel_pos);
        rgb_converter.integer = Wheel(wheel_pos);
        byte2array rgb_converter; // Alternative???
        colorWipe(strip.Color(rgb_converter.array[0],rgb_converter.array[1],rgb_converter.array[2]), 50);
        Serial.println(wheel_pos);
      break;
    };
    /*Option 4 - Features - Allows the user to overlay features with compatible colors i.e white, rainbow, color picker
        - Sound to light VU
        - Sound to light FFT
        - Motion to light PIR
        - Gesture to light
    */

    //Menu Navigation
    //================================
    copy(menu_position, last_pos, 3);
    //Button Menu
    checkButtons();
    //
}


// Function to copy 'len' elements from 'src' to 'dst'
void copy(byte* src, byte* dst, int len) {
    memcpy(dst, src, sizeof(src[0])*len);
}

// NEOPIXEL CONNECTION BEST PRACTICES (From: Adafruit Neopixel Uber Guide)
/*
 * Before connecting NeoPixels to any large power source (DC â€œwall wartâ€� or even a large battery), 
 * add a capacitor (1000 ÂµF, 6.3V or higher) across the + and â€“ terminals as shown above. 
 * The capacitor buffers sudden changes in the current drawn by the strip.
 * 
 * Place a 300 to 500 Ohm resistor between the Arduino data output pin and the input to the first NeoPixel. 
 * The resistor should be at the end of the wire closest to the NeoPixel(s), not the microcontroller. 
 * Some products already incorporate this resistorâ€¦if youâ€™re not sure, add oneâ€¦thereâ€™s no harm in doubling up!
 * 
 * Try to minimize the distance between the Arduino and first pixel, so the signal is clear.  
 * A meter or two is usually no problem. Much longer and things can become unreliable.
 * 
 * Avoid connecting NeoPixels to a live circuit. If you simply must, always connect ground first, 
 * then +5V, then data. Disconnect in the reverse order.
 * 
 * If powering the pixels with a separate supply, apply power to the pixels before applying 
 * power to the microcontroller.
 * 
 * Observe the same precautions as you would for any static-sensitive part; ground yourself before handling, etc.
 * 
 * NeoPixels powered by 5v require a 5V data signal. If using a 3.3V microcontroller you must use a logic level 
 * shifter such as a 74AHCT125 or 74HCT245. (If you are powering your NeoPixels with 3.7v like from a LiPoly, 
 * a 3.3v data signal is OK).
 * 
 * If your microcontroller and NeoPixels are powered from two different sources 
 * (e.g. separate batteries for each), there must be a ground connection between the two.
 */
