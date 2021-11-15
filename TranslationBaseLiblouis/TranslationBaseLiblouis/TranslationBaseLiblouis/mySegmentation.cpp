#include "stdio.h"
#include "string.h"
//#include "GbkToUnicode.h"
#include "malloc.h"
#include"mySegmentation.h"

#define isChCharacter(a) (((a >= 0x4E00 && a <= 0x9FFF) || (a >= 0x3400 && a <= 0x4DBF) || (a >= 0xF900 && a <= 0xFAFF)) ? 1 : 0)
#define WORD_ITEM_LEN	32
#define WORD_ITEM_MAXCNT	9
#if 0
#define TWO_CNT			179296
#define THREE_CNT		147828
#define FOUR_CNT		188628
#define FIVE_CNT		14620
#define SIX_CNT			7567
#define SEVEN_CNT		8138
#define EIGHT_CNT		1669
#define NINE_CNT		641
char segpath[] = ".\\Debug\\FenciTable.txt";//使用原来的字典

#else
#define TWO_CNT			114128
#define THREE_CNT		131337
#define FOUR_CNT		84894
#define FIVE_CNT		3563
#define SIX_CNT			1641
#define SEVEN_CNT		918
#define EIGHT_CNT		385
#define NINE_CNT		225

#endif

#define TWO_START		0
#define TWO_END			TWO_START + TWO_CNT * WORD_ITEM_LEN - 1//0x578BFF
#define THREE_START		TWO_END + 1//0x578C00
#define THREE_END		THREE_START	 + THREE_CNT * WORD_ITEM_LEN - 1//0x9FBA7F
#define FOUR_START		THREE_END + 1//0x9FBA80
#define FOUR_END		FOUR_START + FOUR_CNT * WORD_ITEM_LEN - 1
#define FIVE_START		FOUR_END + 1 //0XFBD500
#define FIVE_END		FIVE_START + FIVE_CNT * WORD_ITEM_LEN - 1
#define SIX_START		FIVE_END + 1//0x102F880
#define SIX_END			SIX_START + SIX_CNT * WORD_ITEM_LEN - 1
#define SEVEN_START		SIX_END + 1//0x106AA60
#define SEVEN_END		SEVEN_START + SEVEN_CNT * WORD_ITEM_LEN - 1
#define EIGHT_START		SEVEN_END + 1//0x10AA3A0
#define EIGHT_END		EIGHT_START + EIGHT_CNT * WORD_ITEM_LEN - 1
#define NINE_START		EIGHT_END + 1//0x10B7440
#define NINE_END		NINE_START + NINE_CNT * WORD_ITEM_LEN - 1


//void DevideString(u16* dst, u16* src,int len)
//{
//	u16* pdst = dst;
//	u16* psrc = src;
//	int isChange = 0;//means the current character is not a Chinese character
//	int res = 0;
//	int res_last = 0;
//	u16* head = src;
//	u16* end = src;
//	u16* tmpbuf = NULL;
//	int tmp_len = 0;
//	int cnt = 0;
//	res_last = isChCharacter(*psrc);
//	while (len)
//	{
//		res = isChCharacter(*psrc);
//		if (res != res_last)
//			isChange = 1;
//		else
//			isChange = 0;
//		if (isChange)
//		{
//			end = psrc;
//			tmp_len = end - head;
//			tmpbuf = (u16*)malloc(sizeof(u16) * tmp_len);
//			for (cnt = 0; cnt < tmp_len; cnt++)
//			{
//				*(tmpbuf + cnt) = *(head + cnt);
//				printf("tmp+%d:%x\n", cnt,*(tmpbuf + cnt));
//			}
//			head = end;
//			/*segement*/
//
//			free(tmpbuf);
//			printf("************************\n");
//			*pdst++ = '|';
//			*pdst++ = *psrc++;
//		}
//		else
//		{
//			*pdst++ = *psrc++;
//		}
//		res_last = res;
//		len--;
//	}
//}

int Unicnt(u16 * src)// if src have no 0x00,fail
{
	int cnt = 0;
	u16* psrc = src;
	while (*(psrc++) != 0x00)
		cnt++;
	psrc = NULL;
	return cnt;
}
void Unidisplay(u16* src, int unilen)
{
	int i = 0;
	u16* psrc = src;
	for (i = 0; i < unilen; i++) {
		if (*(psrc + i) == 0x20)printf("\\u0020");
		//printf("src[%d]:%x\n", i, *(psrc + i));
		else
		{
			printf("\\u%x", *(psrc + i));
		}
	}
	psrc = NULL;
}

int UniInvercpy(u16* dst, u16* src, int get_len, int tol_len)
{
	u16* pdst = dst;
	u16* psrc = src;
	int i = 0;
	int offset;
	while (pdst == NULL || psrc == NULL)
		return 0;
	if (get_len > tol_len)
		get_len = tol_len;
	offset = tol_len - get_len;
	for (i = 0; i < get_len; i++)
		*(pdst++) = *(psrc + offset + i);
	pdst = NULL;
	psrc = NULL;
	return offset;
}/*
void GBKConvertUni(u8* gbkstr, u16* unistr)
{
	u16 gbktoken = 0;
	u8 gbkh, gbkl;
	u8* gbktmp = gbkstr;
	u16* unitmp = unistr;
	while (*gbktmp != '\0')
	{
		if (*gbktmp < 0x80)
		{
			*unitmp = ff_convert((u16)(*gbktmp), 1);
			gbktmp++;
			unitmp++;
		}
		else
		{
			gbkh = *gbktmp;
			gbkl = *(++gbktmp);
			gbktoken = (u16)(gbkh << 8) | gbkl;
			*unitmp = ff_convert(gbktoken, 1);
			gbktmp++;
			unitmp++;
		}
	}
	gbktmp = NULL;
	unitmp = NULL;
}
*/
void RangeDefine(int* low, int* high, int* baseaddress, int len)
{
	switch (len)
	{
	case 2:
		*low = 0;
		*high = TWO_CNT - 1;
		*baseaddress = TWO_START;
		break;
	case 3:
		*low = 0;
		*high = THREE_CNT - 1;
		*baseaddress = THREE_START;
		break;
	case 4:
		*low = 0;
		*high = FOUR_CNT - 1;
		*baseaddress = FOUR_START;
		break;
	case 5:
		*low = 0;
		*high = FIVE_CNT - 1;
		*baseaddress = FIVE_START;
		break;
	case 6:
		*low = 0;
		*high = SIX_CNT - 1;
		*baseaddress = SIX_START;
		break;
	case 7:
		*low = 0;
		*high = SEVEN_CNT - 1;
		*baseaddress = SEVEN_START;
		break;
	case 8:
		*low = 0;
		*high = EIGHT_CNT - 1;
		*baseaddress = EIGHT_START;
		break;
	case 9:
		*low = 0;
		*high = NINE_CNT - 1;
		*baseaddress = NINE_START;
		break;
	default:
		*low = 0;
		*high = 0;
		*baseaddress = 0;
		break;
	}
}
int Unicmp(u16* dst, u16* src, int src_cnt)
{
	int i;
	for (i = 0; i < src_cnt; i++)
	{
		if (*(src + i) == *(dst + i))
			continue;
		else if (*(dst + i) > *(src + i))
			return 1;// dst > src
		else
			return -1;//dst < src
	}
	return 0;//dst == src
}
int StringMatch(u16* src, int length)
{
	/*FILE* pSeg = NULL;*/
	u16* psrc = src;
	/*u16 unitmp[10] = { 0x00 };*/
	u16* unitmp = (u16*)malloc(sizeof(u16) * length);
	/*char* pname = (char*)malloc(sizeof(char) * 100);*/
	int low, middle, high, baseaddress;
	int offset = 0;
	int k = 0;
	int res = 0;
	unsigned char is_smaller = 0;
	unsigned char is_larger = 0;
	if (psrc == NULL)
		return -2;
	if (unitmp == NULL)
	{
		printf("allocate error\n");
		return -2;
	}
	/*if (pname == NULL || unitmp==NULL)
	{
		printf("allocate error\n");
		return -2;
	}
	strcpy(pname, segpath);
	pSeg = fopen(pname, "r");
	if (pSeg == (FILE*)NULL)
	{
		printf("open dict file error\n");
		return -2;
	}*/
	RangeDefine(&low, &high, &baseaddress, length);//define low, high and baseaddress value
	while (low <= high)//dichotomous method
	{
		middle = (low + high) / 2;
		offset = middle * WORD_ITEM_LEN + baseaddress;
		fseek(pSeg, offset, 0);
		fread(unitmp, sizeof(u16), length, pSeg);
		/*printf("--------first locate unitmp--------\n");
		Unidisplay(unitmp, length);*/

		if (*unitmp == *psrc)
			break;
		else if (*unitmp > *psrc)
			high = middle - 1;
		else
			low = middle + 1;
	}
	if (low <= high)//find the first unicode matched
	{
		k = middle;
		while (*unitmp == *psrc)// find the following matched unicode
		{
			/*printf("***********k:%d************\n", k);
			Unidisplay(unitmp, length);*/
			psrc = src;
			res = Unicmp(unitmp, psrc, length);
			if (res == 0)
				return 0;//find current length in table
			else if (res == -1)//unitmp<src
			{
				is_smaller = 1;
				if (is_larger == 1)
					return -1;
				k++;
			}
			else if (res == 1)//unitmp>src
			{
				is_larger = 1;
				if (is_smaller == 1)
					return -1;
				k--;
			}
			offset = k * WORD_ITEM_LEN + baseaddress;
			fseek(pSeg, offset, 0);
			fread(unitmp, sizeof(u16), length, pSeg);
		}
		return -1;
	}
	else
		return -1;
	fclose(pSeg);
	free(unitmp);
	/*free(pname);*/
}
void AddSegSymbol(u16* src, int addplace, int len)
{
	u16* psrc = src;
	int i = 0;
	for (i = len - 1; i > addplace; i--)
	{
		*(psrc + i) = *(psrc + i - 1);
	}
	*(psrc + addplace) = 0x20;
}
int StringSegment(u16* dst, u16* src, int src_len, int* seg_dst_len)
{
	u16* pdst = dst;
	u16* psrc = src;
	int get_len = 0;
	int seg_offset = 0;
	int i = 0;
	int res = -1;
	int dst_len = src_len;
	int addsegcnt = 0;
	u16 unitmp[100] = { 0x00 };
	for (i = 0; i < src_len; i++)
		*(pdst + i) = *(psrc + i);
	if (src_len == 1)
	{
		*seg_dst_len = 1;
		/*printf("---------print dst-----------\n");*/
		/*Unidisplay(pdst, dst_len);*/
		return 0;// one character
	}
	while (src_len > 1)
	{
		pdst = dst;
		if (src_len < WORD_ITEM_MAXCNT)
			get_len = src_len;
		else
			get_len = WORD_ITEM_MAXCNT;
		for (i = get_len; i >= 2; i--)
		{
			/*printf("*******GET %d*******\n", i);*/
			seg_offset = UniInvercpy(unitmp, psrc, i, src_len);
			/*printf("offset:%d\n", seg_offset);*/
			/*Unidisplay(unitmp, i);*/
			res = StringMatch(unitmp, i);
			/*printf("is match %d\n", res);*/
			if (res == 0)
				break;
		}
		if (res == -1)
		{
			src_len -= 1;
			dst_len += 1;
			seg_offset = seg_offset + 1;
			/*printf("no found current offset:%d\n", seg_offset);*/
		}
		else if (res == 0)
		{
			/*seg_get = src_len - seg_offset;
			current_get += seg_get;
			printf("seg_get:%d,current_get:%d\n", seg_get,current_get);*/
			src_len -= i;
			/*printf("found current offset:%d\n", seg_offset);*/
			if (seg_offset != 0)
			{
				dst_len += 1;
			}
		}
		if (src_len != 0)
		{
			addsegcnt += 1;
			AddSegSymbol(pdst, seg_offset, dst_len);
		}
	}
	/*Unidisplay(pdst, dst_len);*/
	*seg_dst_len = dst_len;
	return addsegcnt;
}
int DevideString(u16* dst, u16* src, int len)
{
	u16* pdst = dst;
	u16* psrc = src;
	int isChange = 0;//means the current character is not a Chinese character
	int res = 0;
	int res_last = 0;
	u16* head = src;
	u16* end = src;
	u16* tmpbuf = NULL;
	int tmp_len = 0;
	int tmp_seg_dstlen = 0;
	int addsegcnt = 0;
	int cnt = 0;
	

	res_last = isChCharacter(*psrc);
	while (len)
	{
		res = isChCharacter(*psrc);
		if (res != res_last && res == 0)
		{
			end = psrc;//first symbol not Chinese character
			tmp_len = end - head;
			tmpbuf = (u16*)malloc(sizeof(u16) * tmp_len);
			for (cnt = 0; cnt < tmp_len; cnt++)
			{
				*(tmpbuf + cnt) = *(head + cnt);
				/*printf("tmp+%d:%x\n", cnt, *(tmpbuf + cnt));*/
			}
			/*printf("---------print pdst-----------\n");*/
			addsegcnt += StringSegment(pdst, tmpbuf, tmp_len, &tmp_seg_dstlen);
			pdst += tmp_seg_dstlen;
			*pdst++ = *psrc;
			free(tmpbuf);
		}
		else if (res != res_last && res == 1)
		{
			head = psrc;
		}
		else if (res == 0)
		{
			*pdst++ = *psrc;
		}
		res_last = res;
		/*pdst++;*/
		psrc++;
		len--;
		if (len == 0 && res == 1 && res_last == 1)
		{
			end = psrc;
			tmp_len = end - head;
			tmpbuf = (u16*)malloc(sizeof(u16) * tmp_len);
			for (cnt = 0; cnt < tmp_len; cnt++)
			{
				*(tmpbuf + cnt) = *(head + cnt);
				/*printf("tmp+%d:%x\n", cnt, *(tmpbuf + cnt));*/
			}
			/*printf("---------print pdst-----------\n");*/
			addsegcnt += StringSegment(pdst, tmpbuf, tmp_len, &tmp_seg_dstlen);
			pdst += tmp_seg_dstlen;
			free(tmpbuf);
		}
	}
	return addsegcnt;
}
/*
int main(void)
{
	int cnt = 0;
	int low, high, baseaddress;
	char str[] = "abc布局和前三殿基本一样";
	char str2[50] = "";
	char dot_res[1000] = "";
	strncpy(str2, str + 4, 1);
	printf("str2:%s\n", str2);
	char* pname = (char*)malloc(sizeof(char) * 100);
	if (pname == NULL)
	{
		printf("allocate error\n");
		return -2;
	}
	strcpy(pname, segpath);
	pSeg = fopen(pname, "r");
	if (pSeg == (FILE*)NULL)
	{
		printf("open dict file error\n");
		return -2;
	}
	u16 dst_res[100] = { 0x00 };
	GBKConvertUni(str, dst_res);
	cnt = Unicnt(dst_res);
	Unidisplay(dst_res, cnt);
	u16 test[200] = { 0x00 };
	int addcnt = DevideString(test, dst_res, cnt);
	printf("seg add:%d\n", addcnt);
	cnt = Unicnt(test);
	Unidisplay(test, cnt);
	free(pname);
	fclose(pSeg);
	TwoPloyphonicTranslate(test, cnt, dot_res, two_polyphonic_path);
	printf("dot len:%d,dot res:%s\n", strlen(dot_res), dot_res);
}*/
//int main(void)
//{
//	char* pname = (char*)malloc(sizeof(char) * 100);
//	u16 dst_res[100] = { 0x00 };
//	int offset=0xa3fe0;
//	unsigned char unil = 0;
//	unsigned char unih = 0;
//	if (pname == NULL)
//	{
//		printf("allocate error\n");
//		return -2;
//	}
//	strcpy(pname, danzipath);
//	pSeg = fopen(pname, "rb");
//	if (pSeg == (FILE*)NULL)
//	{
//		printf("open dict file error\n");
//		return -2;
//	}
//	fseek(pSeg, offset, 0);
//	fread(dst_res, sizeof(u16), 1, pSeg);
//	Unidisplay(dst_res, 2);
//	fclose(pSeg);
//}