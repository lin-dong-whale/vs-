#pragma once
#include"utf-8tounicode.h"
#define INPUTSIZE 120//存放输入语句的最大字节数，输入的最大Unicode码个数
#define UNICODESIZE 120//输入的最大Unicode码个数
#define POINTSIZE 120*4//点序输出数组的最大个数
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;
int HanZiTranslate();
int TranslateBaseOnTable(u8 InPut[], int InPutlen,int mode, u16 DevideUnicodeOutput[], int *Unicodelen, char PointOut[], int *Dotlen);