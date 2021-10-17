/*
 Meeting keyboard v0.1
 by Tran Thach Anh 2021
 
 * Currently support Google Meet only.
 */

//Pro micro using RXLED
#define ST_LED 17
// 6 buttons
#define BTN_CNT 6
#define BTN_1 0
#define BTN_2 1
#define BTN_3 2
#define BTN_4 3

byte lastPins[BTN_CNT];
boolean macos = false;
boolean debug = false;

long cam_delay = 0;

void setup() {
  //configure pins, config as internal pull-up resistor
  for(int i=0;i<BTN_CNT;i++)
    pinMode(2+i, INPUT_PULLUP);
  pinMode(ST_LED, OUTPUT); 
  digitalWrite(ST_LED, LOW);
  //push 2 and 3 at the same time to reconfig
  byte r2 = digitalRead(2);
  byte r3 = digitalRead(3);
  boolean b = false;
  if(r2 == LOW && r3 == LOW) {
    //Serial.println("Sleep 10s to reconfig...");
    for (int j = 0;j<10;j++) {
      delay(1000);
      digitalWrite(ST_LED, b ? LOW : HIGH);
      b != b;
      byte r4 = digitalRead(4);
      if(r4 == LOW && r2 == HIGH && r3 == HIGH) {
        //macos mode
        macos = true;
        break;
      }
      if (j>6 && r2 == HIGH && r3 == HIGH) {
          //start serial connection
          Serial.begin(9600);
          debug = true;
      }
    }
  }
  if(!debug)
    Keyboard.begin();
}

void loop(){
  //read the pushbutton value into a variable
  for(int i =0; i<BTN_CNT; i++) {
    int sensorVal = digitalRead(2+i);
    if(sensorVal == lastPins[i]) {
      delay(10);
      if(cam_delay > 0)
        cam_delay--;
      continue;
    }
     
    if(debug) {
      //print out the value of the pushbutton
      Serial.print("Change pin[");
      Serial.print(2+i);
      Serial.print("]: ");
      Serial.println(sensorVal);
    }
    lastPins[i] = sensorVal;
    
    // Keep in mind the pullup means the pushbutton's
    // logic is inverted. It goes HIGH when it's open,
    if (sensorVal == HIGH) {
      digitalWrite(ST_LED, LOW);
    } 
    else {
      digitalWrite(ST_LED, HIGH);
      if(!debug) {
       switch(i) {
        case BTN_1: //mute mic
          if(macos) {
            Keyboard.press(KEY_LEFT_GUI);
            delay(10);
            Keyboard.press('d');
            delay(100);
            Keyboard.releaseAll();
          }
          else {
            Keyboard.press(KEY_LEFT_CTRL);
            delay(10);
            Keyboard.press('d');
            delay(100);
            Keyboard.releaseAll();
          }
        break;
        case BTN_2: //camera on/off
          if(cam_delay > 0)
            return;
          cam_delay = 1000;//50 seconds delay
          if(macos) {
            Keyboard.press(KEY_LEFT_GUI);
            delay(10);
            Keyboard.press('e');
            delay(100);
            Keyboard.releaseAll();
          }
          else {
            Keyboard.press(KEY_LEFT_CTRL);
            delay(10);
            Keyboard.press('e');
            delay(100);
            Keyboard.releaseAll();
          }
        break;
        case BTN_3: //switch tab
            Keyboard.press(KEY_LEFT_CTRL);
            delay(10);
            Keyboard.press(KEY_TAB);
            delay(100);
            Keyboard.releaseAll();
        break;
        case BTN_4: //switch app
          Keyboard.press(KEY_ESC);
          delay(100);
          Keyboard.release(KEY_ESC);
          delay(10);
          if(macos) {
            Keyboard.press(KEY_LEFT_GUI);
            delay(10);
            Keyboard.press(KEY_TAB);
            delay(100);
            Keyboard.releaseAll();
          }
          else {
            Keyboard.press(KEY_LEFT_ALT);
            delay(10);
            Keyboard.press(KEY_TAB);
            delay(100);
            Keyboard.releaseAll();
          }
        break;
       }
      }
    }
  }
}



