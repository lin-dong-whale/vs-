#pragma once
#include <iostream>
#include<stdio.h>
#include<string.h>

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

unsigned int BytesOneUTF_Required(unsigned char str);
unsigned int UTF8toUni(const unsigned char* pInput, unsigned short* Unic, unsigned int utfbytes);
int StringToUni(unsigned char* Inputbuf, unsigned short* Outputbuf, unsigned char len);
int htoi(char s[]);