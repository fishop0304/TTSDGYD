#include <Wire.h>
#include "Ultrasonic.h"
#define slave_address 0x3C

Ultrasonic ultrasonic(6);
byte x = 0x00;
void setup(){
  Wire.begin(slave_address); //I2C位址與連線設定，這裡設定為3號
  Wire.onReceive(receiveEvent); //當收到I2C訊號時，啟動的動作
  //Wire.onRequest(requestEvent); // register event
  Serial.begin(115200); 
  Serial.println("I2C Slave.05 started\n");
}

void loop(){
  long RangeInCentimeters;
  RangeInCentimeters = ultrasonic.MeasureInCentimeters();
  if((RangeInCentimeters < 200) && (RangeInCentimeters > 100 )){
    buzzer(RangeInCentimeters);
  }
  else if(RangeInCentimeters <= 100){
    buzzer(RangeInCentimeters);
  }
  else noTone(7);
    
  Serial.print(RangeInCentimeters);//0~400cm
  Serial.println(" cm");
  delay(100);
}
void buzzer(int nu){
  if(x == 49){
    tone(7, 2000);
    delay(nu);
    noTone(7);
  }
  else noTone(7);
}

void receiveEvent(int bytes) {
  if(Wire.available() != 0) {
    for(int i = 0; i< bytes; i++) {
      x = Wire.read();
      //Serial.print("Received: ");
      //Serial.print(x);
      //Serial.print("\n");
    }
  }
}

/*
void requestEvent() {
  Wire.write(0x68);
  Wire.write(0x71);
  Wire.write(0x73);
  
}*/
