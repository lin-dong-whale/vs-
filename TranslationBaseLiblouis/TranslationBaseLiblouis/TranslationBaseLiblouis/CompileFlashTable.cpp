#include "CompileFlashTable.h"
#include"utf-8tounicode.h"
#include"malloc.h"

#pragma warning(disable:4996)

#define SIGNSIZE 20902
char Dot01[64] = { "\0" };//点序翻译结果


typedef struct SIGNNN {
	u16 unicode;
	char Dot[64];
}chndanzi;

chndanzi signtable1111[SIGNSIZE]{};


typedef struct numtodot {
	char num[7];
	char dot[7];


}ntod;

ntod numanddot[64]{

	{"0","000000"},  {"1","100000"},   {"2","010000"},   {"12","110000"},   {"3","001000"},   {"13","101000"},   {"23","011000"},   {"123","111000"},
	{"4","000100"},  {"14","100100"},  {"24","010100"},  {"124","110100"},  {"34","001100"},  {"134","101100"},  {"234","011100"},  {"1234","111100"},
	{"5","000010"},  {"15","100010"},  {"25","010010"},  {"125","110010"},  {"35","001010"},  {"135","101010"},  {"235","011010"},  {"1235","111010"},
	{"45","000110"}, {"145","100110"}, {"245","010110"}, {"1245","110110"}, {"345","001110"}, {"1345","101110"}, {"2345","011110"}, {"12345","111110"},
	{"6","000001"},  {"16","100001"},  {"26","010001"},  {"126","110001"},  {"36","001001"},  {"136","101001"},  {"236","011001"},  {"1236","111001"},
	{"46","000101"}, {"146","100101"}, {"246","010101"}, {"1246","110101"}, {"346","001101"}, {"1346","101101"}, {"2346","011101"} ,{"12346","111101"},
	{"56","000011"}, {"156","100011"}, {"256","010011"}, {"1256","110011"}, {"356","001011"}, {"1356","101011"}, {"2356","011011"}, {"12356","111011"},
	{"456","000111"},{"1456","100111"},{"2456","010111"},{"12456","110111"},{"3456","001111"},{"13456","101111"},{"23456","011111"},{"123456","111111"}

};



int tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return c + 'a' - 'A';
	}
	else
	{
		return c;
	}
}
//将十六进制的字符串转换成整数  
int htoi(char s[])
{
	int i;
	int n = 0;
	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
	{
		i = 2;
	}
	else
	{
		i = 0;
	}
	for (; (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'); ++i)
	{
		if (tolower(s[i]) > '9')
		{
			n = 16 * n + (10 + tolower(s[i]) - 'a');
		}
		else
		{
			n = 16 * n + (tolower(s[i]) - '0');
		}
	}
	return n;
}
int Compile(char tableLine[],u16*SignU,u16*AlwaysU) {
	int i,j;
	int dotset = 0;
	int findflag = 0;//检查是否找到了数字点序与01点序的对应
	char lintype[7] = {"\0"};//存放条目是sign还是always
	char always[] = "always";
	char sign[] = "sign";
	char hanzi1[6] = { "\0" };//词组汉字第一个的Unicode码
	char hanzi2[6] = { "\0" };
	u16 hanzi1x;
	u16 hanzi2x;
	char Dot[64] = { "\0" };//存放一个条目的数字点序
	char OneDot[7] = { "\0" };//临时存放一方的数字点序

	
	int hanzi1flag = 0;//是否已经写入了一个汉字

	for (i = 0; i < 64; i++)Dot01[i] = '\0';

	for (i = 0; i < 64&&tableLine[i]!='\0'; i++) {
		if (tableLine[i] == 32)break;
		lintype[i] = tableLine[i];		//获取词条的字符类型
	}
	if (!strcmp(lintype, always)) {//如果词条是多音字

		for (i = 0; tableLine[i] != '\0'; i++) {
			if ((tableLine[i] == 92) && hanzi1flag == 0) {
				for (int j = 0; j <= 4; j++) {
					hanzi1[j] = tableLine[i + j + 1];
					hanzi1flag = 1;
					
				}
				i = i + 5;
				*SignU = htoi(hanzi1);

			}
			else if ((tableLine[i] == 92) && hanzi1flag == 1)
			{
				for (int j = 0; j <= 4; j++)
				{
					hanzi2[j] = tableLine[i + j + 1];
					hanzi1flag = 2;
					
				}
				i = i + 5;
				*AlwaysU = htoi(hanzi2);
			}
			else if (hanzi1flag == 2 && tableLine[i] != 32) {

				Dot[dotset] = tableLine[i];
				dotset++;
			}
		}

	}
	else if (!strcmp(lintype, sign)) {//如果词条是单字
		for (i = 0; tableLine[i] != '\0'; i++) {
			if ((tableLine[i] == 92)) {
				for (int j = 0; j <= 4; j++) {
					hanzi1[j] = tableLine[i + j + 1];
					hanzi1flag = 1;
				}
				i = i + 5;
				*SignU = htoi(hanzi1);
			}
			else if (hanzi1flag == 1 && tableLine[i] != 32) {

				Dot[dotset] = tableLine[i];//遍历获取
				dotset++;
			}
		}


	}
	else {

		printf("%s这一行不符合标准,情修改标志位", tableLine);
		return 1;
	}
	j = 0;
	for (i = 0; Dot[i] != '\n'; i++) {
		if (Dot[i] != 0x2d) {
			OneDot[j] = Dot[i];
		}
		else {
			findflag = 0;
			for (int k=0; k < 64; k++) {
				if (!strcmp(OneDot, numanddot[k].num)) {
					strcat(Dot01, numanddot[k].dot);
					findflag = 1;
					break;
				}
			}
			if(findflag==0)
				strcat_s(Dot01, numanddot[0].dot);
			j = 0;
			i++;
			for (int ii = 0; ii < 7;ii++)OneDot[ii] ='\0';
			OneDot[j]=Dot[i];
		}
		j++;
	}
	for (int k=0; k < 64; k++) {
		if (!strcmp(OneDot, numanddot[k].num)) {
			strcat(Dot01, numanddot[k].dot);
			findflag = 1;
			break;
		}
	}
	if (findflag == 0)
		strcat_s(Dot01, numanddot[0].dot);
	strcat(Dot01,"\0");
	char* reslut = Dot01;
	return 0;
}


void Merge(chndanzi signtable[],int left,int mid,int right) {
	int len = right - left + 1;        //    数组的长度
	// *temp=new chndanzi[len];
	chndanzi* tempp = (chndanzi*)malloc(len * sizeof(chndanzi));
	int k = 0;
	int i = left;                   // 前一数组的起始元素
	int j = mid + 1;                // 后一数组的起始元素
	while (i <= mid && j <= right)
	{
		//    选择较小的存入临时数组
		if (signtable[i].unicode <= signtable[j].unicode) {
			tempp[k].unicode = signtable[i].unicode;
			for (int kk = 0; kk < 64; kk++) {
				tempp[k].Dot[kk]=signtable[i].Dot[kk];

			}
			//strcat(tempp[k].Dot, signtable[i].Dot);
			i++;

		}
		else {
			tempp[k].unicode = signtable[j].unicode;
			for (int kk = 0; kk < 64; kk++) {
				tempp[k].Dot[kk]=signtable[j].Dot[kk];

			}
			//strcat(tempp[k].Dot, signtable[j].Dot);
		    j++;
	    }
		k++;
		
		
		//temp[k++] = a[i] <= a[j] ? a[i++] : a[j++];

	}
	while (i <= mid)
	{
		tempp[k].unicode = signtable[i].unicode;
		for (int kk = 0; kk < 64; kk++) {
			tempp[k].Dot[kk]=signtable[i].Dot[kk];

		}
		//strcat(tempp[k].Dot, signtable[i].Dot);
		k++;
		i++;
		//temp[k++] = a[i++];
	}
	while (j <= right)
	{
		tempp[k].unicode = signtable[j].unicode;
		for (int kk = 0; kk < 64; kk++) {
			tempp[k].Dot[kk]= signtable[j].Dot[kk];

		}
		//strcat(tempp[k].Dot, signtable[j].Dot);
		k++;
		j++;
		//temp[k++] = a[j++];
	}
	for (int k = 0; k < len; k++)
	{
		signtable[left].unicode = tempp[k].unicode;
		for (int kk = 0; kk < 64; kk++) {
			signtable[left].Dot[kk]=tempp[k].Dot[kk] ;
		}
		//strcat(signtable[left].Dot, tempp[k].Dot);
		left++;
		//a[left++] = temp[k];
	}
	free(tempp);
}

void MergeSort(chndanzi signtable[],int left , int right) {
	if (left == right)return;

	int mid = (left + right) / 2;

	MergeSort(signtable, left, mid);
	MergeSort(signtable, mid + 1, right);
	Merge(signtable, left, mid, right);
}


int GteAndWrite(int mode) {//mode的值为1.转换单字表，为2转换两个字的多音字表

	

	char tableLine[64] = {'\0'};//存放表的一行内容
	u16 SignU;//第一个汉字Unicode
	u16 AlwaysU;//第二个汉字Unicode
	int signtableset = 0;


	FILE* Table = fopen("D:\\LD\\vc-c\\TranslationBaseLiblouis\\test.txt","r");
	FILE* FlashTable = fopen("D:\\LD\\vc-c\\TranslationBaseLiblouis\\FlashTable.txt", "wb");//以二进制文件写入，防止用“w”模式出现要写入0x0a（回车的ASCII码）自动补齐0x0d0x0a（换行加回车）的情况

	if (Table == (FILE*)NULL) {
		printf("open dict fileerror !\n");
		return -1;
	}

	while (!feof(Table)) {
		for(int i=0;i<64;i++)tableLine[i]='\0';
		fgets(tableLine, 64, Table);//获取一行的词条
		if (tableLine[0] == '\0')break;

		if (!Compile(tableLine, &SignU,&AlwaysU)) {
			if (mode == 1) {//执行单字表转换
				signtable1111[signtableset].unicode = SignU;
				strcat(signtable1111[signtableset].Dot, Dot01);

				//fwrite(&SignU, 2, 1, FlashTable);
				//fwrite(Dot01, 1, 30, FlashTable);
			}
			else if (mode == 2) {//执行多音字表转化
				fwrite(&SignU, 2, 1, FlashTable);
				fwrite(&AlwaysU, 2, 1, FlashTable);
				fwrite(Dot01, 1, 28, FlashTable);
			}
			else
				continue;
			
		}
		signtableset++;
	}
	MergeSort(signtable1111, 0, SIGNSIZE-1);
	for (int k = 0; k < SIGNSIZE;k++) {
		fwrite(&signtable1111[k].unicode, 2, 1, FlashTable);
		fwrite(&signtable1111[k].Dot, 1, 30, FlashTable);

	}
	fclose(Table);
	fclose(FlashTable);



	return 0;



}
