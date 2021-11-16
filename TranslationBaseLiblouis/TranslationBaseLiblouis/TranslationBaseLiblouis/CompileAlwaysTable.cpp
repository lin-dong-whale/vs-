#include"CompileAlwaysTable.h"
#include"utf-8tounicode.h"

#include"malloc.h"

#pragma warning(disable:4996)

#define SIZE1 20999
#define SIZE2 30000
#define SIZE3 900
#define SIZE4 1200
#define SIZE5 50
#define SIZE6 50
#define SIZE7 50
#define SIZE8 50
#define SIZE9 50
#define SIZE10 50

#define ciyumax 10
#define dotmax  300
#define OneLineMax 300

typedef struct ciyu_2 {
	u16 ciyu[ciyumax];
	char dot[dotmax];
}ciyu;
ciyu OneAlwaysWords[SIZE1]{};
ciyu TwoAlwaysWords[SIZE2]{};
ciyu ThreeAlwaysWords[SIZE3]{};
ciyu FourAlwaysWord[SIZE4]{};
ciyu FiveAlwaysWord[SIZE5]{};
ciyu SixAlwaysWord[SIZE6]{};
ciyu SevenAlwaysWord[SIZE7]{};
ciyu EightAlwaysWord[SIZE8]{};
ciyu NineAlwaysWord[SIZE9]{};
ciyu TenAlwaysWord[SIZE10]{};

typedef struct numchange {
	char num[7];
	char dot[7];


}nuntod;

nuntod numdottable[64]{

	{"0","000000"},  {"1","100000"},   {"2","010000"},   {"12","110000"},   {"3","001000"},   {"13","101000"},   {"23","011000"},   {"123","111000"},
	{"4","000100"},  {"14","100100"},  {"24","010100"},  {"124","110100"},  {"34","001100"},  {"134","101100"},  {"234","011100"},  {"1234","111100"},
	{"5","000010"},  {"15","100010"},  {"25","010010"},  {"125","110010"},  {"35","001010"},  {"135","101010"},  {"235","011010"},  {"1235","111010"},
	{"45","000110"}, {"145","100110"}, {"245","010110"}, {"1245","110110"}, {"345","001110"}, {"1345","101110"}, {"2345","011110"}, {"12345","111110"},
	{"6","000001"},  {"16","100001"},  {"26","010001"},  {"126","110001"},  {"36","001001"},  {"136","101001"},  {"236","011001"},  {"1236","111001"},
	{"46","000101"}, {"146","100101"}, {"246","010101"}, {"1246","110101"}, {"346","001101"}, {"1346","101101"}, {"2346","011101"} ,{"12346","111101"},
	{"56","000011"}, {"156","100011"}, {"256","010011"}, {"1256","110011"}, {"356","001011"}, {"1356","101011"}, {"2356","011011"}, {"12356","111011"},
	{"456","000111"},{"1456","100111"},{"2456","010111"},{"12456","110111"},{"3456","001111"},{"13456","101111"},{"23456","011111"},{"123456","111111"}

};


