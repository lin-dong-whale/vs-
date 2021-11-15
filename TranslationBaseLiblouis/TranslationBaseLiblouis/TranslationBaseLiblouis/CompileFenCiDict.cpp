#include"CompileFenCiDict.h"
#include"utf-8tounicode.h"

#pragma warning(disable:4996)

#define SIZE2 179300
#define SIZE3 147830
#define SIZE4 188630
#define SIZE5 14630
#define SIZE6 7570
#define SIZE7 8200
#define SIZE8 1670
#define SIZE9 650
#define SIZE10 1000

typedef struct ciyu_2 {
	u16 ciyu[9];
}ciyu;
ciyu TwoWords[SIZE2]{};
ciyu ThreeWords[SIZE3]{};
ciyu FourWord[SIZE4]{};
ciyu FiveWord[SIZE5]{};
ciyu SixWord[SIZE6]{};
ciyu SevenWord[SIZE7]{};
ciyu EightWord[SIZE8]{};
ciyu NineWord[SIZE9]{};
ciyu TenWord[SIZE10]{};



typedef struct ciyu_3 {
	u16 ciyu[3];
}ciyu3;
typedef struct ciyu_4 {
	u16 ciyu[4];
}ciyu4;
typedef struct ciyu_5 {
	u16 ciyu[5];
}ciyu5;
typedef struct ciyu_6 {
	u16 ciyu[6];
}ciyu6;
typedef struct ciyu_7 {
	u16 ciyu[7];
}ciyu7;
typedef struct ciyu_8 {
	u16 ciyu[8];
}ciyu8;
typedef struct ciyu_9 {
	u16 ciyu[9];
}ciyu9;


int SortTwoWords(int WordNum) {
	int i,j,k;
	int change = 0;
	u16 temp;
	for (i = SIZE2; i >0; i--) {
		change = 0;
		for (j = SIZE2-1; j >0; j--) {
			change = 0;
			for(k=0;k<WordNum;k++){
				if (TwoWords[j].ciyu[k] < TwoWords[j - 1].ciyu[k]) { 
					change = 1; 
					break;
				}
				else if (TwoWords[j].ciyu[k] == TwoWords[j - 1].ciyu[k]) {
					continue;
				}
				else { 
					change = 0;
					break;
				}
			}
			
			if (change == 1) {
				for (k = 0; k < WordNum; k++) {
					temp = TwoWords[j - 1].ciyu[k];
					TwoWords[j - 1].ciyu[k] = TwoWords[j].ciyu[k];
					TwoWords[j].ciyu[k] = temp;
				}

			}

		}
	}
	return 0;
}

int SortThreeWords(int WordNum) {
	int i, j, k;
	int change = 0;
	u16 temp;
	for (i = SIZE3; i > 0; i--) {
		change = 0;
		for (j = SIZE3-1; j > 0; j--) {
			change = 0;
			for (k = 0; k < WordNum; k++) {
				if (ThreeWords[j].ciyu[k] < ThreeWords[j - 1].ciyu[k]) {
					change = 1;
					break;
				}
				else if (ThreeWords[j].ciyu[k] == ThreeWords[j - 1].ciyu[k]) {
					continue;
				}
				else {
					change = 0;
					break;
				}
			}

			if (change == 1) {
				for (k = 0; k < WordNum; k++) {
					temp = ThreeWords[j - 1].ciyu[k];
					ThreeWords[j - 1].ciyu[k] = ThreeWords[j].ciyu[k];
					ThreeWords[j].ciyu[k] = temp;
				}

			}

		}
	}
	return 0;
}

int SortFourWords(int WordNum) {
	int i, j, k;
	int change = 0;
	u16 temp;
	for (i = SIZE4; i > 0; i--) {
		change = 0;
		for (j = SIZE4-1; j > 0; j--) {
			change = 0;
			for (k = 0; k < WordNum; k++) {
				if (FourWord[j].ciyu[k] < FourWord[j - 1].ciyu[k]) {
					change = 1;
					break;
				}
				else if (FourWord[j].ciyu[k] == FourWord[j - 1].ciyu[k]) {
					continue;
				}
				else {
					change = 0;
					break;
				}
			}

			if (change == 1) {
				for (k = 0; k < WordNum; k++) {
					temp = FourWord[j - 1].ciyu[k];
					FourWord[j - 1].ciyu[k] = FourWord[j].ciyu[k];
					FourWord[j].ciyu[k] = temp;
				}

			}

		}
	}
	return 0;
}

