int latchPin = 5;  // Latch pin of 74HC595 is connected to Digital pin 5
int clockPin = 6; // Clock pin of 74HC595 is connected to Digital pin 6
int dataPin = 4;  // Data pin of 74HC595 is connected to Digital pin 4

int leds = 0;    // Variable to hold the pattern of which LEDs are currently turned on or off

/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
void setup() 
{
  pinMode(13, OUTPUT);

  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  pinMode(3, OUTPUT);  
delay(50);
  digitalWrite(3, LOW);
  delay(50);
  digitalWrite(3, HIGH);
}

/*
 * loop() - this function runs over and over again
 */
void loop() 
{
  
  /*leds = B01000100;
  updateShiftRegister(leds);
  delay(1000);
  leds = B00000001;
  updateShiftRegister(leds);
  delay(1000);
  leds = B00000010;
  updateShiftRegister(leds);
  delay(5000);
  */
  leds = 0;
  for (int i = 0; i < 9; i++) // Turn all the LEDs ON one by one.
  {
    //if(i<4)
    //bitClear(leds, i);    // Set the bit that controls that LED in the variable 'leds'
    //else
    bitSet(leds, i);
    updateShiftRegister(leds);
    bitClear(leds, i);
    delay(500);
    digitalWrite(13, i % 2 == 0?HIGH:LOW);
  }
  updateShiftRegister(0xff);
  delay(5000);
  /*updateShiftRegister(leds++);
  digitalWrite(13, leds % 2 == 0?HIGH:LOW);*/
}

/*
 * updateShiftRegister() - This function sets the latchPin to low, then calls the Arduino function 'shiftOut' to shift out contents of variable 'leds' in the shift register before putting the 'latchPin' high again.
 */
void updateShiftRegister(int l)
{
   digitalWrite(latchPin, HIGH);
   //digitalWrite(latchPin, LOW);
   //delay(10);
   shiftOut(dataPin, clockPin, MSBFIRST, l);
   /*for(int b = 7;b>=0;b--) {
    //digitalWrite(clockPin, LOW);
    //delay(10);
    digitalWrite(dataPin, bitRead(leds,b) ? HIGH : LOW);
    delay(10);
    digitalWrite(clockPin, HIGH);
    delay(10);
    digitalWrite(clockPin, LOW);
   }*/
   //delay(10);
   digitalWrite(latchPin, LOW);
   //delay(500);
   //digitalWrite(latchPin, HIGH);
}