void AlwaysMerge(ciyu Word[], int left, int mid, int right) {
	int len = right - left + 1;
	ciyu* temp = new ciyu[len];
	//ciyu temp[2];
	int k = 0;
	int l = 0;
	int i = left;
	int j = mid + 1;
	int change = 0;
	while (i <= mid && j <= right) {
		change = 0;
		for (l = 0; l < ciyumax; l++) {
			if (Word[i].ciyu[l] < Word[j].ciyu[l]) {
				change = 1;
				break;
			}
			else if (Word[i].ciyu[l] == Word[j].ciyu[l]) {
				continue;
			}
			else {
				change = 0;
				break;
			}
		}
		if (change == 1) {
			for (l = 0; l < ciyumax; l++) {
				temp[k].ciyu[l] = Word[i].ciyu[l];
			}
			for (int kk = 0; kk < dotmax; kk++) {
				temp[k].dot[kk] = Word[i].dot[kk];
			}
			i++;

		}
		else {
			for (l = 0; l < ciyumax; l++) {
				temp[k].ciyu[l] = Word[j].ciyu[l];
			}
			for (int kk = 0; kk < dotmax; kk++) {
				temp[k].dot[kk] = Word[j].dot[kk];

			}
			j++;
		}
		k++;
	}

	while (i <= mid) {
		for (l = 0; l < ciyumax; l++) {
			temp[k].ciyu[l] = Word[i].ciyu[l];
		}
		for (int kk = 0; kk < dotmax; kk++) {
			temp[k].dot[kk] = Word[i].dot[kk];
		}
		k++;
		i++;
	}
	while (j <= right) {
		for (l = 0; l < ciyumax; l++) {
			temp[k].ciyu[l] = Word[j].ciyu[l];
		}
		for (int kk = 0; kk < dotmax; kk++) {
			temp[k].dot[kk] = Word[j].dot[kk];

		}
		k++;
		j++;
	}
	for (k = 0; k < len; k++) {
		for (l = 0; l < ciyumax; l++) {
			Word[left].ciyu[l] = temp[k].ciyu[l];
		}
		for (int kk = 0; kk < dotmax; kk++) {
			Word[left].dot[kk]= temp[k].dot[kk] ;

		}
		left = left + 1;
	}

}
void Merge_Sort(ciyu Word[], int left, int right) {
	if (left == right)return;
	int mid = (left + right) / 2;
	Merge_Sort(Word, left, mid);
	Merge_Sort(Word, mid + 1, right);
	AlwaysMerge(Word, left, mid, right);
}

int Merge_Sort_(ciyu Word[], int SIZE) {

	Merge_Sort(Word, 0, SIZE - 1);

	return 0;
}