int SortFiveWords(int WordNum) {
	int i, j, k;
	int change = 0;
	u16 temp;
	for (i = SIZE5; i > 0; i--) {
		change = 0;
		for (j = SIZE5-1; j > 0; j--) {
			change = 0;
			for (k = 0; k < WordNum; k++) {
				if (FiveWord[j].ciyu[k] < FiveWord[j - 1].ciyu[k]) {
					change = 1;
					break;
				}
				else if (FiveWord[j].ciyu[k] == FiveWord[j - 1].ciyu[k]) {
					continue;
				}
				else {
					change = 0;
					break;
				}
			}

			if (change == 1) {
				for (k = 0; k < WordNum; k++) {
					temp = FiveWord[j - 1].ciyu[k];
					FiveWord[j - 1].ciyu[k] = FiveWord[j].ciyu[k];
					FiveWord[j].ciyu[k] = temp;
				}

			}

		}
	}
	return 0;
}

int SortSixWords(int WordNum) {
	int i, j, k;
	int change = 0;
	u16 temp;
	for (i = SIZE6; i > 0; i--) {
		change = 0;
		for (j = SIZE6-1; j > 0; j--) {
			change = 0;
			for (k = 0; k < WordNum; k++) {
				if (SixWord[j].ciyu[k] < SixWord[j - 1].ciyu[k]) {
					change = 1;
					break;
				}
				else if (SixWord[j].ciyu[k] == SixWord[j - 1].ciyu[k]) {
					continue;
				}
				else {
					change = 0;
					break;
				}
			}

			if (change == 1) {
				for (k = 0; k < WordNum; k++) {
					temp = SixWord[j - 1].ciyu[k];
					SixWord[j - 1].ciyu[k] = SixWord[j].ciyu[k];
					SixWord[j].ciyu[k] = temp;
				}

			}

		}
	}
	return 0;
}

int SortSevenWords(int WordNum) {
	int i, j, k;
	int change = 0;
	u16 temp;
	for (i = SIZE7; i > 0; i--) {
		change = 0;
		for (j = SIZE7-1; j > 0; j--) {
			change = 0;
			for (k = 0; k < WordNum; k++) {
				if (SevenWord[j].ciyu[k] < SevenWord[j - 1].ciyu[k]) {
					change = 1;
					break;
				}
				else if (SevenWord[j].ciyu[k] == SevenWord[j - 1].ciyu[k]) {
					continue;
				}
				else {
					change = 0;
					break;
				}
			}

			if (change == 1) {
				for (k = 0; k < WordNum; k++) {
					temp = SevenWord[j - 1].ciyu[k];
					SevenWord[j - 1].ciyu[k] = SevenWord[j].ciyu[k];
					SevenWord[j].ciyu[k] = temp;
				}

			}

		}
	}
	return 0;
}

int SortEightWords(int WordNum) {
	int i, j, k;
	int change = 0;
	u16 temp;
	for (i = SIZE8; i > 0; i--) {
		change = 0;
		for (j = SIZE8-1; j > 0; j--) {
			change = 0;
			for (k = 0; k < WordNum; k++) {
				if (EightWord[j].ciyu[k] < EightWord[j - 1].ciyu[k]) {
					change = 1;
					break;
				}
				else if (EightWord[j].ciyu[k] == EightWord[j - 1].ciyu[k]) {
					continue;
				}
				else {
					change = 0;
					break;
				}
			}

			if (change == 1) {
				for (k = 0; k < WordNum; k++) {
					temp = EightWord[j - 1].ciyu[k];
					EightWord[j - 1].ciyu[k] = EightWord[j].ciyu[k];
					EightWord[j].ciyu[k] = temp;
				}

			}

		}
	}
	return 0;
}

