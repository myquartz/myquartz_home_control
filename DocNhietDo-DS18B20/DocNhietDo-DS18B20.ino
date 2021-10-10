#include <OneWire.h>
#include <DallasTemperature.h>

#include <ShiftRegister74HC595.h>

#define ONE_WIRE_BUS 2
//onewire port 2 always
OneWire oneWire(ONE_WIRE_BUS);
//DallasTemperature read this
DallasTemperature sensors(&oneWire);

boolean blink = false;
int deviceCount = 0;
DeviceAddress Thermometer;

//7 bits, khong co dau cham
#define LED7_NUMBER 1
//8 bits, co dau cham
#define LED7_NUMBER_DOT 2
//level bar, 7-8 leds
#define LED_7LEVEL 3
#define LED_8LEVEL 4

// number and pointer shift register objectl
byte registerCount = 0;
ShiftRegister74HC595 *ledSR = null;

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

uint8_t  numberDot[] = {
  B01000000, //0.
  B01111001, //1. 
  B00100100, //2.
  B00110000, //3. 
  B00011001, //4.
  B00010010, //5.
  B00000011, //6.
  B01111000, //7.
  B00000000, //8.
  B00011000 //9.
};
                     
void setup(void)
{
  pinMode(3, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(3, LOW); 
  digitalWrite(13, LOW); 
  Serial.begin(9600);
  sensors.begin();
  deviceCount = sensors.getDeviceCount();
  Serial.print("Number of DS18B20 sensors: ");
  Serial.println(deviceCount);
  //(number of shift registers, data pin, clock pin, latch pin)
  ledSR = new ShiftRegister74HC595(2, 8, 9, 10); 
  displayLED7(deviceCount); 
  if(deviceCount>0) {
    listAddress();
  }
  delay(1000);
  sr.setAllHigh(); 
}

void listAddress() {
  Serial.println("Printing addresses...");
  for (int i = 0;  i < deviceCount;  i++)
  {
    Serial.print("Sensor ");
    Serial.print(i+1);
    Serial.print(": ");
    sensors.getAddress(Thermometer, i);
    printAddress(Thermometer);
  }
}

void printAddress(DeviceAddress deviceAddress)
{ 
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.print("0x");
    if (deviceAddress[i] < 0x10) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
    if (i < 7) Serial.print(", ");
  }
  Serial.println("");
}

void loop(void) { 
  if (Serial.available() > 0) {
    // read the incoming byte:
    char k = Serial.read();
    if(k == 'L') {
      //deviceCount = sensors.getDeviceCount();
      listAddress();
    }
  }
  float temp = 0;
  
  if(deviceCount == 0)
   blink = false;
  else {
    sensors.requestTemperatures();
    for(int i=0;i<deviceCount;i++) {
      temp = sensors.getTempCByIndex(i);
      if(i>0)
          Serial.print("\t");
      if(temp < 0) {
        Serial.print("-");
        blink = false;
        digitalWrite(3, LOW);
      }
      else {
        displayLED7(temp);
        Serial.print(temp);
        if(temp > 31)
          digitalWrite(3, HIGH); 
        else
          digitalWrite(3, LOW);
      }
    }
    Serial.println();    
  }
  
  //one second sleep
  blink = !blink;
  digitalWrite(13, blink ? HIGH:LOW);
  delay(900);
}

void showNumberToLED7(int number) {
    if(sr == null || registerCount == 0)
      return;
    uint8_t numberToPrint[registerCount];
    int digit = 0;
    for(int i=0;i<registerCount;i++) {
      digit = number % 10;
      number /= 10;
      numberToPrint[i] = numberB[digit2];
    }
    
    //Send them to 7 segment displays
    uint8_t numberToPrint[]= {numberB[digit2],numberB[digit1]};
    ledSR->setAll(numberToPrint); 
}