int GetAlwaysAndWrite() {

	char hanziuni[6] = { "0x00"};
	u16 unibuf[40] = { 0x0000 };
	u8 OneLine[OneLineMax] = { '\0' };
	char OneDot[7] = { "\0" };//临时存放一方的数字点序
	char Dot01[dotmax] = { "\0" };//点序翻译结果
	int LineSubscript = 0;
	u8 ch;
	int unicount = 0;
	int uniset = 0;
	
	int findflag = 0;
	int i = 0;
	int j = 0;
	int linbigin = 0;
	int linend = 0;
	int canttranse=0;

	FILE* Table = fopen("D:\\LD\\vc-c\\TranslationBaseLiblouis\\test.txt", "r");
	FILE* FlashTable = fopen("D:\\LD\\vc-c\\TranslationBaseLiblouis\\FlashTable.txt", "wb");//以二进制文件写入，防止用“w”模式出现要写入0x0a（回车的ASCII码）自动补齐0x0d0x0a（换行加回车）的情况
	FILE* WordNumCount = fopen("D:\\LD\\vc-c\\TranslationBaseLiblouis\\WordNumCount.txt", "wb");
	if (Table == (FILE*)NULL) {
		printf("open dict fileerror !\n");
		return -1;
	}
	while (!feof(Table)) {
		
		

		ch = fgetc(Table);
		if (ch != '\n') {//获取一行的内容
			OneLine[LineSubscript] = ch;
			if (ch == 0x20&& linend==0)linbigin = LineSubscript;
			if (ch == 0x20 && linbigin != 0)linend = LineSubscript;

			LineSubscript++;
		}
		else{
	        unicount = 0;
			findflag = 0;
	        for (uniset = linbigin; uniset <= linend; uniset++) {
		        if (OneLine[uniset] == 0x78) {
		        	for (int j = 0; j <= 4; j++) {
		    	    	hanziuni[j] = OneLine[uniset + j];

			        }
					uniset = uniset + 5;
		        	
			        unibuf[unicount] = htoi(hanziuni);
					unicount++;

	    	    }

	        }
			j = 0;
			for (i = linend+1;i<= LineSubscript; i++) {
				if (OneLine[i] != 0x2d) {
					OneDot[j] = OneLine[i];
				}
				else {
					findflag = 0;
					for (int k = 0; k < 64; k++) {if (!strcmp(OneDot, numdottable[k].num)) {strcat(Dot01, numdottable[k].dot);findflag = 1;
							break;
						}
					}
					if (findflag == 0)
						strcat_s(Dot01, numdottable[0].dot);
					j = 0;
					i++;
					for (int ii = 0; ii < 7; ii++)OneDot[ii] = '\0';
					OneDot[j] = OneLine[i];
				}
				j++;
				
			}
			for (int k = 0; k < 64; k++) {
				if (!strcmp(OneDot, numdottable[k].num)) {
					strcat(Dot01, numdottable[k].dot);
					findflag = 1;
					break;
				}

			}
			if (findflag == 0)
				strcat_s(Dot01, numdottable[0].dot);
			strcat(Dot01, "\0");


			if (unicount == 1) {
				for (i = 0; i < 6; i++)hanziuni[i] = 0x00;			
				for (i = 0; i < OneLineMax; i++) OneLine[i] = '\0';
				for (i = 0; i < 7; i++)OneDot[i] = '\0';

				LineSubscript = 0;
				for (i = 0; i < SIZE1; i++) {
					if (OneAlwaysWords[i].ciyu[0] == '\0') {
						for (j = 0; j < 1; j++) {
							OneAlwaysWords[i].ciyu[j] = unibuf[j];
						}
						strcat(OneAlwaysWords[i].dot,Dot01);
						for (i = 0; i < 40; i++)unibuf[i] = 0x00;
						for (i = 0; i < dotmax; i++)Dot01[i] = '\0';
						break;
					}
					else continue;
				}
				
			}
			if (unicount == 2) {
				for (i = 0; i < 6; i++)hanziuni[i] = 0x00;			
				for (i = 0; i < OneLineMax; i++) OneLine[i] = '\0';
				for (i = 0; i < 7; i++)OneDot[i] = '\0';
				LineSubscript = 0;
				for (i = 0; i < SIZE2; i++) {
					if (TwoAlwaysWords[i].ciyu[0] == '\0') {
						for (j = 0; j < 2; j++) {
							TwoAlwaysWords[i].ciyu[j] = unibuf[j];
						}
						strcat(TwoAlwaysWords[i].dot, Dot01);
						for (i = 0; i < 40; i++)unibuf[i] = 0x00;
						for (i = 0; i < dotmax; i++)Dot01[i] = '\0';
						break;
					}
					else continue;
				}

			}
			if (unicount == 3) {
				for (i = 0; i < 6; i++)hanziuni[i] = 0x00;
				for (i = 0; i < OneLineMax; i++) OneLine[i] = '\0';
				for (i = 0; i < 7; i++)OneDot[i] = '\0';
				LineSubscript = 0;
				for (i = 0; i < SIZE3; i++) {
					if (ThreeAlwaysWords[i].ciyu[0] == '\0') {
						for (j = 0; j < 3; j++) {
							ThreeAlwaysWords[i].ciyu[j] = unibuf[j];
						}
						strcat(ThreeAlwaysWords[i].dot, Dot01);
						for (i = 0; i < 40; i++)unibuf[i] = 0x00;
						for (i = 0; i < dotmax; i++)Dot01[i] = '\0';
						break;
					}
					else continue;
				}

			}

			if (unicount == 4) {
				for (i = 0; i < 6; i++)hanziuni[i] = 0x00;
				for (i = 0; i < OneLineMax; i++) OneLine[i] = '\0';
				for (i = 0; i < 7; i++)OneDot[i] = '\0';
				LineSubscript = 0;
				for (i = 0; i < SIZE4; i++) {
					if (FourAlwaysWord[i].ciyu[0] == '\0') {
						for (j = 0; j < unicount; j++) {
							FourAlwaysWord[i].ciyu[j] = unibuf[j];
						}
						strcat(FourAlwaysWord[i].dot, Dot01);
						for (i = 0; i < 40; i++)unibuf[i] = 0x00;
						for (i = 0; i < dotmax; i++)Dot01[i] = '\0';
						break;
					}
					else continue;
				}

			}

			if (unicount == 5) {
				for (i = 0; i < 6; i++)hanziuni[i] = 0x00;
				for (i = 0; i < OneLineMax; i++) OneLine[i] = '\0';
				for (i = 0; i < 7; i++)OneDot[i] = '\0';
				LineSubscript = 0;
				for (i = 0; i < SIZE5; i++) {
					if (FiveAlwaysWord[i].ciyu[0] == '\0') {
						for (j = 0; j < unicount; j++) {
							FiveAlwaysWord[i].ciyu[j] = unibuf[j];
						}
						strcat(FiveAlwaysWord[i].dot, Dot01);
						for (i = 0; i < 40; i++)unibuf[i] = 0x00;
						for (i = 0; i < dotmax; i++)Dot01[i] = '\0';
						break;
					}
					else continue;
				}

			}

			if (unicount == 6) {
				for (i = 0; i < 6; i++)hanziuni[i] = 0x00;
				for (i = 0; i < OneLineMax; i++) OneLine[i] = '\0';
				for (i = 0; i < 7; i++)OneDot[i] = '\0';
				LineSubscript = 0;
				for (i = 0; i < SIZE6; i++) {
					if (SixAlwaysWord[i].ciyu[0] == '\0') {
						for (j = 0; j < unicount; j++) {
							SixAlwaysWord[i].ciyu[j] = unibuf[j];
						}
						strcat(SixAlwaysWord[i].dot, Dot01);
						for (i = 0; i < 40; i++)unibuf[i] = 0x00;
						for (i = 0; i < dotmax; i++)Dot01[i] = '\0';
						break;
					}
					else continue;
				}

			}

			if (unicount == 7) {
				for (i = 0; i < 6; i++)hanziuni[i] = 0x00;
				for (i = 0; i < OneLineMax; i++) OneLine[i] = '\0';
				for (i = 0; i < 7; i++)OneDot[i] = '\0';
				LineSubscript = 0;
				for (i = 0; i < SIZE7; i++) {
					if (SevenAlwaysWord[i].ciyu[0] == '\0') {
						for (j = 0; j < unicount; j++) {
							SevenAlwaysWord[i].ciyu[j] = unibuf[j];
						}
						strcat(SevenAlwaysWord[i].dot, Dot01);
						for (i = 0; i < 40; i++)unibuf[i] = 0x00;
						for (i = 0; i < dotmax; i++)Dot01[i] = '\0';
						break;
					}
					else continue;
				}

			}

			if (unicount == 8) {
				for (i = 0; i < 6; i++)hanziuni[i] = 0x00;
				for (i = 0; i < OneLineMax; i++) OneLine[i] = '\0';
				for (i = 0; i < 7; i++)OneDot[i] = '\0';
				LineSubscript = 0;
				for (i = 0; i < SIZE8; i++) {
					if (EightAlwaysWord[i].ciyu[0] == '\0') {
						for (j = 0; j < unicount; j++) {
							EightAlwaysWord[i].ciyu[j] = unibuf[j];
						}
						strcat(EightAlwaysWord[i].dot, Dot01);
						for (i = 0; i < 40; i++)unibuf[i] = 0x00;
						for (i = 0; i < dotmax; i++)Dot01[i] = '\0';
						break;
					}
					else continue;
				}

			}
			if (unicount ==9) {
				for (i = 0; i < 6; i++)hanziuni[i] = 0x00;
				for (i = 0; i < OneLineMax; i++) OneLine[i] = '\0';
				for (i = 0; i < 7; i++)OneDot[i] = '\0';
				LineSubscript = 0;
				for (i = 0; i < SIZE9; i++) {
					if (NineAlwaysWord[i].ciyu[0] == '\0') {
						for (j = 0; j < unicount; j++) {
							NineAlwaysWord[i].ciyu[j] = unibuf[j];
						}
						strcat(NineAlwaysWord[i].dot, Dot01);
						for (i = 0; i < 40; i++)unibuf[i] = 0x00;
						for (i = 0; i < dotmax; i++)Dot01[i] = '\0';
						break;
					}
					else continue;
				}

			}
			if (unicount == 10) {
				for (i = 0; i < 6; i++)hanziuni[i] = 0x00;
				for (i = 0; i < OneLineMax; i++) OneLine[i] = '\0';
				for (i = 0; i < 7; i++)OneDot[i] = '\0';
				LineSubscript = 0;
				for (i = 0; i < SIZE10; i++) {
					if (TenAlwaysWord[i].ciyu[0] == '\0') {
						for (j = 0; j < unicount; j++) {
							TenAlwaysWord[i].ciyu[j] = unibuf[j];
						}
						strcat(TenAlwaysWord[i].dot, Dot01);
						for (i = 0; i < 40; i++)unibuf[i] = 0x00;
						for (i = 0; i < dotmax; i++)Dot01[i] = '\0';
						break;
					}
					else continue;
				}

			}
			if (unicount > 10) { 
				canttranse++;
				for (i = 0; i < 6; i++)hanziuni[i] = 0x00;
				for (i = 0; i < OneLineMax; i++) OneLine[i] = '\0';
				for (i = 0; i < 7; i++)OneDot[i] = '\0';
				LineSubscript = 0;
				for (i = 0; i < 40; i++)unibuf[i] = 0x00;
				for (i = 0; i < dotmax; i++)Dot01[i] = '\0';
				
			};
			
		}
	}
	fclose(Table);
	Merge_Sort_(OneAlwaysWords, SIZE1);
	Merge_Sort_(TwoAlwaysWords,SIZE2);
	Merge_Sort_(ThreeAlwaysWords, SIZE3);
	Merge_Sort_(FourAlwaysWord, SIZE4);
	Merge_Sort_(FiveAlwaysWord, SIZE5);
	Merge_Sort_(SixAlwaysWord, SIZE6);
	Merge_Sort_(SevenAlwaysWord, SIZE7);
	Merge_Sort_(EightAlwaysWord, SIZE8);
	Merge_Sort_(NineAlwaysWord, SIZE9);
	Merge_Sort_(TenAlwaysWord, SIZE10);


	int typecount = 0;
	int countsum = 0;
	int k;
	char kong[32] = { "\0" };
	for (k = 0; k < SIZE1; k++) {

		if (OneAlwaysWords[k].ciyu[0] == 0x0000 && OneAlwaysWords[k].ciyu[1] == 0x0000)continue;
		else {
			
			fwrite(OneAlwaysWords[k].ciyu, 2, 1, FlashTable);
			//fwrite(kong, 28, 1, FlashTable);
			fwrite(OneAlwaysWords[k].dot, 1, 62, FlashTable);
			typecount++;
		}
	}
	fwrite(&typecount, 4, 1, WordNumCount);
	printf("一个字的词有%d个\n", typecount);
	countsum = countsum + typecount;
	typecount = 0;


	for (k = 0; k < SIZE2; k++) {

		if (TwoAlwaysWords[k].ciyu[0] == 0x0000 && TwoAlwaysWords[k].ciyu[1] == 0x0000)continue;
		else {
			fwrite(TwoAlwaysWords[k].ciyu, 4, 1, FlashTable);
			//fwrite(kong, 28, 1, FlashTable);
			fwrite(TwoAlwaysWords[k].dot, 1, 60, FlashTable);
			typecount++;
		}
	}
	fwrite(&typecount, 4, 1, WordNumCount);
	printf("两个字的词有%d个\n", typecount);
	countsum = countsum + typecount;
	typecount = 0;


	for (k = 0; k < SIZE3; k++) {

		if (ThreeAlwaysWords[k].ciyu[0] == 0x0000 && ThreeAlwaysWords[k].ciyu[1] == 0x0000)continue;
		else {
			fwrite(ThreeAlwaysWords[k].ciyu, 6, 1, FlashTable);
			//fwrite(kong, 28, 1, FlashTable);
			fwrite(ThreeAlwaysWords[k].dot, 1, 58, FlashTable);
			typecount++;
		}
	}
	fwrite(&typecount, 4, 1, WordNumCount);
	printf("三个字的词有%d个\n", typecount);
	countsum = countsum + typecount;
	typecount = 0;


	for (k = 0; k < SIZE4; k++) {

		if (FourAlwaysWord[k].ciyu[0] == 0x0000 && FourAlwaysWord[k].ciyu[1] == 0x0000)continue;
		else {
			fwrite(FourAlwaysWord[k].ciyu, 8, 1, FlashTable);
			//fwrite(kong, 28, 1, FlashTable);
			fwrite(FourAlwaysWord[k].dot, 1, 120, FlashTable);
			typecount++;
		}
	}
	fwrite(&typecount, 4, 1, WordNumCount);
	printf("四个字的词有%d个\n", typecount);
	countsum = countsum + typecount;
	typecount = 0;

	for (k = 0; k < SIZE5; k++) {

		if (FiveAlwaysWord[k].ciyu[0] == 0x0000 && FiveAlwaysWord[k].ciyu[1] == 0x0000)continue;
		else {
			fwrite(FiveAlwaysWord[k].ciyu, 10, 1, FlashTable);
			//fwrite(kong, 28, 1, FlashTable);
			fwrite(FiveAlwaysWord[k].dot, 1, 118, FlashTable);
			typecount++;
		}
	}
	fwrite(&typecount, 4, 1, WordNumCount);
	printf("五个字的词有%d个\n", typecount);
	countsum = countsum + typecount;
	typecount = 0;

	for (k = 0; k < SIZE6; k++) {

		if (SixAlwaysWord[k].ciyu[0] == 0x0000 && SixAlwaysWord[k].ciyu[1] == 0x0000)continue;
		else {
			fwrite(SixAlwaysWord[k].ciyu, 12, 1, FlashTable);
			//fwrite(kong, 28, 1, FlashTable);
			fwrite(SixAlwaysWord[k].dot, 1, 116, FlashTable);
			typecount++;
		}
	}
	fwrite(&typecount, 4, 1, WordNumCount);
	printf("六个字的词有%d个\n", typecount);
	countsum = countsum + typecount;
	typecount = 0;

	for (k = 0; k < SIZE7; k++) {

		if (SevenAlwaysWord[k].ciyu[0] == 0x0000 && SevenAlwaysWord[k].ciyu[1] == 0x0000)continue;
		else {
			fwrite(SevenAlwaysWord[k].ciyu, 14, 1, FlashTable);
			//fwrite(kong, 28, 1, FlashTable);
			fwrite(SevenAlwaysWord[k].dot, 1, 242, FlashTable);
			typecount++;
		}
	}
	fwrite(&typecount, 4, 1, WordNumCount);
	printf("七个字的词有%d个\n", typecount);
	countsum = countsum + typecount;
	typecount = 0;

	for (k = 0; k < SIZE8; k++) {

		if (EightAlwaysWord[k].ciyu[0] == 0x0000 && EightAlwaysWord[k].ciyu[1] == 0x0000)continue;
		else {
			fwrite(EightAlwaysWord[k].ciyu, 16, 1, FlashTable);
			//fwrite(kong, 28, 1, FlashTable);
			fwrite(EightAlwaysWord[k].dot, 1, 240, FlashTable);
			typecount++;
		}
	}
	fwrite(&typecount, 4, 1, WordNumCount);
	printf("八个字的词有%d个\n", typecount);
	countsum = countsum + typecount;
	typecount = 0;


	for (k = 0; k < SIZE9; k++) {

		if (NineAlwaysWord[k].ciyu[0] == 0x0000 && NineAlwaysWord[k].ciyu[1] == 0x0000)continue;
		else {
			fwrite(NineAlwaysWord[k].ciyu, 18, 1, FlashTable);
			//fwrite(kong, 28, 1, FlashTable);
			fwrite(NineAlwaysWord[k].dot, 1, 238, FlashTable);
			typecount++;
		}
	}
	fwrite(&typecount, 4, 1, WordNumCount);
	printf("九个字的词有%d个\n", typecount);
	countsum = countsum + typecount;
	typecount = 0;

#if 0
	for (k = 0; k < SIZE10; k++) {

		if (TenAlwaysWord[k].ciyu[0] == 0x0000 && TenAlwaysWord[k].ciyu[1] == 0x0000)continue;
		else {
			fwrite(TenAlwaysWord[k].ciyu, 20, 1, FlashTable);
			//fwrite(kong, 28, 1, FlashTable);
			fwrite(TenAlwaysWord[k].dot, 1, 236, FlashTable);
			typecount++;
		}
	}
	fwrite(&typecount, 4, 1, WordNumCount);
	printf("十个字的词有%d个\n", typecount);
	countsum = countsum + typecount;
	typecount = 0;
#endif

	printf("共计词组%d个",countsum);
	fclose(FlashTable);
	return 0;
}