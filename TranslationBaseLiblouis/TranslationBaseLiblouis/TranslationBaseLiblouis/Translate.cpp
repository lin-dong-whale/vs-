

#include <iostream>
#include<stdio.h>
#include<string.h>
#include"max.h"
#include"utf-8tounicode.h"
#include"ToBraille.h"
#include"CompileFlashTable.h"
#include"CompileAlwaysTable.h"
#include"CompileFenCiDict.h"
#include"USGrade1Trans.h"
#include"MergeSort.h"
#include"GetEnglishWord.h"
#include"mySegmentation.h"

#include"TranslateBaseOnTable.h"
#pragma warning(disable:4996)

#pragma execution_character_set("utf-8")
char segpath[] = ".\\Debug\\JieBaDict.txt";//使用处理过的jieba的字典，除去10个字及以上的词
FILE* pSeg = NULL;
int a = 0;
int main()
{
	//inint();
	/*
	u8 buffer1[100] = "第二十周周报";


	char* result[1000];

	u16 unibuf[100] = { 0x0000 };
	int unibufsize;
	StringToUni(buffer1, unibuf,strlen((const char*)buffer1));
	unibufsize = sizeof(unibuf) /sizeof(unibuf[0]);

	GetDot(unibuf, unibufsize);
	*/


	//GteAndWrite(1);//mode的值为1.转换单字表，为2转换两个字的多音字表
	//GetAndWriteFenCi();
	//MergeSortTest();
	//GetAlwaysAndWrite();//编译1-9个的通用翻译表
	//EnglisfGrade1();
	int InPutlen = 21;
	int Unicodelen = 0;
	int Dotlen = 0;
	int mode = 1;

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


	u8 InPut[INPUTSIZE] = "于是看到了不对得地方是他的";
	u16 DevideUnicodeOutput[UNICODESIZE * 2] = {0x00};
	char PointOut[POINTSIZE] = { '\0' };



	TranslateBaseOnTable(InPut,InPutlen,mode ,DevideUnicodeOutput,&Unicodelen,PointOut,&Dotlen);
	free(pname);
	pname = NULL;
	fclose(pSeg);

	printf(PointOut);
	printf("end!");
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
