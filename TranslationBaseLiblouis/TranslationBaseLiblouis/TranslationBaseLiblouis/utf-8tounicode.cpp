
#include"utf-8tounicode.h"


unsigned int BytesOneUTF_Required(unsigned char str)
{
	unsigned int nBytes = 0;//UFT8可用1-6个字节编码,ASCII用一个字节  
	unsigned char chr = str;
	//如果不是ASCII码,应该是多字节符,计算字节数  
	if (chr >= 0x80)
	{
		if (chr >= 0xE0)
		{
			nBytes = 3;
		}
		else if (chr >= 0xC0)
		{
			nBytes = 2;
		}
		else
		{
			return 0;
		}
	}
	else
		nBytes = 1;
	return nBytes;
}


unsigned int UTF8toUni(const unsigned char* pInput, unsigned short* Unic, unsigned int utfbytes)
{
	// b1 表示UTF-8编码的pInput中的高字节, b2 表示次高字节, ...
	unsigned char b1, b2, b3;

	unsigned char* pOutput = (unsigned char*)Unic;

	*Unic = 0x0; // 把 *Unic 初始化为全零
	switch (utfbytes)
	{
	case 1:
		b1 = 0x00;
		b2 = *pInput;
		if (b2 <= 0x7F && b2 >= 0x00)
		{
			*pOutput = b2;
			*(pOutput + 1) = 0x00;
		}
		else
			return 0;
		break;
	case 2:
		b1 = *pInput;
		b2 = *(pInput + 1);
		if ((b2 & 0xC0) != 0x80)
			return 0;
		*pOutput = (b1 << 6) + (b2 & 0x3F);
		*(pOutput + 1) = (b1 >> 2) & 0x07;
		break;
	case 3:
		b1 = *pInput;
		b2 = *(pInput + 1);
		b3 = *(pInput + 2);
		if (((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80))
			return 0;
		*pOutput = (b2 << 6) + (b3 & 0x3F);
		*(pOutput + 1) = (b1 << 4) + ((b2 >> 2) & 0x0F);
		break;
	default:
		return 0;
		break;
	}
	return utfbytes;
}

int StringToUni(unsigned char* Inputbuf, unsigned short* Outputbuf, unsigned char len)
{
	int encodeType;
	unsigned int utfbytes_Required = 0;
	unsigned int utfbytes = 0;
	unsigned char cnt = 0;
	int index = 0;
	unsigned char* pInputbuf = Inputbuf;
	unsigned char* p = pInputbuf;
	unsigned short* pOutputbuf = Outputbuf;
	unsigned char ch;
	unsigned char buf_Toconvert[4] = { 0x00 };
	while (cnt < len)
	{
		ch = *pInputbuf;
		index = 0;
		utfbytes_Required = BytesOneUTF_Required(ch);
		utfbytes = utfbytes_Required;
		if (cnt + utfbytes > len)
			return -1;
		memset(buf_Toconvert, 0x00, sizeof(buf_Toconvert) / sizeof(char));
		while (utfbytes_Required)
		{
			p = pInputbuf;
			buf_Toconvert[index] = *(p + index);
			index++;
			utfbytes_Required--;
		}
		UTF8toUni(buf_Toconvert, pOutputbuf, utfbytes);
		pOutputbuf++;
		pInputbuf += utfbytes;

		cnt += utfbytes;
	}
	pInputbuf = NULL;
	p = NULL;
	pOutputbuf = NULL;
	return 1;
}
