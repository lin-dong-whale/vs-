#pragma once
#include"utf-8tounicode.h"
#define INPUTSIZE 120//���������������ֽ�������������Unicode�����
#define UNICODESIZE 120//��������Unicode�����
#define POINTSIZE 120*4//������������������
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;
int HanZiTranslate();
int TranslateBaseOnTable(u8 InPut[], int InPutlen,int mode, u16 DevideUnicodeOutput[], int *Unicodelen, char PointOut[], int *Dotlen);