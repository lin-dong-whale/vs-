#pragma once
#include"utf-8tounicode.h"
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;


int DevideString(u16* dst, u16 * src, int len);

extern int a;
extern FILE* pSeg;
char segpath[];//ʹ�ô������jieba���ֵ䣬��ȥ10���ּ����ϵĴ�

