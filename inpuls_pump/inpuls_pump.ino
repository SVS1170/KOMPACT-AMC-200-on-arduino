#include "Bounce2.h"
int LED_PIN = 7;
int PULSE_PIN = 2;
int water_counter = 0; 
bool last_PULSE_PIN_State = false;
int val =1;
// Initiate Debouncer 
Bounce debouncer = Bounce();
void setup() {
  // Initialize digital pin 2 as an input with the internal pull-up (+5V) resistor enabled
  pinMode(PULSE_PIN, INPUT_PULLUP);
  // Attach PULSE_PIN for debouncing
  debouncer.attach(PULSE_PIN);
  debouncer.interval(50); // Ignore interval
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600, SERIAL_8N1);
}
void loop() { 
   if(digitalRead(3)){
      digitalWrite(6, LOW);
      digitalWrite(5, HIGH);
      //val = analogRead(A0); 
      val = map(analogRead(A0), 0, 725, 1, 10);
      debouncer.update();
//      Serial.println(val);
      // Read Reed Switch state
      int value = debouncer.read();
     
      // Now all processes are finished and we know exactly the state of the Reed Switch
      if ( value == LOW ) {
        //digitalWrite(LED_PIN, HIGH );
        if (last_PULSE_PIN_State == false)
        {
          water_counter++;
//          Serial.println("Water consumption: " + (String)(water_counter*1) + " l.");
        }
        last_PULSE_PIN_State = true;
      }
      else {
        //digitalWrite(LED_PIN, LOW);
        last_PULSE_PIN_State = false;
      }
       if (water_counter>=val){
         water_counter=0;
         digitalWrite(5, LOW);
         delay(100);
         digitalWrite(LED_PIN, HIGH );
         delay(2);
         digitalWrite(LED_PIN, LOW );
         }
    }
//    else {
//      digitalWrite(6, HIGH );    
//  }
  else {
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH );    
  }
}
