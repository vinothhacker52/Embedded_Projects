#include "initial.h"
#include "lcd.h"
#include "gsm.h"
#include "ss.h"
//#include "gps.h"

void serialEvent();

int loop_count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ss.begin(9600);
  dht.dht_read(DHTPIN);
  lcd.begin();
  lcd.backlight();
  //gps();

  //attachInterrupt(digitalPinToInterrupt(CRASH_SENSOR), crash_ISR, RISING);
  pinMode(GAS_SENSOR, INPUT);
  pinMode(CRASH_SENSOR, INPUT);
  pinMode(ESP_PIN, OUTPUT);
  digitalWrite(ESP_PIN, LOW);
  //  if (digitalRead(8) == 0)
  //    gps();
  lcd.setCursor(3, 0);
  lcd.print("BLACK BOX");
  lcd.setCursor(5, 1);
  lcd.print("SYSTEM");
  delay(1000);

  while (!Serial) {
    //h/ wait for serial port to connect. Needed for native USB port only
    ;
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
}

void loop() {
  // put your main code here, to run repeatedly:

  //  if (digitalRead(CRASH_SENSOR) == 1) {
  //    //    CRASH_FLAG = false;
  //    while (inchar == 'X')
  //    {
  //      serialEvent();
  //      lcd.clear();
  //      lcd.setCursor(0, 1);
  //      lcd.print("WAITING FOR DATA");
  //
  //      if (python_accident == true)
  //      {
  //        CRASH_FLAG = false;
  //        python_accident = false;
  //        Serial.println("ACCIDENT");
  //        lcd.clear();
  //        lcd.setCursor(4, 1);
  //        lcd.print("ACCIDENT");
  //        GSM_SEND();
  //        IOT("*ACCIDENT#");
  //        Serial.println("GSM SEND");
  //      }
  //      delay(1000);
  //    }
  //  }

  //int a = digitalRead(CRASH_SENSOR);
  //Serial.print("vib" + String(a));
  Serial.println(analogRead(A3));

  if (analogRead(A3) > 200) {
    //CRASH_FLAG = false;
    Serial.println("ACCIDENT");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ACCIDENT DETECT");
    lcd.setCursor(2, 1);
    lcd.print("SENDING INFO");
    GSM_SEND();
    IOT("*ACCIDENT#");
    Serial.println("GSM SEND");
  }

  lcd.clear();
  dht.dht_read(DHTPIN);
  t = dht.temperature;
  Serial.println(t);
  lcd.setCursor(4, 0);
  lcd.print("T:");
  lcd.print(t);

  GAS_DATA = digitalRead(GAS_SENSOR);
  Serial.println(GAS_DATA);
  lcd.setCursor(10, 0);
  lcd.print("G:");
  lcd.print(GAS_DATA);

  if (GAS_DATA == 0) {
    lcd.setCursor(3, 1);
    lcd.print("Gas detected");
  }
  else {
    lcd.setCursor(1, 1);
    lcd.print("No Gas detected");
  }

  IOT("@" + String(t) + "#" + "$" + String(GAS_DATA) + "#");
  SD_CARD_WRITE(String(GAS_DATA), String(t));













}

//void crash_ISR() {
//  CRASH_FLAG = true;
//}

void IOT(String s) {
  for (int i = 0; i < s.length(); i++) {
    Serial.write(s[i]);
  }
  delay(3000);
}

//void serialEvent()
//{
//  if (Serial.available() > 0)
//  {
//    inchar = Serial.read();
//    Serial.println(inchar);
//
//    if (inchar == 'A') {
//      Serial.println("receive A");
//      python_accident = true;
//    }
//  }
//}

void SD_CARD_WRITE(String s1, String s2) {

  myFile = SD.open("data.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to data.txt...");
    myFile.println();
    myFile.print("Gas: ");
    myFile.print(s1);
    myFile.print("\t");
    myFile.print("temp: ");
    myFile.print(s2);
    myFile.close();
    Serial.println("done.");
  }
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
