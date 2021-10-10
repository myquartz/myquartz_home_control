//Sketch de test LED 7 thanh
#include <ShiftRegister74HC595.h>
// create shift register object (number of shift registers, data pin, clock pin, latch pin)
ShiftRegister74HC595 sr (1, 4, 6, 5); 

int number=0; // <--- Change it from 0 to 22

int value,digit1,digit2,digit3,digit4; 
//thu tu bit: dot G F E D C B A
uint8_t  numberB[] = {B11000000, //0
                      B11111001, //1 
                      B10100100, //2
                      B10110000, //3 
                      B10011001, //4
                      B10010010, //5
                      B10000010, //6
                      B11111000, //7
                      B10000000, //8
                      B10010000, //9
                      B10001000, //A
                      B10000011, //b
                      B10100111, //c
                      B10100001, //d
                      B10000110, //E
                      B10001110, //F
                     };

uint8_t  testbit[] = {B01111111, //0
                      B10111111, //1
                      B11011111, //2
                      B11101111, //3
                      B11110111, //4
                      B11111011, //5
                      B11111101, //6
                      B11111110, //7
                     };
void setup() {
  pinMode(13, OUTPUT);
  //Count from 0 to 'number' 
  //countUp();
  //Count from 'number' to 0
  //countDown();  // <--- Comment countUp and uncomment countDown
  //Blink 4 times all on and all off.
  blink();  
}

void loop() {
  countUp();
  digitalWrite(13, number % 2);
  delay(1000);
}

void countUp(){
    //Split number to digits:
    if(number==22) {
      blink();
      number=0;
    }
    else
      number++;
    
    if(number <= 7) {
      uint8_t test[2];
      test[0] = test[1] = testbit[number];
      sr.setAll(test);
    }
    else {
      int digit1=(number-7) % 16 ;
      //int digit2=((number-7) / 10) % 10 ;
      //Send them to 7 segment displays
      uint8_t numberToPrint[] = {numberB[digit1],numberB[digit1]};
      sr.setAll(numberToPrint);
    }
}

//Blink
void blink(){
  for(int i = 0; i<4; i++){
    sr.setAllLow(); // set all pins Low (off)
    delay(300);
    sr.setAllHigh(); // set all pins High (on)
    delay(300);
  }
}