int SortNineWords(int WordNum) {
	int i, j, k;
	int change = 0;
	u16 temp;
	for (i = SIZE9-1; i > 0; i--) {
		change = 0;
		for (j = SIZE9-1; j > 0; j--) {
			change = 0;
			for (k = 0; k < WordNum; k++) {
				if (NineWord[j].ciyu[k] < NineWord[j - 1].ciyu[k]) {
					change = 1;
					break;
				}
				else if (NineWord[j].ciyu[k] == NineWord[j - 1].ciyu[k]) {
					continue;
				}
				else {
					change = 0;
					break;
				}
			}

			if (change == 1) {
				for (k = 0; k < WordNum; k++) {
					temp = NineWord[j - 1].ciyu[k];
					NineWord[j - 1].ciyu[k] = NineWord[j].ciyu[k];
					NineWord[j].ciyu[k] = temp;
				}

			}

		}
	}
	return 0;
}

void Merge(ciyu Word[], int left, int mid, int right) {
	int len = right - left + 1;
	ciyu *temp=new ciyu[len];
	//ciyu temp[2];
	int k = 0;
	int l = 0;
	int i = left;
	int j = mid + 1;
	int change = 0;
	while (i <= mid && j <= right) {
		change = 0;
		for (l = 0; l < 9; l++) {
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
			for (l= 0; l < 9; l++) {
				temp[k].ciyu[l] = Word[i].ciyu[l];
			}
			i++;

		}
		else {
			for (l = 0; l < 9; l++) {
				temp[k].ciyu[l] = Word[j].ciyu[l];
				
			}
			j++;
		}
		k++;	
	}

	while (i <= mid) {
		for (l = 0; l < 9; l++) {
			temp[k].ciyu[l] = Word[i].ciyu[l];
		}
		k++;
		i++;
	}
	while (j <= right) {
		for (l = 0; l < 9; l++) {
			temp[k].ciyu[l] = Word[j].ciyu[l];
		}
		k++;
		j++;
	}
	for (k = 0; k < len; k++) {
		for(l=0;l<9;l++){
			Word[left].ciyu[l] = temp[k].ciyu[l];
		}
		left = left + 1;
	}

}
void MergeSort(ciyu Word[],int left,int right) {
	if (left == right)return;
	int mid = (left + right)/2;
	MergeSort(Word, left, mid);
	MergeSort(Word, mid+1, right);
	Merge(Word, left, mid, right);
}

int Merge_Sort(ciyu Word[],int SIZE) {

	MergeSort(Word,0,SIZE-1);

	return 0;
}



