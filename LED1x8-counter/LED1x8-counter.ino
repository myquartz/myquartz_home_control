
byte counter = 0;

void setup() {
  for(byte i=5;i<=12;i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  
  pinMode(13, OUTPUT);
  Serial.begin(19200);
}

void loop() {
  int voltage = analogRead(A0);
  int pin=0;
  
  if(voltage < 128 || voltage >= 640)
    pin = 0; //out of range
  else pin = ((voltage-128)/64)+5;
  for(byte i=5;i<=12;i++) 
    if(pin == 0)
      //digitalWrite(i, (voltage<128 && i <= 8 || voltage>=640 && i > 8) ? LOW : HIGH);
      digitalWrite(i, voltage<128 ? HIGH: LOW);
    else
      digitalWrite(i, pin >= i ? LOW : HIGH);
  digitalWrite(13,counter % 4 == 0?HIGH:LOW);
  counter++;
  if(counter>=8) {
    counter = 0;
    Serial.print(voltage);
    Serial.print(",");
    Serial.println(pin);
  }
  delay(100);
}
