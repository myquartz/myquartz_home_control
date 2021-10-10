
byte counter = 0;
   
int encoder0PinA = 3;
int encoder0PinB = 4;
volatile int icount = 0;
volatile int encoder0Pos = 0;
int lastPos = 0; 
byte encoder0PinALast = LOW;
   
void setup() {
  for(byte i=5;i<=12;i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
 
  pinMode(13, OUTPUT);
   
  pinMode (encoder0PinA, INPUT);
  //digitalWrite(encoder0PinA, HIGH);//pull up resister
  pinMode (encoder0PinB, INPUT);
  //digitalWrite(encoder0PinB, HIGH);//pull up resister
  
  attachInterrupt(digitalPinToInterrupt(2), doReset, RISING);
  attachInterrupt(digitalPinToInterrupt(3), doEncoder, CHANGE);
  
  Serial.begin (38400);
  Serial.println("BEGIN");
  Serial.println();
}

void loop() {
  /*int a = digitalRead(encoder0PinA);
  int b = digitalRead(encoder0PinB);
  if (encoder0PinALast == LOW && a == HIGH) {
    if (b == LOW) {
      encoder0Pos--;
    } else {
      encoder0Pos++;
    }
    Serial.print (encoder0Pos);
    Serial.print (" ");
    Serial.print (a);
    Serial.print (" ");
    Serial.println (b);
  }
  encoder0PinALast = a;*/
  noInterrupts();
  int p = encoder0Pos;
  interrupts();
  if(lastPos != p) {
    /*Serial.print (icount);
    Serial.print (": ");
    Serial.print (p);
    Serial.print (" ");*/
    Serial.println (lastPos);
    lastPos = p;
  int pin = p/4;
  for(byte i=5;i<=12;i++) 
    if(pin < 5 || pin > 12)
      digitalWrite(i,pin > 12 ? HIGH:LOW);
    else
      digitalWrite(i, pin == i ? LOW : HIGH);
  }
  
  digitalWrite(13,counter % 32 == 0?HIGH:LOW);
  counter++;
  if(counter>=128) {
    counter = 0;
  }
  delay(40);
}

void doReset() {
  encoder0Pos = 0;
}

void doEncoder() {
  //icount++;
  delayMicroseconds(50);
  byte a = digitalRead(encoder0PinA);
  byte b = digitalRead(encoder0PinB);
  delayMicroseconds(50);
  byte a2 = digitalRead(encoder0PinA);
  byte b2 = digitalRead(encoder0PinB);
  if(a != a2 || b != b2) {//inconsistent data, re-read it
    delayMicroseconds(50);
    byte a3 = digitalRead(encoder0PinA);
    byte b3 = digitalRead(encoder0PinB);
    if(a2 == a3)
      a = a2;
    if(b2 == b3)
      b = b2;
  }
  /*Serial.print (icount);
  Serial.print (": ");
  Serial.print (a);
  Serial.print (" ");
  Serial.print (b);
  Serial.print (" => ");
  Serial.println (encoder0Pos);*/
  if (a == b) {
      encoder0Pos--;
    } else {
      encoder0Pos++;
    }
  /*byte a = digitalRead(encoder0PinA);
  byte b = digitalRead(encoder0PinB);
  if(a != encoder0PinALast) {
    if (HIGH == b) {
      encoder0Pos++;
    } else {
      encoder0Pos--;
    }
    encoder0PinALast = a;
  }*/
}

