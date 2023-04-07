#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"
#include <Servo.h>

/**
  Connection
  Arduino    VoiceRecognitionModule
   2   ------->     TX
   3   ------->     RX
*/
VR myVR(2,3);    // 2:RX 3:TX, you can choose your favourite pins.

uint8_t records[7]; // save record
uint8_t buf[64];

int led = 13;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int servo4Pos = 0;

#define fuck    (0)
#define shit   (1) 
#define cock    (2)
#define dick   (3) 
#define mf    (4)
#define bitch   (5) 
#define puzzy    (6)

void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){
      Serial.write(buf[i]);
    }
    else{
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}

void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if(buf[0] == 0xFF){
    Serial.print("NONE");
  }
  else if(buf[0]&0x80){
    Serial.print("UG ");
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}

void setup()
{
  /** initialize */
  myVR.begin(9600);
  
  Serial.begin(115200);
  Serial.println("Elechouse Voice Recognition V3 Module\r\nControl Servos sample");
  
  servo1.attach(7);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);
  
  servo4.write(servo4Pos);
    
  if(myVR.clear() == 0){
    Serial.println("Recognizer cleared.");
  }else{
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while(1);
  }
  
  if(myVR.load((uint8_t)fuck) >= 0){
    Serial.println("fuck loaded");
  }
  
  if(myVR.load((uint8_t)shit) >= 0){
    Serial.println("shit loaded");
  }
  
  if(myVR.load((uint8_t)cock) >= 0){
    Serial.println("cock loaded");
  }
  
  if(myVR.load((uint8_t)dick) >= 0){
    Serial.println("dick loaded");
  }
  
  if(myVR.load((uint8_t)mf) >= 0){
    Serial.println("mf loaded");
  }
  
  if(myVR.load((uint8_t)bitch) >= 0){
    Serial.println("bitch loaded");
  }
  
  if(myVR.load((uint8_t)puzzy) >= 0){
    Serial.println("puzzy loaded");
  }
}

void moveServos(){
  /** move first 3 servos */
  for(int i=0; i<3; i++){
    if(i == 0){
      servo4.write(90);
      delay(400);
      servo4.write(-40);
      delay(1000);
      servo1.write(90);
      servo2.write(90);
      servo3.write(90);
    }else if(i == 1){
      servo4.write(90);
      delay(400);
      servo4.write(-40);
      delay(1000);
      servo1.write(90);
      servo2.write(90);
      servo3.write(90);
    }else{
      servo4.write(90);
      delay(400);
      servo4.write(-40);
      delay(1000);
      servo1.write(90);
      servo2.write(90);
      servo3.write(90);
    }
    delay(500);
    if(i == 0){
      servo4.write(-40);
      servo1.write(-90);
      servo2.write(-90);
      servo3.write(-90);
    }else if(i == 1){
      servo4.write(-40);
      servo1.write(-90);
      servo2.write(-90);
      servo3.write(-90);
    }else{
      servo4.write(-40);
      servo1.write(-90);
      servo2.write(-90);
      servo3.write(-90);
    }  
  }
  
  /** move fourth servo */
  delay(1000);
  servo4.write(90);
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
}

void loop()
{
  int ret;
  int curseCount = 0; // initialize curse count to 0
  ret = myVR.recognize(buf, 50);
  if(ret>0){
    switch(buf[1]){
      case fuck:
      case shit:
      case cock:
      case dick:
      case mf:
      case bitch:
      case puzzy:
        /** increment curse count and move servos */
        curseCount++;
        for(int i = 0; i < curseCount; i++){
          moveServos();
        }
        break;
      default:
        Serial.println("Record function undefined");
        break;
    }
    /** voice recognized */
  }
}