int GetAndWriteFenCi() {

	u8 OneLine[60] = { '\0' };
	u8 ch;
	u16 unibuf[40] = { 0x0000 };

	int i = 0;
	int j = 0;
	int unibufsize=0;

	FILE* Table = fopen("D:\\LD\\vc-c\\TranslationBaseLiblouis\\test.txt", "r");
	FILE* FlashTable = fopen("D:\\LD\\vc-c\\TranslationBaseLiblouis\\FenciTable.txt", "wb");//以二进制文件写入，防止用“w”模式出现要写入0x0a（回车的ASCII码）自动补齐0x0d0x0a（换行加回车）的情况
	FILE* WordNumCount = fopen("D:\\LD\\vc-c\\TranslationBaseLiblouis\\WordNumCount.txt", "wb");
	if (Table == (FILE*)NULL) {
		printf("open dict fileerror !\n");
		return -1;
	}
	while (!feof(Table)) {
		ch = fgetc(Table);
		if (ch!='\n') {//获取一行的内容
			OneLine[i] = ch;
			i++;

		}
		else {
			printf("我还在!我没死!");
		
			StringToUni(OneLine,unibuf,strlen((const char*)OneLine));//一行内容转换为Unicode
			unibufsize = 0;
			for(i=0;i<sizeof(unibuf)/sizeof(unibuf[0]);i++){
				if (unibuf[i] != 0x0000)unibufsize = unibufsize + 2;
			}

		
			if (unibufsize == 4) {
				for (i = 0; i < SIZE2; i++) {
					if (TwoWords[i].ciyu[0] == '\0') {
						for ( j=0; j < 2; j++) {
							TwoWords[i].ciyu[j] = unibuf[j];
						}
						break;
					}
					else continue;

				}
			}
			if (unibufsize == 6) {
				for (i = 0; i < SIZE3; i++) {
					if (ThreeWords[i].ciyu[0] == '\0') {
						for ( j = 0; j < 3; j++) {
							ThreeWords[i].ciyu[j] = unibuf[j];
						}
						break;
					}
					else continue;

				}
			}
			if (unibufsize == 8) {
				for (i = 0; i < SIZE4; i++) {
					if (FourWord[i].ciyu[0] == '\0') {
						for (j = 0; j < 4; j++) {
							FourWord[i].ciyu[j] = unibuf[j];
						}
						break;
					}
					else continue;

				}
			}

			if (unibufsize == 10) {
				for (i = 0; i < SIZE5; i++) {
					if (FiveWord[i].ciyu[0] == '\0') {
						for (j = 0; j < 5; j++) {
							FiveWord[i].ciyu[j] = unibuf[j];
						}
						break;
					}
					else continue;

				}
			}
			if (unibufsize == 12) {
				for (i = 0; i < SIZE6; i++) {
					if (SixWord[i].ciyu[0] == '\0') {
						for (j = 0; j < 6; j++) {
							SixWord[i].ciyu[j] = unibuf[j];
						}
						break;
					}
					else continue;

				}
			}
			if (unibufsize == 14) {
				for (i = 0; i < SIZE7; i++) {
					if (SevenWord[i].ciyu[0] == '\0') {
						for (j = 0; j < 7; j++) {
							SevenWord[i].ciyu[j] = unibuf[j];
						}
						break;
					}
					else continue;

				}
			}
			if (unibufsize == 16) {
				for (i = 0; i < SIZE8; i++) {
					if (EightWord[i].ciyu[0] == '\0') {
						for (j = 0; j < 8; j++) {
							EightWord[i].ciyu[j] = unibuf[j];
						}
						break;
					}
					else continue;

				}
			}
			if (unibufsize == 18) {
				for (i = 0; i < SIZE9; i++) {
					if (NineWord[i].ciyu[0] == '\0') {
						for (j = 0; j < 9; j++) {
							NineWord[i].ciyu[j] = unibuf[j];
						}
						break;
					}
					else continue;

				}
			}
			if (unibufsize == 20) {
				for (i = 0; i < SIZE10; i++) {
					if (NineWord[i].ciyu[0] == '\0') {
						for (j = 0; j < 10; j++) {
							TenWord[i].ciyu[j] = unibuf[j];
						}
						break;
					}
					else continue;

				}
			}

			for (j = 0; j < 60; j++) OneLine[j] = '\0';
			for (j = 0; j < 40; j++)unibuf[j] = 0x0000;
			
			i = 0;
			printf("我一行写到结构体里了！");
		}

	
	
	}


	fclose(Table);
	Merge_Sort(TwoWords, SIZE2); printf("2个字排序好了\n");
	Merge_Sort(ThreeWords, SIZE3); printf("3个字排序好了\n");
	Merge_Sort(FourWord, SIZE4); printf("4个字排序好了\n");
	Merge_Sort(FiveWord, SIZE5); printf("5个字排序好了\n");
	Merge_Sort(SixWord, SIZE6); printf("6个字排序好了\n");
	Merge_Sort(SevenWord, SIZE7); printf("7个字排序好了\n");
	Merge_Sort(EightWord, SIZE8); printf("8个字排序好了\n");
	Merge_Sort(NineWord, SIZE9); printf("9个字排序好了\n");
	Merge_Sort(TenWord, SIZE10); printf("10个字排序好了\n");
	/*
	SortTwoWords(2); printf("2个字排序好了");
	
	SortThreeWords(3); printf("3个字排序好了");
	SortFourWords(4); printf("4个字排序好了");
	SortFiveWords(5); printf("5个字排序好了");
	SortSixWords(6); printf("6个字排序好了");
	SortSevenWords(7); printf("7个字排序好了");
	SortEightWords(8); printf("8个字排序好了");
	SortNineWords(9); printf("9个字排序好了");*/
	int typecount=0;
	int countsum = 0;
	int k;
	char kong[32] = { "\0" };
	for (k = 0; k < SIZE2; k++) {
	
		if (TwoWords[k].ciyu[0] == 0x0000 && TwoWords[k].ciyu[1] == 0x0000)continue;
		else {
			fwrite(TwoWords[k].ciyu,4,1,FlashTable);
			fwrite(kong, 28, 1, FlashTable);
			typecount++;
		}
	}
	fwrite(&typecount, 4, 1, WordNumCount); 
	printf("两个字的词有%d个\n", typecount);
	countsum = countsum + typecount;
	typecount = 0;

	for (k = 0; k < SIZE3; k++) {

		if (ThreeWords[k].ciyu[0] == 0x0000 && ThreeWords[k].ciyu[1] == 0x0000)continue;
		else {
			fwrite(ThreeWords[k].ciyu, 6, 1, FlashTable);
			fwrite(kong, 26, 1, FlashTable);
			typecount++;
		}
	}
	fwrite(&typecount, 4, 1, WordNumCount); 
	printf("三个字的词有%d个\n", typecount);
	countsum = countsum + typecount;
	typecount = 0;

	for (k = 0; k < SIZE4; k++) {

		if (FourWord[k].ciyu[0] == 0x0000 && FourWord[k].ciyu[1] == 0x0000)continue;
		else {
			fwrite(FourWord[k].ciyu, 8, 1, FlashTable);
			fwrite(kong, 24, 1, FlashTable);
			typecount++;
		}
	}
	fwrite(&typecount, 4, 1, WordNumCount); 
	printf("四个字的词有%d个\n", typecount);
	countsum = countsum + typecount;
	typecount = 0;

	for (k = 0; k < SIZE5; k++) {

		if (FiveWord[k].ciyu[0] == 0x0000 && FiveWord[k].ciyu[1] == 0x0000)continue;
		else {
			fwrite(FiveWord[k].ciyu, 10, 1, FlashTable);
			fwrite(kong, 22, 1, FlashTable);
			typecount++;
		}
	}
	fwrite(&typecount, 4, 1, WordNumCount); 
	printf("五个字的词有%d个\n", typecount);
	countsum = countsum + typecount;
	typecount = 0;

	for (k = 0; k < SIZE6; k++) {

		if (SixWord[k].ciyu[0] == 0x0000 && SixWord[k].ciyu[1] == 0x0000)continue;
		else {
			fwrite(SixWord[k].ciyu, 12, 1, FlashTable);
			fwrite(kong, 20, 1, FlashTable);
			typecount++;
		}
	}
	fwrite(&typecount, 4, 1, WordNumCount); 
	printf("六个字的词有%d个\n", typecount);
	countsum = countsum + typecount;
	typecount = 0;

	for (k = 0; k < SIZE7; k++) {

		if (SevenWord[k].ciyu[0] == 0x0000 && SevenWord[k].ciyu[1] == 0x0000)continue;
		else {
			fwrite(SevenWord[k].ciyu, 14, 1, FlashTable);
			fwrite(kong, 18, 1, FlashTable);
			typecount++;
		}
	}
	fwrite(&typecount, 4, 1, WordNumCount); 
	printf("七个字的词有%d个\n", typecount);
	countsum = countsum + typecount;
	typecount = 0;

	for (k = 0; k < SIZE8; k++) {

		if (EightWord[k].ciyu[0] == 0x0000 && EightWord[k].ciyu[1] == 0x0000)continue;
		else {
			fwrite(EightWord[k].ciyu, 16, 1, FlashTable);
			fwrite(kong, 16, 1, FlashTable);
			typecount++;
		}
	}
	fwrite(&typecount, 4, 1, WordNumCount); 
	printf("八个字的词有%d个\n", typecount);
	countsum = countsum + typecount;
	typecount = 0;


	for (k = 0; k < SIZE9; k++) {

		if (NineWord[k].ciyu[0] == 0x0000 && NineWord[k].ciyu[1] == 0x0000)continue;
		else {
			fwrite(NineWord[k].ciyu, 18, 1, FlashTable);
			fwrite(kong, 14, 1, FlashTable);
			typecount++;
		}
	}
	fwrite(&typecount, 4, 1, WordNumCount); 
	printf("九个字的词有%d个\n", typecount);
	countsum = countsum + typecount;
	typecount = 0;

	for (k = 0; k < SIZE10; k++) {

		if (TenWord[k].ciyu[0] == 0x0000 && TenWord[k].ciyu[1] == 0x0000)continue;
		else {
			fwrite(TenWord[k].ciyu, 20, 1, FlashTable);
			fwrite(kong, 12, 1, FlashTable);
			typecount++;
		}
	}
	fwrite(&typecount, 4, 1, WordNumCount);
	printf("十个字的词有%d个\n", typecount);
	countsum = countsum + typecount;
	typecount = 0;


	printf("总共有%d个词语\n", countsum);
	fclose(FlashTable);
	return 0;
}