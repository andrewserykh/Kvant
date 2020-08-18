/*
  KVANT v.1.0

  COM0 - Debug
  COM1 - FREQ
  COM2 - 
  COM3 - HMI

 */

#include <SPI.h>
//#include <Ethernet.h>
#include <EEPROM.h>
#include "converter.h"
#include "Wire.h"
#include "MCP4725.h"

#define   MS_SERIALRCV    100   //задержка ожидания конца пакета по порту
#define   MS_HMIUPDATE    1000  //обновление данных на HMI

bool debug = true;  //вывод в Serial отладочной информации

void(* resetArduino) (void) = 0;  //необходимо для перезагрузки

byte SerialIn[7][64]; //буфер приема по serial портам
byte SerialInLen[7]; //заполнение буфера
long SerialRcv_ms[7]; //прием по последовательному порту (отсрочка на прием всего пакета)

long HmiUpdate_ms;
byte Hmi_fin[] = {0xff, 0xff, 0xff}; //добивка для приема экраном команды


String IpAddr = "192.168.0.8";
long F1,F2;
long V1,V2;

MCP4725 DAC1(0x60);  // 0x62 or 0x63MCP4725 DAC(0x62);  // 0x62 or 0x63

void setup() {
  Serial.begin(115200);
  if(debug) Serial.print("Initialization...");

  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(9600);
  DAC1.begin();
  if(debug) Serial.println("ok.");
}

void loop() {

  while(1){

    #include "serial.h"; //прием данных по последовательному порту
    #include "hmi.h"; //вывод данных на hmi панель


  }
}
