//www.elegoo.com
//2016.12.08

#include "pitches.h"


// notes in the melody:
int melody[] = {NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, 
				NOTE_B5, NOTE_B5, NOTE_B5, NOTE_D6, NOTE_G5, NOTE_A5, 
				NOTE_B5, 0, 0, 0, NOTE_C6, NOTE_C6, NOTE_C6, NOTE_C6, 
				NOTE_C6, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_A5, 
				NOTE_A5, NOTE_B5, NOTE_A5, NOTE_A5, NOTE_D6, 0, 0, 0, 
				NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, 
				NOTE_B5, NOTE_B5, NOTE_B5, NOTE_D6, NOTE_G5, NOTE_A5, 
				NOTE_B5, 0, 0, 0, NOTE_C6, NOTE_C6, NOTE_C6, NOTE_C6, 
				NOTE_C6, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_D6, 
				NOTE_D6, NOTE_C6, NOTE_B5, NOTE_A5, NOTE_A5};
int duration = 250;  // 200 miliseconds
 
void setup() {}
 
void loop() {  
    for (int thisNote = 0; thisNote < 65; thisNote++) {
	   // pin8 output the voice, every scale is 0.5 sencond
	   tone(11, melody[thisNote], duration);
	 
	   // Output the voice after several minutes
	   delay(250);
    }

    // restart after two seconds 
    delay(200);
}
