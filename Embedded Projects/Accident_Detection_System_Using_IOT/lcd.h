#ifndef LCD_H
#define LCD_H
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

//byte iot[] = {
//  B00100,
//  B00100,
//  B01110,
//  B10101,
//  B00100,
//  B00100,
//  B00100,
//  B00100
//};
//
//byte car[] = {
//  B00000,
//  B11111,
//  B11111,
//  B11111,
//  B11111,
//  B11111,
//  B11111,
//  B01010
//};
//byte guard[] = {
//  B01110,
//  B01110,
//  B01110,
//  B01110,
//  B01110,
//  B01110,
//  B01110,
//  B01110
//};
//byte train[] = {
//  B11000,
//  B11000,
//  B11000,
//  B11000,
//  B11111,
//  B11111,
//  B11111,
//  B11111
//};
//byte train1[] = {
//  B11111,
//  B11111,
//  B11111,
//  B11111,
//  B11111,
//  B11111,
//  B11111,
//  B11111
//};
#endif