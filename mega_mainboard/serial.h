#ifndef __SERIAL_H__
#define __SERIAL_H__

#ifdef ARDUINO

//---Прием данных по последовательным портам

while (Serial.available()) {
  byte SerialChar = (byte)Serial.read();
  SerialIn[0][SerialInLen[0]] = SerialChar;
  SerialInLen[0]++;
  SerialRcv_ms[0] = millis();
}

while (Serial1.available()) {
  byte SerialChar = Serial1.read();
  SerialIn[1][SerialInLen[1]] = SerialChar;
  SerialInLen[1]++;
  SerialRcv_ms[1] = millis();
}

while (Serial2.available()) {
  byte SerialChar = (byte)Serial2.read();
  SerialIn[2][SerialInLen[2]] = SerialChar;
  SerialInLen[2]++;
  SerialRcv_ms[2] = millis();
}

while (Serial3.available()) {
  byte SerialChar = (byte)Serial3.read();
  SerialIn[3][SerialInLen[3]] = SerialChar;
  SerialInLen[3]++;
  SerialRcv_ms[3] = millis();
}


//-----------------------------------------------------------------------------------------------------Есть данные по 485 порту

for (int n = 0; n < 4; n++) { //перебор массива принятых пакетов (0,1,2,3)

  if (SerialInLen[n] > 0 && (millis() - SerialRcv_ms[n] > MS_SERIALRCV)) { //оттяжка на прием пакета целиком (для dibus = 100мс)

    Serial.print("<");
    if (SerialInLen[n] > 0 && SerialInLen[n] < 96) { //предположительно по размеру это пакет
      if(debug){
        Serial.print("COM");
        Serial.print(n);
        Serial.println(" is packet");
        for (int q = 0; q < SerialInLen[n]; q++) { //вывод принятого пакета на консоль
        Serial.print(SerialIn[n][q], HEX); Serial.print(" ");
        } Serial.println(" ");
      }

      if (n==1){ //пришли данные по COM1 порту
        if (SerialIn[1][0]==1 && SerialInLen[1]>3){ //первый байт 1 - значит данные с частотомера
          union {
            byte bytes[4];
            long value;
          } long_conv;
          
          long_conv.bytes[0]=SerialIn[1][1];
          long_conv.bytes[1]=SerialIn[1][2];
          long_conv.bytes[2]=SerialIn[1][3];
          long_conv.bytes[3]=SerialIn[1][4];
          F1 = long_conv.value;
          Serial.print("F1=");
          Serial.println(F1);
          
        }
      } //COM==1

      if (n==3){ //пришли данные по COM3 порту HMI

       if (SerialIn[3][2]==0x1A && SerialIn[3][1]==0x01) V1 = V1 - 100;  //V1 -10
       if (SerialIn[3][2]==0x18 && SerialIn[3][1]==0x01) V1 = V1 - 10;   //V1 -1
       if (SerialIn[3][2]==0x19 && SerialIn[3][1]==0x01) V1 = V1 + 10;   //V1 +1
       if (SerialIn[3][2]==0x1B && SerialIn[3][1]==0x01) V1 = V1 + 100;  //V1 +10
       if (V1<0) V1=0;
       
       DAC1.setValue(V1);
        
      } //COM3
      
    } //if length > <
    SerialInLen[n] = 0; //очистка буфера приема
  }
} //for (0..3)

#else
#error This example is only for use on Arduino.
#endif // ARDUINO

#endif
