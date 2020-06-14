#include "Mouse.h"

#define MOUSE_MOVE_DELAY  1000
#define LED_DELAY         100
#define UP                1
#define DOWN              2
#define LEFT              3
#define RIGHT             4
#define DIAG_TLEFT        5
#define DIAG_TRIGHT       6
#define DIAG_BLEFT        7
#define DIAG_BRIGHT       8 

void blinkLED() {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(LED_DELAY);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(LED_DELAY);
}

void moveMouse(uint8_t dir, uint8_t repeat, uint8_t increments) {
  uint8_t rand_num;
  uint8_t rand_delay;
  for(int i = 0; i < repeat; i++) {
    for (int i = 0; i < increments; i++) {
        rand_num = random(0, 5);
        switch(dir) {
          case LEFT: 
            Mouse.move(-8, rand_num, 0);
            break;
           case RIGHT: 
            Mouse.move(8, rand_num, 0);
            break;
           case UP: 
            Mouse.move(rand_num, -8, 0);
            break;
           case DOWN: 
            Mouse.move(rand_num, 8, 0);
            break;
           case DIAG_TLEFT: 
            Mouse.move(-5 - rand_num, -5 + rand_num, 0);
            break;
           case DIAG_TRIGHT: 
            Mouse.move(5 + rand_num, -5 + rand_num, 0);
            break;
           case DIAG_BLEFT: 
            Mouse.move(-5 + rand_num, 5 - rand_num, 0);
            break;
           case DIAG_BRIGHT: 
            Mouse.move(5 + rand_num, 5 + rand_num, 0);
            break;
           default:
            //do nothing
            break;    
        }
       delay(3);
    }
  }
}

void setup() {
  // initialize mouse control:
  Mouse.begin();
  pinMode(LED_BUILTIN, OUTPUT);  
}

void randomGeneratorNums(uint16_t *r_time, uint8_t *r_inc, uint8_t *r_rep, uint8_t *mm) {
  *r_time = random(1000, 2000);
  *r_inc = random(50, 127);
  *r_rep = random(1, 3);
  *mm = random(UP, DIAG_BRIGHT); 
}

void loop() {
  randomSeed(analogRead(0));
  uint16_t rand_time;
  uint8_t rand_increments;
  uint8_t rand_repeats;
  uint8_t mm;

  randomGeneratorNums(&rand_time, &rand_increments, &rand_repeats, &mm);
  moveMouse(mm, rand_repeats, rand_increments);
  delay(rand_time); 
}
