#ifndef GSM_H
#define GSM_H
#include"ss.h"

void GSM_SEND() {
  // put your main code here, to run repeatedly:

  ss.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  ss.println("AT+CMGS=\"+918668036852\"\r"); // Replace x with mobile number
  delay(1000);
  ss.println("ACCIDENT....");// The SMS text you want to send
  delay(100);
  ss.println("https://www.google.com/maps/@12.9461724,80.2449083,19.75z");
//  ss.print(lat3);
//  ss.print("13.1508°");
//  ss.print(",");
//  ss.print("16.03");
//  ss.print(lon3);
  ss.println((char)26);// ASCII code of CTRL+Z
  delay(3000);
}
#endif
