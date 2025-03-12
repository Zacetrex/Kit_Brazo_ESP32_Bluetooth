// Producto de ZACETREX TECHNOLOGIES S.A.C
// Este código se hizo con fin de compartirlo con la comunidad y tiene fines educativos

#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#include <ESP32Servo.h>
Servo servoA,servoB,servoC,servoD;

#define SERV_UPDWSTEP 1

uint8_t TIMEDELSER = 50;

uint8_t cmd=0;
uint8_t rcvAct=0;
uint8_t rcvAnt=0;
byte cmdBT[2];

void servRst(){
servoA.write(90);delay(500);
servoB.write(90);delay(500);
servoC.write(90);delay(500);
servoD.write(90);delay(500);
}

void printInfoSrv(){
Serial.println(servoA.read());
Serial.println(servoB.read());
Serial.println(servoC.read());
Serial.println(servoD.read());
}

void setup() {
servoA.attach(33); // Garra
servoB.attach(27); // Servo izquierdo
servoC.attach(26); // Servo derecho
servoD.attach(25); // Servo base
servRst();
Serial.begin(115200);
SerialBT.begin("ZACETREX_BRAZO");
}

void loop() {
  if(SerialBT.available()){
  rcvAct=SerialBT.read();
    if(rcvAct!=rcvAnt){
    rcvAnt=rcvAct;
    cmd= rcvAct;
    Serial.write(cmd);
    }    
  }
    switch(cmd){
    case 21:
      if(SerialBT.readBytes(cmdBT,2)==2){
        if(!cmdBT[1])TIMEDELSER=cmdBT[0];
      cmd=1;
      }
    break;
    
    case 'A': delay(TIMEDELSER);  if(servoA.read()<114) servoA.write(servoA.read()+SERV_UPDWSTEP);  break;
    case 'a': delay(TIMEDELSER);  if(servoA.read()>80)  servoA.write(servoA.read()-SERV_UPDWSTEP);  break;
    case 'B': delay(TIMEDELSER);  if(servoB.read()<140) servoB.write(servoB.read()+SERV_UPDWSTEP);  break;
    case 'b': delay(TIMEDELSER);  if(servoB.read()>78)  servoB.write(servoB.read()-SERV_UPDWSTEP);  break;
    case 'C': delay(TIMEDELSER);  if(servoC.read()<160) servoC.write(servoC.read()+SERV_UPDWSTEP);  break;
    case 'c': delay(TIMEDELSER);  if(servoC.read()>80)  servoC.write(servoC.read()-SERV_UPDWSTEP);  break;
    case 'D': delay(TIMEDELSER);  if(servoD.read()<170) servoD.write(servoD.read()+SERV_UPDWSTEP);  break;
    case 'd': delay(TIMEDELSER);  if(servoD.read()>10)  servoD.write(servoD.read()-SERV_UPDWSTEP);  break;
    case 'R': printInfoSrv(); cmd=1; break;
    }  
}
