/*
  Moosetimer.
  
  Work break timer based on an arduino board.
  
  When turned on, a countdown will start, based on the settings in the CONFIGURATION block. 
  
  The default is a 25 minute time period, with 5 minutes for each of the 5 LEDs. The "active" LED (for the current time period)
  will blink slowly.

  At the end of the time period, a buzzer will sound and all LEDS will stay lit.
  
  Pressing the button again at any time will reset the counter. 
  
  by Matthew Christensen 2014
  
  This software is in the public domain. Use as you wish.
*/

#define __ASSERT_USE_STDERR
 
#include <assert.h>
 

// CONFIGURATION

// Amount of time to wait before advancing each LED
unsigned long LED_INTERVAL_IN_MILLIS=300000;

// How many timing LEDs are we going to use?
int NUMBER_OF_LEDS = 5;

// Pins LED_BASE -> LED_BASE + NUMBER_OF_LEDS must be connected to the LEDs. In the schematic,
// this consists of D8 through D12
int LED_BASE = 8;

int BUTTON_PIN = 5; // Schematic has button attached to D5
int SPEAKER_PIN = 4; // Positive lead of speaker, schematic has on D4

//Interval (in ms) between on/off of blinking led
unsigned long BLINK_INTERVAL = 1000;

// Rough frequency (in Hz) of buzzer sound
int BUZZER_FREQUENCY = 440;

// STATE VARIABLES
int current_LED = 0; // Index of thec urrently selected LED
int button_pressed = 0; // Set to 1 when the button has been pressed
unsigned long last_millis = 0; // Used to handle delay on blinking LED
int last_state = LOW; // Used to handle delay on blinking LED
unsigned long next_led_at = 0 ;// Used to decide when to advance to next LED. Stores a millisecons value.
int  timer_active=0; // When 1, indicates the timer is currently active and that we should check for advancing LED.

int should_blink = 0; // If 1, we should blink the current LED
int buzzer_on = 1; // If 1, buzzer is currently active and should sound

// Map an LED index to a pin. Note this is zero-based
int mapLEDtoPin(int led_index) {
  return LED_BASE+led_index;
}

// Start (or restart) the timer
void startTimer() {
  current_LED = 0;
  should_blink = 1;
  last_state = LOW;
  button_pressed=0;
  timer_active=1;
  last_millis=millis();

  // Turn off the LEDs if currently on
  for (int i = 0; i<NUMBER_OF_LEDS; i++) { 
    digitalWrite(mapLEDtoPin(i),LOW);
  }
  
  setCurrentLED(0);
}

// Set the current LED to next_led_idx (zero-based). Light any previous LEDs
void setCurrentLED(int next_led_idx)
{
  assert(next_led_idx < NUMBER_OF_LEDS);
  next_led_at = millis() + LED_INTERVAL_IN_MILLIS;

  current_LED = next_led_idx;
  for (int i = 0; i <= next_led_idx; i++) {
    digitalWrite(mapLEDtoPin(i), HIGH);
  }
  
}

// Increment to our next LED, wrapping around to 0 if at end
void incrementLED() {
 if (current_LED+1 >= NUMBER_OF_LEDS) {
   should_blink = 0;
   setCurrentLED(current_LED);
   tone(SPEAKER_PIN,BUZZER_FREQUENCY,500);
   timer_active=0;
 } else {
   setCurrentLED(current_LED+1);
 }  
}

// the setup routine runs once when you press reset:
void setup() {                
  // Serial used for debugging
  Serial.begin(9600);
  
  // initialize the digital pin as an output.
  for (int i = 0; i<NUMBER_OF_LEDS; i++) { 
     pinMode(LED_BASE+i, OUTPUT); 
  }
  
  pinMode(BUTTON_PIN,INPUT);
  
  // Start the timer
  startTimer(); 

  setCurrentLED(0);
}

void checkButton() {
  // The first time the button is pressed, increment the LED. After that,  wait for next press for further action
  if (digitalRead(BUTTON_PIN) == HIGH) {
    if (button_pressed == 0) {
      button_pressed=1;
      startTimer();
      delay(500); // Wait 500 millisecond before continuing to debounce reliably
    }
  } else {
    button_pressed = 0;
  }
}

// Blink the active LED on/off, based on a stored time
void blinkLED() {
    unsigned long current_millis = millis();
    if (current_millis > last_millis+BLINK_INTERVAL) {
       if (last_state == LOW) {
         last_state = HIGH;
       } else {
         last_state = LOW;
       }
       digitalWrite(mapLEDtoPin(current_LED), last_state);   // toggle the LED
       last_millis = current_millis;
    }
}

// Call to dump debug info about the current state of the timing loop.
void debugTiming() {
    Serial.print("Target time: ");
    Serial.print(next_led_at);
    Serial.print(", current time: ");
    Serial.print(millis());
    Serial.print(", offset: ");
    Serial.println(LED_INTERVAL_IN_MILLIS);
}

// Check if we need to move to the next LED
void checkLEDs() {
  unsigned long current_millis = millis();
  
  if (current_millis > next_led_at) {
     incrementLED();
  }
}

// the loop routine runs over and over again forever:
void loop() {
  checkButton();
  
  // Blink timing LED with no 
  if (should_blink == 1) {
    blinkLED();
  }
  
  // Check for LED advance
  if (timer_active == 1) {
    checkLEDs();
  }
}

