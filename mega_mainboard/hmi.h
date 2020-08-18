#ifndef __HMI_H__
#define __HMI_H__

#ifdef ARDUINO

//---Вывод данных на HMI панель
if ((millis() - HmiUpdate_ms > MS_HMIUPDATE)) {
  Serial3.print("f1.txt=\"");
  Serial3.print(F1);
  Serial3.print("\"");
  Serial3.write(Hmi_fin,3);

  Serial3.print("f2.txt=\"");
  Serial3.print(F2);
  Serial3.print("\"");
  Serial3.write(Hmi_fin,3);

  Serial3.print("v1.txt=\"");
  Serial3.print(V1);
  Serial3.print("\"");
  Serial3.write(Hmi_fin,3);

  Serial3.print("v2.txt=\"");
  Serial3.print(V2);
  Serial3.print("\"");
  Serial3.write(Hmi_fin,3);
  
  Serial3.print("ip.txt=\"");
  Serial3.print(IpAddr);
  Serial3.print("\"");
  Serial3.write(Hmi_fin,3);

  HmiUpdate_ms = millis();
} //HMIUPDATE

#else
#error This example is only for use on Arduino.
#endif // ARDUINO

#endif
