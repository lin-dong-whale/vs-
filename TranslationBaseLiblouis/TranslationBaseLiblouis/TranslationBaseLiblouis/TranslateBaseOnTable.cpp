#include <stdio.h>
#include <string.h>
#include<malloc.h>
#include"USGrade1Trans.h"
#include<malloc.h>
#include "TranslateBaseOnTable.h"
#include"mySegmentation.h"
#pragma execution_character_set("utf-8")
#pragma warning(suppress : 4996)

/*
char tablepath[] = ".\\Debug\\FlashTable.txt";//使用的字典路径
#define WORD_ITEM_LEN123	64//这个字典一个字的词条存放的字节数,下面是4-5，7-9的字节数
#define WORD_ITEM_LEN456	128
#define WORD_ITEM_LEN789	256
#define WORD_ITEM_MAXCNT	9//这个字典词条最大的汉字个数

#define ONE_CHN 20985  //一个字的词条个数
#define TWO_CHN 29516
#define THREE_CHN 880
#define FOUR_CHN 1184
#define FIVE_CHN 49
#define SIX_CHN 36
#define SEVEN_CHN 20
#define EIGHT_CHN 11
#define NINE_CHN 11

#define ONE_CHN_START      0//文件中一个字词条的起始位置
#define ONE_CHN_END        ONE_CHN_START + ONE_CHN * WORD_ITEM_LEN123-WORD_ITEM_LEN123//文件最后一个词条的起始位置

#define TWO_CHN_START      ONE_CHN_END+WORD_ITEM_LEN123
#define TWO_CHN_END        TWO_CHN_START+TWO_CHN*WORD_ITEM_LEN123-WORD_ITEM_LEN123

#define THREE_CHN_START    TWO_CHN_END+WORD_ITEM_LEN123
#define THREE_CHN_END      THREE_CHN_START+THREE_CHN*WORD_ITEM_LEN123-WORD_ITEM_LEN123

#define FOUR_CHN_START     THREE_CHN_END+WORD_ITEM_LEN123
#define FOUR_CHN_END       FOUR_CHN_START+FOUR_CHN*WORD_ITEM_LEN456-WORD_ITEM_LEN456

#define FIVE_CHN_START     FOUR_CHN_START+WORD_ITEM_LEN456
#define FIVE_CHN_END       FIVE_CHN_START+FIVE_CHN*WORD_ITEM_LEN456-WORD_ITEM_LEN456

#define SIX_CHN_START     FIVE_CHN_END+WORD_ITEM_LEN456
#define SIX_CHN_END       SIX_CHN_START+SIX_CHN*WORD_ITEM_LEN456-WORD_ITEM_LEN456

#define SEVEN_CHN_START     SIX_CHN_END+WORD_ITEM_LEN456
#define SEVEN_CHN_END       SEVEN_CHN_START+SEVEN_CHN*WORD_ITEM_LEN789-WORD_ITEM_LEN789

#define EIGHT_CHN_START     SEVEN_CHN_END+WORD_ITEM_LEN789
#define EIGHT_CHN_END       EIGHT_CHN_START+EIGHT_CHN*WORD_ITEM_LEN789-WORD_ITEM_LEN789

#define NINE_CHN_START     EIGHT_CHN_END+WORD_ITEM_LEN789
#define NINE_CHN_END       NINE_CHN_START+NINE_CHN*WORD_ITEM_LEN789-WORD_ITEM_LEN789

*/


//#define isChCharacter(a) (((a >= 0x4E00 && a <= 0x9FFF) || (a >= 0x3400 && a <= 0x4DBF) || (a >= 0xF900 && a <= 0xFAFF)) ? 1 : 0)



#define CHARMAX 100//一段待翻译英文的最大长度
#define SAMETYPE 30//同种类型字符的最大长度
#define ONEWORDMAX 30//由空格切分的一个词 的最大长度
#define DOTNUMMAX 500

enum MyEnum
{
	CHPUNC,
	PREPUNC,
	POSTPUNC,
	ALWAYS,
	BEGNUM,
	MIDNUM,
	ENDNUM,

	CAPITAL,
	LOWER,
	NUM,

	DECPINT,
	HYPHEN,
	PUNC,
	SPACE,
	EMPTY,



}CharacterType;

typedef struct CharacterLinkList {
	u16 OneTypeChar[SAMETYPE];//同种类型的字符放在一起
	enum MyEnum CharacterType;//这段字符的类型
	struct CharacterLinkList* previous;//前一断字符
	struct CharacterLinkList* next;//后一个
	int len;


}Linklist;

typedef struct TranslateTable {
	u16 unicode;
	char numdot[15];
	char Dot01[25];
}EnTable;

typedef struct TranslateTables {
	char unicode[4];
	char numdot[25];
	char Dot01[25];
}Tables;

typedef struct TranslateTabless {
	char unicode[7];
	char numdot[20];
	char Dot01[25];
}Tabless;


EnTable Prepunc[]{
 {'\"',"236-","011001"},
 {'\'',"6-236-","000001011001"},
{'(',"2356-","011011"},
{'`',"236-","011001"},
{'`',"6-236-","000001011001"},

{'’',"356-3-","001001001000"},

/*
{'\'',"6-236-"},
{'[',"6-2356-"},
{'{',"56-2356-"},
*/
};
EnTable Postpunc[]{


{'"',"356-","001011"},
{'\'',"356-3-","001011001000"},
{')',"2356-","011011"},
{'`',"6-236-","000001011001"},
{'’',"356-3-","001011001000"},

/*
{',',"2-"},
{'.',"256-"},
{';',"23-"},
{':',"25-"},
{'!',"235-"},
{'?',"236-"},
{'}',"2356-23-"},
{']',"2356-3-"},
*/

};

EnTable always[]{
	{'#',"4-3456-","000100001111"},
	{'/',"456-34-","000111001100"},
	{'^',"456-126-","000111110001"},
	{'~',"4-156-","000100100011"},
{'&',"4-12346-","000100111101"},
{'[',"6-2356-","000001011011"},
{']',"2356-3-","011011001000"},
{'{',"46-2356-","000101011011"},
{'}',"46-2356-","000101011011"},
{'%',"25-1234-","010010111100"},
{'*',"35-35-","001010001010"},
{'‘',"6-236-","000001011001"},
{'|',"5-123-","000010111000"},
{'£',"4-123-","000100111000"},
{0x2013,"56-36-","000011001001"},


{'\'',"3-","001000"},
{',',"2-","010000"},
{'.',"256-","010011"},
{';',"23-","011000"},
{':',"25-","010010"},
{'!',"235-","011010"},
{'?',"236-","011001"},
{'?',"236-","011001"},
{'>',"135-","101010"},
{'`',"4-","000100"},
{'(',"2356-","011011"},
{'@',"2346-","011101"},
{'<',"246-","010101"},
{0x2212,"36-","001001"},

{0x201C,"236-","011001"},
{0x201D,"356-","001011"},
{0x201E,"236-","011001"},
{0x201F,"356-","001011"},

/*
	{':',"4-25-"},
{'!',"4-235-"},
{'/',"456-34-"},
{'<',"5-13-"},
{'=',"46-13-"},
{'>',"46-2-"},
{'+',"4-346-"},


{'@',"4-1-"},
{'\\',"4-1256-"},

{'$',"4-256-"},
{'-',"36-"},
*/

{'，',"5-","000010000000"},
{0xff0c,"5-","000010000000"},

{'、',"6-","000001000000"},
{0x3001,"6-","000001000000"},
{'；',"56-","000011000000"},
{0xff1b,"56-","000011000000"},
{'：',"6-3-","000001001000000000"},
{0xff1a,"6-3-","000001001000000000"},
{'…',"5-5-5-","000010000010000010000000"},
{0x2026,"5-5-5-","000010000010000010000000"},

{'。',"5-23-","000010011000"},
{0x3002,"5-23-","000010011000"},
{'？',"5-3-","000010001000"},
{0xff1f,"5-3-","000010001000"},
{'！',"56-2-","000011010000"},
{0xff01,"56-2-","000011010000"},
{'“',"","000011001000"},
{0x201c,"","000011001000"},
{'”',"","000001011000"},
{0x201d,"","000001011000"},
{'‘',"","000001011001"},
{0x2018,"","000001011001"},
{'’',"","001011001000"},
{0x2019,"","001011001000"},
{'《',"","000010001001"},
{0x300a,"","000010001001"},
{'》',"","001001010000"},
{0x300b,"","001001010000"},
{'〈 ',"","000010001000"},
{0x3008,"","000010001000"},
{'〉',"","000010001000"},
{0x3009,"","000010001000"},
{'（',"","000011001001"},
{0xff08,"","000011001001"},
{'）',"","001001011000"},
{0xff09,"","001001011000"},
{'【',"","000011011000"},
{0x3010,"","000011011000"},
{'】',"","000011011000"},
{0x3011,"","000011011000"},
{'—',"","000001001001001001001000"},
{0x2014,"","000001001001001001001000"},
};

EnTable Chpunc[]{
	{'#',"4-3456-","000100001111"},
	{'/',"456-34-","000111001100"},
	{'^',"456-126-","000111110001"},
	{'~',"4-156-","000100100011"},
{'&',"4-12346-","000100111101"},
{'[',"6-2356-","000001011011"},
{']',"2356-3-","011011001000"},
{'{',"46-2356-","000101011011"},
{'}',"46-2356-","000101011011"},
{'%',"25-1234-","010010111100"},
{'*',"35-35-","001010001010"},
{'‘',"6-236-","000001011001"},
{'|',"5-123-","000010111000"},
{'£',"4-123-","000100111000"},
{0x2013,"56-36-","000011001001"},


{'\'',"3-","001000"},
{',',"2-","010000"},
{'.',"256-","010011"},
{';',"23-","011000"},
{':',"25-","010010"},
{'!',"235-","011010"},
{'?',"236-","011001"},
{'?',"236-","011001"},
{'>',"135-","101010"},
{'`',"4-","000100"},
{'(',"2356-","011011"},
{'@',"2346-","011101"},
{'<',"246-","010101"},
//{0x2212,"36-","001001"},

//{0x201C,"236-","011001"},
//{0x201D,"356-","001011"},
//{0x201E,"236-","011001"},
{0x201F,"356-","001011"},

/*
	{':',"4-25-"},
{'!',"4-235-"},
{'/',"456-34-"},
{'<',"5-13-"},
{'=',"46-13-"},
{'>',"46-2-"},
{'+',"4-346-"},


{'@',"4-1-"},
{'\\',"4-1256-"},

{'$',"4-256-"},
{'-',"36-"},
*/
{'。',"5-23-","000010011000"},
{0x3002,"5-23-","000010011000"},
{'，',"5-","000010000000"},
{0xff0c,"5-","000010000000"},
{'、',"4-","000100000000"},
{0x3001,"4-","000100000000"},
{'；',"56-","000011000000"},
{0xff1b,"56-","000011000000"},
{'？',"5-3-","000010001000"},
{0xff1f,"5-3-","000010001000"},
{'！',"56-2-","000011010000"},
{0xff01,"56-2-","000011010000"},
{'：',"36-","001001000000"},
{0xff1a,"36-","001001000000"},
{'“',"","000110"},
{0x201c,"","000110"},
{'”',"","000110"},
{0x201d,"","000110"},
{'‘',"","000001011001"},
{0x2018,"","000001011001"},
{'’',"","001011001000"},
{0x2019,"","001011001000"},
{'（',"","000011001000"},
{0xff08,"","000011001000"},
{'）',"","000001011000"},
{0xff09,"","000001011000"},
{'【',"","000011011000"},
{0x3010,"","000011011000"},
{'】',"","000011011000"},
{0x3011,"","000011011000"},
{'《',"","000010001001"},
{0x300a,"","000010001001"},
{'》',"","001001010000"},
{0x300b,"","001001010000"},
{'〈 ',"","000010001000"},
{0x3008,"","000010001000"},
{'〉',"","000010001000"},
{0x3009,"","000010001000"},
{'—',"","000001001001"},
{0x2014,"","000001001001"},
{'…',"5-5-5-","000010000010000010000000"},
{0x2026,"5-5-5-","000010000010000010000000"},

};



EnTable Midnum[]{
	{',',"3-","001000"},
	{'.',"2","010000"},
	{':',"3456-","001111"},
	{'/',"456-34-3456-","000111001100001111"},
	{'^',"346-3456-","001101001111"},
	{'*',"0-56-236-3456-","000000000011011001001111"},
	{'-',"36-3456-","001001001111"},
	//{0x2013,"36-"},
	{'÷',"0-56-256-3456-","000000000011010011001111"},
	{'+',"0-56-235-3456-","000000000011011010001111"},
	{0x2013,"36-3456-","001001001111"},
	//{0x00ad,"36-"},
};
EnTable Deception[]{
	{'.',"2-","010000"}
};

EnTable hyphen[]{
	{'-',"36-","001001"}
};

EnTable Begnum[]{
	{'#',"4-","000100"},
	{'£',"123-","111000"},
	{'+',"56-235-","000011011010"},
};

EnTable joinnum[]{
	{'+',"56-235-","000011011010"},
	{'=',"56-2356-","000011011011"},
	{'×',"56-236-","000011011001"},
	{'÷',"56-256-","000011010011"},

};


EnTable litdigit[]{
{'0',"245-","010110"},
{'1',"1-","100000"},
{'2',"12-","110000"},
{'3',"14-","100100"},
{'4',"145-","100110"},
{'5',"15-","100010"},
{'6',"124-","110100"},
{'7',"1245-","110110"},
{'8',"125-","110010"},
{'9',"24-","010100"},

};


EnTable capital[]{
{'A',"1-","100000"},
{'B',"12-","110000"},
{'C',"14-","100100"},
{'D',"145-","100110"},
{'E',"15-","100010"},
{'F',"124-","110100"},
{'G',"1245-","110110"},
{'H',"125-","110010"},
{'I',"24-","010100"},
{'J',"245-","010110"},
{'K',"13-","101000"},
{'L',"123-","111000"},
{'M',"134-","101100"},
{'N',"1345-","101110"},
{'O',"135-","101010"},
{'P',"1234-","111100"},
{'Q',"12345-","111110"},
{'R',"1235-","111010"},
{'S',"234-","011100"},
{'T',"2345-","011110"},
{'U',"136-","101001"},
{'V',"1236-","111001"},
{'W',"2456-","010111"},
{'X',"1346-","101101"},
{'Y',"13456-","101111"},
{'Z',"1356-","101011"},

};

EnTable lower[]{
{'a',"1-","100000"},
{'b',"12-","110000"},
{'c',"14-","100100"},
{'d',"145-","100110"},
{'e',"15-","100010"},
{'f',"124-","110100"},
{'g',"1245-","110110"},
{'h',"125-","110010"},
{'i',"24-","010100"},
{'j',"245-","010110"},
{'k',"13-","101000"},
{'l',"123-","111000"},
{'m',"134-","101100"},
{'n',"1345-","101110"},
{'o',"135-","101010"},
{'p',"1234-","111100"},
{'q',"12345-","111110"},
{'r',"1235-","111010"},
{'s',"234-","011100"},
{'t',"2345-","011110"},
{'u',"136-","101001"},
{'v',"1236-","111001"},
{'w',"2456-","010111"},
{'x',"1346-","101101"},
{'y',"13456-","101111"},
{'z',"1356-","101011"},
};





int changetype(Linklist* head) {//判断修改每个节点的字符类型
	Linklist* currentlink=NULL;//###
	Linklist* nood=NULL;//###
	int endflag = 0;
	currentlink = head;
	while (1) {
		switch (currentlink->CharacterType)
		{
		case CAPITAL:
			if (currentlink->next == NULL)endflag = 1;
			currentlink = currentlink->next;
			break;

		case LOWER:

			if (currentlink->next == NULL)endflag = 1;
			currentlink = currentlink->next;
			break;
		case NUM:
			if (currentlink->next == NULL)endflag = 1;
			currentlink = currentlink->next;
			break;
		case PUNC:
			if (currentlink->previous == NULL) {

				currentlink->CharacterType = PREPUNC;

				if (currentlink->next->CharacterType == NUM)currentlink->CharacterType = BEGNUM;
				if (currentlink->next->CharacterType == NUM && (currentlink->OneTypeChar[0] == '#' || currentlink->OneTypeChar[0] == '$'))currentlink->CharacterType = BEGNUM;
				if (currentlink->OneTypeChar[0] == '.' && currentlink->len == 1 && currentlink->next->CharacterType == NUM)currentlink->CharacterType = DECPINT;
				if (currentlink->OneTypeChar[0] == '-' && currentlink->len == 1 && currentlink->next->CharacterType == NUM)currentlink->CharacterType = HYPHEN;

			}
			

			if (currentlink->previous != NULL) {
				if (currentlink->next == NULL) {
					//if (currentlink->CharacterType == CAPITAL || currentlink->CharacterType == LOWER)currentlink->CharacterType = POSTPUNC;
					currentlink->CharacterType = POSTPUNC;
					
					if (currentlink->previous->CharacterType == NUM)currentlink->CharacterType = ENDNUM;

				}
				else {
					if (currentlink->previous->CharacterType == SPACE)currentlink->CharacterType = PREPUNC;
					//if(currentlink->next->CharacterType==SPACE&&(currentlink->previous-> CharacterType==CAPITAL||currentlink->previous->CharacterType==LOWER))currentlink->CharacterType = POSTPUNC;
					if (currentlink->next->CharacterType == SPACE)currentlink->CharacterType = POSTPUNC;
					if (currentlink->next->CharacterType == NUM && currentlink->previous->CharacterType != NUM)currentlink->CharacterType = BEGNUM;
					if (currentlink->previous->CharacterType == NUM && currentlink->next->CharacterType == NUM)currentlink->CharacterType = MIDNUM;
					if (currentlink->OneTypeChar[0] == '.' && currentlink->len == 1 && currentlink->next->CharacterType == NUM)currentlink->CharacterType = DECPINT;
					if (currentlink->OneTypeChar[0] == '-' && currentlink->len == 1 && currentlink->next->CharacterType == NUM)currentlink->CharacterType = HYPHEN;
					if (currentlink->previous->CharacterType == NUM && currentlink->next->CharacterType == SPACE)currentlink->CharacterType = ENDNUM;

	
				}

			}

			if (currentlink->next == NULL)endflag = 1;
			currentlink = currentlink->next;
			break;

		default:
			if (currentlink->next == NULL)endflag = 1;
			currentlink = currentlink->next;
			break;
		}

		if (endflag == 1)break;

	}

	currentlink = NULL;//###
	nood = NULL;//###
	return 0;
}

int GetOneCharNumDot(u16 ch, EnTable tab[], char* OneCharDot, int tablesize) {//对节点里的字符取对应的字典里取寻找对应的盲文
	for (int i = 0; i < tablesize; i++) {
		if (ch == tab[i].unicode) {
			strcat(OneCharDot, tab[i].Dot01);
			return 1;
		}
	}

	int alwastablesize = sizeof(always) / sizeof(always[0]);

	for (int i = 0; i < alwastablesize; i++) {
		if (ch == always[i].unicode) {
			strcat(OneCharDot, always[i].Dot01);
			return 1;
		}
	}


	return 0;
}

int GetOneCharNumDot_s(u16 ch[], int len, Tables tab[], char* OneCharDot, int tablesize) {
	for (int i = 0; i < tablesize; i++) {
		for (int j = 0; j < len; j++) {
			if (ch[j] != tab[i].unicode[j])break;
			if (tab[i].unicode[j + 1] == '0' && j == len - 1) {
				strcat(OneCharDot, tab[i].Dot01);
				return 1;
			}
		}
	}
	int alwastablesize = sizeof(always) / sizeof(always[0]);

	for (int i = 0; i < alwastablesize; i++) {
		
		if (ch[0]== always[i].unicode) {
			strcat(OneCharDot, always[i].Dot01);
			return 1;
		}
	}


	return 0;
}

int GetOneCharNumDot_ss(u16 ch[], int len, Tabless tab[], char* OneCharDot, int tablesize) {
	for (int i = 0; i < tablesize; i++) {
		for (int j = 0; j < len; j++) {
			if (ch[j] != tab[i].unicode[j])break;
			if (tab[i].unicode[j + 1] == '0' && j == len - 1) {
				strcat(OneCharDot, tab[i].Dot01);
				return 1;
			}
		}
	}
	return 0;
}
int TranslateLinkList(Linklist* head, char* NumDot) {//翻译每个节点得到结果
	Linklist* node=NULL;//###
	node = head;
	char OneNodeNumDot[DOTNUMMAX];

	//char letsign[4] = "56-";
	char letsign[7] = "000011";
	//char capsletter[3] = "6-";
	char capsletter[7] = "000001";
	//char begcapsword[5] = "6-6-";
	char begcapsword[13] = "000001000001";
	//char endcapsword[6] = "4-6-";
	char endcapsword[13] = "000100000001";
	//char numsign[6] = "3456-";
	char numsign[7] = "001111";
	//char decpoint[4] = "46-";
	char decpoint[7] = "000101";
	//char hyphen[4] = "36-";
	char hyphen[7] = "001001";
	//char space[3] = "0-";
	char space[7] = "000000";
	//char midword[3] = "3-";
	char midword[7] = "001000";
	int i = 0;
	int tablesize = 0;
	int endflag = 0;
	//while (node->next!=NULL) {
	while (endflag!=1) {
		for (i = 0; i < DOTNUMMAX; i++)OneNodeNumDot[i] = '\0';
		switch (node->CharacterType)
		{

		case(CAPITAL):
			tablesize = sizeof(capital) / sizeof(capital[0]);
			for (int i = 0; i < node->len; i++) {

				GetOneCharNumDot(node->OneTypeChar[i], capital, OneNodeNumDot, tablesize);
			}
			if (node->len == 1) {
				if ((node->next->CharacterType == SPACE || node->next == NULL) && (node->previous == NULL || node->previous->CharacterType == SPACE)) {

					strcat(NumDot, letsign);

				}

				strcat(NumDot, capsletter);
				strcat(NumDot, OneNodeNumDot);
			}
			else {
				strcat(NumDot, begcapsword);
				strcat(NumDot, OneNodeNumDot);
				strcat(NumDot, endcapsword);
			}
			if (node->next == NULL)endflag = 1;
			node = node->next;
			break;

		case(LOWER):
			tablesize = sizeof(lower) / sizeof(lower[0]);
			for (int i = 0; i < node->len; i++) {
				GetOneCharNumDot(node->OneTypeChar[i], lower, OneNodeNumDot, tablesize);
			}
			
			strcat(NumDot, OneNodeNumDot);
			if (node->next == NULL)endflag = 1;
			node = node->next;
			break;

		
		case(PREPUNC):
			tablesize = sizeof(Prepunc) / sizeof(Prepunc[0]);
			for (int i = 0; i < node->len; i++) {
				GetOneCharNumDot(node->OneTypeChar[i], Prepunc, OneNodeNumDot, tablesize);
			}
			//GetOneCharNumDot_s(node->OneTypeChar, node->len, Prepunc, OneNodeNumDot, tablesize);
			strcat(NumDot, OneNodeNumDot);
			if (node->next == NULL)endflag = 1;
			node = node->next;
			break;
		case(POSTPUNC):
			tablesize = sizeof(Postpunc) / sizeof(Postpunc[0]);
			for (int i = 0; i < node->len; i++) {
				GetOneCharNumDot(node->OneTypeChar[i], Postpunc, OneNodeNumDot, tablesize);
			}
			//GetOneCharNumDot_s(node->OneTypeChar, node->len, Postpunc, OneNodeNumDot, tablesize);
			strcat(NumDot, OneNodeNumDot);
			if (node->next == NULL)endflag = 1;
			node = node->next;
			break;
		
		case(CHPUNC):
			tablesize = sizeof(Chpunc) / sizeof(Chpunc[0]);
			for (int i = 0; i < node->len; i++) {
				GetOneCharNumDot(node->OneTypeChar[i], Chpunc, OneNodeNumDot, tablesize);
			}

			strcat(NumDot, OneNodeNumDot);
			if (node->next == NULL)endflag = 1;
			node = node->next;
			break;

		case(PUNC):
			tablesize = sizeof(always) / sizeof(always[0]);
			for (int i = 0; i < node->len; i++) {
				GetOneCharNumDot(node->OneTypeChar[i], always, OneNodeNumDot, tablesize);
			}
			strcat(NumDot, OneNodeNumDot);
			if (node->next == NULL)endflag = 1;
			node = node->next;
			break;
		case(BEGNUM):
			tablesize = sizeof(Begnum) / sizeof(Begnum[0]);
			for (int i = 0; i < node->len; i++) {
				GetOneCharNumDot(node->OneTypeChar[i], Begnum, OneNodeNumDot, tablesize);
			}
			strcat(NumDot, OneNodeNumDot);
			if (node->next == NULL)endflag = 1;
			node = node->next;
			break;
		
		case(MIDNUM):
			tablesize = sizeof(Midnum) / sizeof(Midnum[0]);
			for (int i = 0; i < node->len; i++) {
				GetOneCharNumDot(node->OneTypeChar[i], Midnum, OneNodeNumDot, tablesize);
			}
			strcat(NumDot, OneNodeNumDot);
			if (node->next == NULL)endflag = 1;
			node = node->next;
			break;
		
		case(DECPINT):

			strcat(OneNodeNumDot, decpoint);
			strcat(NumDot, OneNodeNumDot);
			if (node->next == NULL)endflag = 1;
			node = node->next;
			break;

		case(HYPHEN):

			strcat(OneNodeNumDot, hyphen);
			strcat(NumDot, OneNodeNumDot);
			if (node->next == NULL)endflag = 1;
			node = node->next;
			break;
		case(NUM):
			tablesize = sizeof(litdigit) / sizeof(litdigit[0]);
			if (node->previous == NULL ||
				(node->previous->CharacterType != MIDNUM && node->previous->CharacterType != DECPINT && node->previous->CharacterType != HYPHEN))
				strcat(OneNodeNumDot, numsign);
			for (int i = 0; i < node->len; i++) {
				GetOneCharNumDot(node->OneTypeChar[i], litdigit, OneNodeNumDot, tablesize);
			}
			strcat(NumDot, OneNodeNumDot);
			if (node->next == NULL)endflag = 1;
			node = node->next;
			break;
	

		default:
			printf("!!!!!!!%x this character can't translate\n", node->OneTypeChar[0]);
			strcat(OneNodeNumDot, space);
			strcat(NumDot, OneNodeNumDot);

			if (node->next == NULL)endflag = 1;
			node = node->next;
			break;

		}
		if (endflag == 1)break;
	}
	node = NULL;//###
	return 0;
}



MyEnum JudgmentType(unsigned short uni) {//判断一个字符是什么类型的，返回类型
	enum MyEnum chartype;

	if (uni >= 0x0030 && uni <= 0x0039) {
		chartype = NUM;
		return chartype;
	}
	else if (uni >= 0x0041 && uni <= 0x005a) {
		chartype = CAPITAL;
		return chartype;
	}
	else if (uni >= 0x0061 && uni <= 0x007a) {
		chartype = LOWER;
		return chartype;
	}
	else if ((uni >= 0x0021 && uni <= 0x002f) || (uni >= 0x003a && uni <= 0x0040) || (uni >= 0x005b && uni <= 0x0060) || (uni >= 0x007b && uni <= 0x007e)) {
		chartype = PUNC;
		return chartype;
	}
	else if ((uni >= 0x3000 && uni <= 0x303F)||(uni>= 0xFF00&&uni<=0xFFEF) || (uni >= 0x2000 && uni <= 0x206f)) {
		chartype = CHPUNC;
		return chartype;
	}
	else {
		chartype = SPACE;
		return chartype;
	}
}

int BulidLinkList(unsigned short* unibuf, int lenth, char* NumDot) {//建立双向链表的函数
	Linklist* head=NULL, * node=NULL, * end=NULL;//定义头节点普通节点和尾节点//###
	head = (Linklist*)malloc(sizeof(Linklist));
	end = head;
	enum MyEnum current, previous;//当前字母的类型，和前面一个字母的类型，用以判断是否塞到同一个节点中
	previous = EMPTY;
	current = EMPTY;
	int samtypecount = 0;//统计一节点中的Unicode存了几个了，应该存在哪了


	int i = 0;

	//int size = sizeof(CharacterLinkList);
	for (int i = 0; i <= lenth; i++) {
		current = JudgmentType(unibuf[i]);//获取当前字符的类型
		if (previous == EMPTY) {//如果是头节点
			head->OneTypeChar[samtypecount] = unibuf[i];
			head->CharacterType = current;
			head->previous = NULL;

			node = head;
			previous = current;
		}
		else {//不是头节点
			if (current == previous&&((unibuf[i]==unibuf[i-1])||current==CAPITAL||current==LOWER||current==NUM)) {//如果类型相同且都一样
				if (unibuf[i] == 0x2014||unibuf[i]== 0x2026) {

				}
				else {
					samtypecount++;

					node->OneTypeChar[samtypecount] = unibuf[i];

					previous = current;
					//继续添加
				}
			}
			else {//如果字符类型发生变换，则建立新的节点
				node->len = samtypecount + 1;//每个节点的长度这个值是指有几个字符，不是从0开始的下标
				samtypecount = 0;//空格也另外算的，不是和其他一起
				node = (Linklist*)malloc(sizeof(Linklist));
				node->OneTypeChar[samtypecount] = unibuf[i];
				node->CharacterType = current;

				previous = current;

				end->next = node;
				node->previous = end;
				end = node;
				//开一个新的节点
			}

		}

	}

	end->next = NULL;

	changetype(head);
	//for (i = 0; i < DOTNUMMAX; i++)NumDot[i] = '\0';
	TranslateLinkList(head, NumDot);


	Linklist* h;
	h = head;
	while (head != NULL) {//释放链表空间
		h = head;
		head = head->next;
		free(h);
	}
	head = NULL;//###
	node = NULL;//###
	end = NULL;//###
	h = NULL;//###

	return 0;

}




int EnglisfGrade1(u16 UnicodeInput[], char* PointOut) {

	u16 OneWord[ONEWORDMAX] = { 0x000 };
	char NumDot[DOTNUMMAX] = {'\0'};//###
	int i = 0, j = 0;

	
	//for (i = 0; i < DOTNUMMAX; i++)NumDot[i] = '\0';
	for (i = 0; i < UNICODESIZE; i++) {
		if (UnicodeInput[i] != 0x0020 && UnicodeInput[i] != 0x0000) {
			OneWord[j++] = UnicodeInput[i];

		}
		else {
			OneWord[j] = 0x0020;

			BulidLinkList(OneWord, j, NumDot);

			for (j = 0; j < ONEWORDMAX; j++) {
				OneWord[j] = 0x0000;

			}
			j = 0;

			if (UnicodeInput[i] == 0x0000)break;
		}


	}
	strcat(PointOut, NumDot);
	return 0;
}



int isChCharacter(u16 a) {
	return (((a >= 0x4E00 && a <= 0x9FFF) || (a >= 0x3400 && a <= 0x4DBF) || (a >= 0xF900 && a <= 0xFAFF)) ? 1 : -1);
}
typedef struct TableInformation {
	char *tablepath=(char*)malloc(sizeof(char)*50);//使用的字典路径###
	int WORD_ITEM_LEN123;	//这个字典一个字的词条存放的字节数,下面是4-5，7-9的字节数
	int WORD_ITEM_LEN456;
	int WORD_ITEM_LEN789;
	int WORD_ITEM_MAXCNT;	//这个字典词条最大的汉字个数
	int ONE_CHN;  //一个字的词条个数
	int TWO_CHN;
	int THREE_CHN;
	int FOUR_CHN;
	int FIVE_CHN;
	int SIX_CHN;
	int SEVEN_CHN;
	int EIGHT_CHN;
	int NINE_CHN;

	int ONE_CHN_START;     //文件中一个字词条的起始位置
	int ONE_CHN_END;

	int TWO_CHN_START;
	int TWO_CHN_END;

	int THREE_CHN_START;
	int THREE_CHN_END;

	int FOUR_CHN_START;
	int FOUR_CHN_END;

	int FIVE_CHN_START;
	int FIVE_CHN_END;

	int SIX_CHN_START;
	int SIX_CHN_END;

	int SEVEN_CHN_START;
	int SEVEN_CHN_END;

	int EIGHT_CHN_START;
	int EIGHT_CHN_END;

	int NINE_CHN_START;
	int NINE_CHN_END;
}TableInformation;
TableInformation Table;

int Dichotomy(const u16 Temp[],int leftset,int rightset,int lenth, FILE* ChnTableFp) {
	u16  CiTiao[9] = {0x00};
	int onelenth = 0;
	bool IsBeEqual = false;
	int mid;
	int left = 0;
	if (lenth >= 1 && lenth <= 3)onelenth = 64;
	else if (lenth >= 4 && lenth <= 6)onelenth = 128;
	else if (lenth >= 7 && lenth <= 9)onelenth = 256;
	else return -1;
	//fseek(ChnTableFp, 1391298, SEEK_SET);
	//fread(CiTiao, 1, 2 * lenth, ChnTableFp);



	int right = (rightset-leftset) / onelenth;
	while (left <=right) {
		mid = (left + right) / 2;
		
		fseek(ChnTableFp, leftset+mid*onelenth, SEEK_SET);
		//int loca=ftell(ChnTableFp);
		//for (int set = 0; set < 9; set++)CiTiao[set] = 0x00;
		fread(CiTiao, 1, 2* lenth, ChnTableFp);
		for (int i = 0; i < lenth; i++) {
			if (Temp[i] == CiTiao[i]) {
				IsBeEqual = true;
			}
			else {
				IsBeEqual = false;
				if (Temp[i] > CiTiao[i])left = mid+1;
				if (Temp[i] < CiTiao[i]) right = mid-1;
				break;
			}
		}
		if (IsBeEqual) {
			//break;
			return leftset + mid * onelenth;
		}

	}
	
	return -1;
}
bool FindInDict(const u16 Temp[], char *PointOut, int len, FILE* ChnTableFp) {
	int left = 0;
	int right = 0;
	int idfind = -1;
	char PointTemp[256] = {'\0'};
	switch (len)
	{

	case 1:
		left = Table.ONE_CHN_START;//设置二分法的左右
		right = Table.ONE_CHN_END;
		idfind = Dichotomy(Temp, left, right, 1, ChnTableFp);//调用二分法，返回值是这词条的在文件中的位置
		if (idfind != -1) {
			fseek(ChnTableFp, idfind+2, SEEK_SET);//移动相应Unicode的字节数
			fread(PointTemp, 1, Table.WORD_ITEM_LEN123, ChnTableFp);//获取01点序
			strcat(PointOut, PointTemp);//复制到点序输出结果数组中
		}
		break;
	case 2:
		left = Table.TWO_CHN_START;
		right = Table.TWO_CHN_END;
		idfind = Dichotomy(Temp, left, right, 2, ChnTableFp);
		if (idfind != -1) {
			fseek(ChnTableFp, idfind + 4, SEEK_SET);
			fread(PointTemp, 1, Table.WORD_ITEM_LEN123, ChnTableFp);
			strcat(PointOut, PointTemp);
		}
		break;
	case 3:
		left = Table.THREE_CHN_START;
		right = Table.THREE_CHN_END;
		idfind = Dichotomy(Temp, left, right, 3, ChnTableFp);
		if (idfind != -1) {
			fseek(ChnTableFp, idfind + 6, SEEK_SET);
			fread(PointTemp, 1, Table.WORD_ITEM_LEN123, ChnTableFp);
			strcat(PointOut, PointTemp);
		}
		break;

	case 4:
		left = Table.FOUR_CHN_START;
		right = Table.FOUR_CHN_END;
		idfind=Dichotomy(Temp, left, right, 4, ChnTableFp);
		if (idfind != -1) {
			fseek(ChnTableFp, idfind + 8, SEEK_SET);
			fread(PointTemp, 1, Table.WORD_ITEM_LEN456, ChnTableFp);
			strcat(PointOut, PointTemp);
		}
		break;
	case 5:
		left = Table.FIVE_CHN_START;
		right = Table.FIVE_CHN_END;
		idfind=Dichotomy(Temp, left, right, 5, ChnTableFp);
		if (idfind != -1) {
			fseek(ChnTableFp, idfind + 10, SEEK_SET);
			fread(PointTemp, 1, Table.WORD_ITEM_LEN456, ChnTableFp);
			strcat(PointOut, PointTemp);
		}
		break;
	case 6:
		left = Table.SIX_CHN_START;
		right = Table.SIX_CHN_END;
		idfind=Dichotomy(Temp, left, right, 6, ChnTableFp);
		if (idfind != -1) {
			fseek(ChnTableFp, idfind + 12, SEEK_SET);
			fread(PointTemp, 1, Table.WORD_ITEM_LEN456, ChnTableFp);
			strcat(PointOut, PointTemp);
		}
		break;
	case 7:
		left = Table.SEVEN_CHN_START;
		right = Table.SEVEN_CHN_END;
		idfind=Dichotomy(Temp, left, right, 7, ChnTableFp);
		if (idfind != -1) {
			fseek(ChnTableFp, idfind + 14, SEEK_SET);
			fread(PointTemp, 1, Table.WORD_ITEM_LEN789, ChnTableFp);
			strcat(PointOut, PointTemp);
		}
		break;
	case 8:
		left = Table.EIGHT_CHN_START;
		right = Table.EIGHT_CHN_END;
		idfind=Dichotomy(Temp, left, right, 8, ChnTableFp);
		if (idfind != -1) {
			fseek(ChnTableFp, idfind + 16, SEEK_SET);
			fread(PointTemp, 1, Table.WORD_ITEM_LEN789, ChnTableFp);
			strcat(PointOut, PointTemp);
		}
		break;
	case 9:
		left = Table.NINE_CHN_START;
		right = Table.NINE_CHN_END;
		idfind=Dichotomy(Temp, left, right, 9, ChnTableFp);
		if (idfind != -1) {
			fseek(ChnTableFp, idfind + 18, SEEK_SET);
			fread(PointTemp, 1, Table.WORD_ITEM_LEN789, ChnTableFp);
			strcat(PointOut, PointTemp);
		}
		break;
	default:
		break;
	}
	if (idfind !=-1)return true;
	else return false;
}

int TableLook(const u16 Temp[], char *PointOut,int len, FILE* ChnTableFp) {
	bool IsFind = false;
	int TempBegein = 0;
	int TempEnd = len;
	while (len >= 1) {//9，8，7，6，5，4，3，2，1，依次查找，查找到了匹配上了 就返回这个长度
		IsFind=FindInDict(Temp, PointOut,len, ChnTableFp);
		if (IsFind) {
			return len;
		}
		else
			len--;
			
	}
	strcat(PointOut, "000000");
	return 1;
}
int CopyUnicode(const u16 Object[],u16 Result[],int len) {//拷贝指定个数的Unicode
	if (Object != NULL) {
		for (int i = 0; i < len; i++) {
			*Result = *Object;
			Result++;
			Object++;
		}
	}
	else
		printf("copy objiect is null");
		return 0;
	return 0;
}
int HanZiTranslate(u16 UnicodeInput[], char *PointOut,int cout) {
	int len=0;//记录长度
	u16 Temp[9] = {0x00};
	int OneceLook = 0;
	u16 InPutUnicode[UNICODESIZE] = { 0x00 };
	u16 *point;

	len = cout;
	point = UnicodeInput;
	FILE* ChnTableFp = NULL;
	char* tablename = (char*)malloc(sizeof(char) * 50);//###
	if (tablename == NULL) {

		printf("allocate error\n");
		return -2;
	}

	strcpy(tablename, Table.tablepath);
	ChnTableFp = fopen(tablename, "rb");//打开中文表
	if (ChnTableFp == (FILE*)NULL) {
		printf("open table file error\n");
		return -2;
	}

	while(*point != 0x00) {
		for (int i = 0; i < 9; i++) { Temp[i] = 0x00; }//清空临时数组
		if (len >= Table.WORD_ITEM_MAXCNT) {//获取段，通用盲文9个9个取，现行2个两个取
			CopyUnicode(point, Temp, Table.WORD_ITEM_MAXCNT);//复制到临时数组中
			
			OneceLook=TableLook(Temp, PointOut, Table.WORD_ITEM_MAXCNT, ChnTableFp);//返回每次找到的个数
			point = point + OneceLook;//移动数组指针
			len = len - OneceLook;//未翻译的长度减去相应的值
		}
		else {
			CopyUnicode(point, Temp, len);//剩下多少就全部复制进去
			OneceLook = TableLook(Temp, PointOut, len, ChnTableFp);
			point = point + OneceLook;
			len = len - OneceLook;
		}
	}
	fclose(ChnTableFp);
	free(tablename);//###
	tablename = NULL;//###
	return 0;

}
void SetTableInformation(int mode) {
	switch (mode)
	{
	case(1):
		strcpy(Table.tablepath, ".\\Debug\\TongYongFlashTable.txt");
		Table.WORD_ITEM_LEN123 = 64;
		Table.WORD_ITEM_LEN456 = 128;
		Table.WORD_ITEM_LEN789 = 256;
		Table.WORD_ITEM_MAXCNT = 9;

		Table.ONE_CHN = 20902;
		Table.TWO_CHN = 29516;
		Table.THREE_CHN = 880;
		Table.FOUR_CHN = 1184;
		Table.FIVE_CHN = 49;
		Table.SIX_CHN = 36;
		Table.SEVEN_CHN = 20;
		Table.EIGHT_CHN = 11;
		Table.NINE_CHN = 11;

		Table.ONE_CHN_START = 0;
		Table.ONE_CHN_END = Table.ONE_CHN_START + Table.ONE_CHN * Table.WORD_ITEM_LEN123 - Table.WORD_ITEM_LEN123;

		Table.TWO_CHN_START = Table.ONE_CHN_END + Table.WORD_ITEM_LEN123;
		Table.TWO_CHN_END = Table.TWO_CHN_START + Table.TWO_CHN * Table.WORD_ITEM_LEN123 - Table.WORD_ITEM_LEN123;

		Table.THREE_CHN_START = Table.TWO_CHN_END + Table.WORD_ITEM_LEN123;
		Table.THREE_CHN_END = Table.THREE_CHN_START + Table.THREE_CHN * Table.WORD_ITEM_LEN123 - Table.WORD_ITEM_LEN123;

		Table.FOUR_CHN_START = Table.THREE_CHN_END + Table.WORD_ITEM_LEN123;
		Table.FOUR_CHN_END = Table.FOUR_CHN_START + Table.FOUR_CHN * Table.WORD_ITEM_LEN456 - Table.WORD_ITEM_LEN456;

		Table.FIVE_CHN_START = Table.FOUR_CHN_START + Table.WORD_ITEM_LEN456;
		Table.FIVE_CHN_END = Table.FIVE_CHN_START + Table.FIVE_CHN * Table.WORD_ITEM_LEN456 - Table.WORD_ITEM_LEN456;

		Table.SIX_CHN_START = Table.FIVE_CHN_END + Table.WORD_ITEM_LEN456;
		Table.SIX_CHN_END = Table.SIX_CHN_START + Table.SIX_CHN * Table.WORD_ITEM_LEN456 - Table.WORD_ITEM_LEN456;

		Table.SEVEN_CHN_START = Table.SIX_CHN_END + Table.WORD_ITEM_LEN456;
		Table.SEVEN_CHN_END = Table.SEVEN_CHN_START + Table.SEVEN_CHN * Table.WORD_ITEM_LEN789 - Table.WORD_ITEM_LEN789;

		Table.EIGHT_CHN_START = Table.SEVEN_CHN_END + Table.WORD_ITEM_LEN789;
		Table.EIGHT_CHN_END = Table.EIGHT_CHN_START + Table.EIGHT_CHN * Table.WORD_ITEM_LEN789 - Table.WORD_ITEM_LEN789;

		Table.NINE_CHN_START = Table.EIGHT_CHN_END + Table.WORD_ITEM_LEN789;
		Table.NINE_CHN_END = Table.NINE_CHN_START + Table.NINE_CHN * Table.WORD_ITEM_LEN789 - Table.WORD_ITEM_LEN789;
		break;
	
	case(2):
		strcpy(Table.tablepath, ".\\Debug\\XianXingFlashTable.txt");
		Table.WORD_ITEM_LEN123 = 64;
		Table.WORD_ITEM_LEN456 = 128;
		Table.WORD_ITEM_LEN789 = 256;
		Table.WORD_ITEM_MAXCNT = 2;

		Table.ONE_CHN = 20994;
		Table.TWO_CHN = 23807;
		Table.THREE_CHN = 0;
		Table.FOUR_CHN = 0;
		Table.FIVE_CHN = 0;
		Table.SIX_CHN = 0;
		Table.SEVEN_CHN = 0;
		Table.EIGHT_CHN = 0;
		Table.NINE_CHN = 0;

		Table.ONE_CHN_START = 0;
		Table.ONE_CHN_END = Table.ONE_CHN_START + Table.ONE_CHN * Table.WORD_ITEM_LEN123 - Table.WORD_ITEM_LEN123;

		Table.TWO_CHN_START = Table.ONE_CHN_END + Table.WORD_ITEM_LEN123;
		Table.TWO_CHN_END = Table.TWO_CHN_START + Table.TWO_CHN * Table.WORD_ITEM_LEN123 - Table.WORD_ITEM_LEN123;

		Table.THREE_CHN_START = Table.TWO_CHN_END + Table.WORD_ITEM_LEN123;
		Table.THREE_CHN_END = Table.THREE_CHN_START + Table.THREE_CHN * Table.WORD_ITEM_LEN123 - Table.WORD_ITEM_LEN123;

		Table.FOUR_CHN_START = Table.THREE_CHN_END + Table.WORD_ITEM_LEN123;
		Table.FOUR_CHN_END = Table.FOUR_CHN_START + Table.FOUR_CHN * Table.WORD_ITEM_LEN456 - Table.WORD_ITEM_LEN456;

		Table.FIVE_CHN_START = Table.FOUR_CHN_START + Table.WORD_ITEM_LEN456;
		Table.FIVE_CHN_END = Table.FIVE_CHN_START + Table.FIVE_CHN * Table.WORD_ITEM_LEN456 - Table.WORD_ITEM_LEN456;

		Table.SIX_CHN_START = Table.FIVE_CHN_END + Table.WORD_ITEM_LEN456;
		Table.SIX_CHN_END = Table.SIX_CHN_START + Table.SIX_CHN * Table.WORD_ITEM_LEN456 - Table.WORD_ITEM_LEN456;

		Table.SEVEN_CHN_START = Table.SIX_CHN_END + Table.WORD_ITEM_LEN456;
		Table.SEVEN_CHN_END = Table.SEVEN_CHN_START + Table.SEVEN_CHN * Table.WORD_ITEM_LEN789 - Table.WORD_ITEM_LEN789;

		Table.EIGHT_CHN_START = Table.SEVEN_CHN_END + Table.WORD_ITEM_LEN789;
		Table.EIGHT_CHN_END = Table.EIGHT_CHN_START + Table.EIGHT_CHN * Table.WORD_ITEM_LEN789 - Table.WORD_ITEM_LEN789;

		Table.NINE_CHN_START = Table.EIGHT_CHN_END + Table.WORD_ITEM_LEN789;
		Table.NINE_CHN_END = Table.NINE_CHN_START + Table.NINE_CHN * Table.WORD_ITEM_LEN789 - Table.WORD_ITEM_LEN789;
		break;
	case(3):
		strcpy(Table.tablepath, ".\\Debug\\QuanDaiDiaoFlashTable.txt");
		Table.WORD_ITEM_LEN123 = 64;
		Table.WORD_ITEM_LEN456 = 128;
		Table.WORD_ITEM_LEN789 = 256;
		Table.WORD_ITEM_MAXCNT = 3;

		Table.ONE_CHN = 20902;
		Table.TWO_CHN = 5051;
		Table.THREE_CHN = 18;
		Table.FOUR_CHN = 0;
		Table.FIVE_CHN = 0;
		Table.SIX_CHN = 0;
		Table.SEVEN_CHN = 0;
		Table.EIGHT_CHN = 0;
		Table.NINE_CHN = 0;

		Table.ONE_CHN_START = 0;
		Table.ONE_CHN_END = Table.ONE_CHN_START + Table.ONE_CHN * Table.WORD_ITEM_LEN123 - Table.WORD_ITEM_LEN123;

		Table.TWO_CHN_START = Table.ONE_CHN_END + Table.WORD_ITEM_LEN123;
		Table.TWO_CHN_END = Table.TWO_CHN_START + Table.TWO_CHN * Table.WORD_ITEM_LEN123 - Table.WORD_ITEM_LEN123;

		Table.THREE_CHN_START = Table.TWO_CHN_END + Table.WORD_ITEM_LEN123;
		Table.THREE_CHN_END = Table.THREE_CHN_START + Table.THREE_CHN * Table.WORD_ITEM_LEN123 - Table.WORD_ITEM_LEN123;

		Table.FOUR_CHN_START = Table.THREE_CHN_END + Table.WORD_ITEM_LEN123;
		Table.FOUR_CHN_END = Table.FOUR_CHN_START + Table.FOUR_CHN * Table.WORD_ITEM_LEN456 - Table.WORD_ITEM_LEN456;

		Table.FIVE_CHN_START = Table.FOUR_CHN_START + Table.WORD_ITEM_LEN456;
		Table.FIVE_CHN_END = Table.FIVE_CHN_START + Table.FIVE_CHN * Table.WORD_ITEM_LEN456 - Table.WORD_ITEM_LEN456;

		Table.SIX_CHN_START = Table.FIVE_CHN_END + Table.WORD_ITEM_LEN456;
		Table.SIX_CHN_END = Table.SIX_CHN_START + Table.SIX_CHN * Table.WORD_ITEM_LEN456 - Table.WORD_ITEM_LEN456;

		Table.SEVEN_CHN_START = Table.SIX_CHN_END + Table.WORD_ITEM_LEN456;
		Table.SEVEN_CHN_END = Table.SEVEN_CHN_START + Table.SEVEN_CHN * Table.WORD_ITEM_LEN789 - Table.WORD_ITEM_LEN789;

		Table.EIGHT_CHN_START = Table.SEVEN_CHN_END + Table.WORD_ITEM_LEN789;
		Table.EIGHT_CHN_END = Table.EIGHT_CHN_START + Table.EIGHT_CHN * Table.WORD_ITEM_LEN789 - Table.WORD_ITEM_LEN789;

		Table.NINE_CHN_START = Table.EIGHT_CHN_END + Table.WORD_ITEM_LEN789;
		Table.NINE_CHN_END = Table.NINE_CHN_START + Table.NINE_CHN * Table.WORD_ITEM_LEN789 - Table.WORD_ITEM_LEN789;
		break;
	case(4):
		strcpy(Table.tablepath, ".\\Debug\\ShuangPinFlashTable.txt");
		Table.WORD_ITEM_LEN123 = 64;
		Table.WORD_ITEM_LEN456 = 128;
		Table.WORD_ITEM_LEN789 = 256;
		Table.WORD_ITEM_MAXCNT = 3;

		Table.ONE_CHN = 20902;
		Table.TWO_CHN = 5051;
		Table.THREE_CHN = 18;
		Table.FOUR_CHN = 0;
		Table.FIVE_CHN = 0;
		Table.SIX_CHN = 0;
		Table.SEVEN_CHN = 0;
		Table.EIGHT_CHN = 0;
		Table.NINE_CHN = 0;

		Table.ONE_CHN_START = 0;
		Table.ONE_CHN_END = Table.ONE_CHN_START + Table.ONE_CHN * Table.WORD_ITEM_LEN123 - Table.WORD_ITEM_LEN123;

		Table.TWO_CHN_START = Table.ONE_CHN_END + Table.WORD_ITEM_LEN123;
		Table.TWO_CHN_END = Table.TWO_CHN_START + Table.TWO_CHN * Table.WORD_ITEM_LEN123 - Table.WORD_ITEM_LEN123;

		Table.THREE_CHN_START = Table.TWO_CHN_END + Table.WORD_ITEM_LEN123;
		Table.THREE_CHN_END = Table.THREE_CHN_START + Table.THREE_CHN * Table.WORD_ITEM_LEN123 - Table.WORD_ITEM_LEN123;

		Table.FOUR_CHN_START = Table.THREE_CHN_END + Table.WORD_ITEM_LEN123;
		Table.FOUR_CHN_END = Table.FOUR_CHN_START + Table.FOUR_CHN * Table.WORD_ITEM_LEN456 - Table.WORD_ITEM_LEN456;

		Table.FIVE_CHN_START = Table.FOUR_CHN_START + Table.WORD_ITEM_LEN456;
		Table.FIVE_CHN_END = Table.FIVE_CHN_START + Table.FIVE_CHN * Table.WORD_ITEM_LEN456 - Table.WORD_ITEM_LEN456;

		Table.SIX_CHN_START = Table.FIVE_CHN_END + Table.WORD_ITEM_LEN456;
		Table.SIX_CHN_END = Table.SIX_CHN_START + Table.SIX_CHN * Table.WORD_ITEM_LEN456 - Table.WORD_ITEM_LEN456;

		Table.SEVEN_CHN_START = Table.SIX_CHN_END + Table.WORD_ITEM_LEN456;
		Table.SEVEN_CHN_END = Table.SEVEN_CHN_START + Table.SEVEN_CHN * Table.WORD_ITEM_LEN789 - Table.WORD_ITEM_LEN789;

		Table.EIGHT_CHN_START = Table.SEVEN_CHN_END + Table.WORD_ITEM_LEN789;
		Table.EIGHT_CHN_END = Table.EIGHT_CHN_START + Table.EIGHT_CHN * Table.WORD_ITEM_LEN789 - Table.WORD_ITEM_LEN789;

		Table.NINE_CHN_START = Table.EIGHT_CHN_END + Table.WORD_ITEM_LEN789;
		Table.NINE_CHN_END = Table.NINE_CHN_START + Table.NINE_CHN * Table.WORD_ITEM_LEN789 - Table.WORD_ITEM_LEN789;
		break;
	default:
		printf("choos table mode error!");
		break;
	}
}


int TranslateBaseOnTable(u8 InPut[], int InPutlen,int mode, u16 DevideUnicodeOutput[], int* Unicodelen, char PointOut[], int* Dotlen) {
	int i = 0;
	int j = 0;
	int fencinum=0;
	int cout = 0;
	int changeflag = 0;
	int isch = 0;
	int currentlanguage = 0;

	u16 *UnicodeInput = (u16*)malloc(sizeof(u16) * InPutlen);
	u16 *UnicodeTemp =(u16*)malloc(sizeof(u16)*InPutlen);
	u16 *DevideUicodeTemp =(u16*)malloc(sizeof(u16)*InPutlen*2);

	memset(UnicodeInput, 0x00, sizeof(u16) * InPutlen);
	memset(UnicodeTemp, 0x00, sizeof(u16) * InPutlen);
	memset(DevideUicodeTemp, 0x00, sizeof(u16) * InPutlen*2);
	
	//u16 DevideUicodeTemp[UNICODESIZE * 2];
	//u16 UnicodeInput[UNICODESIZE];
	
	/*
	for (i = 0; i < sizeof(u16) * InPutlen; i++) {

		UnicodeInput[i] = 0x00; 
		UnicodeTemp[i] = 0x00;
	}
	for (i = 0; i < sizeof(u16) * InPutlen *2; i++) {

		DevideUicodeTemp[i] = 0x00;
	}

	*/

	//StringToUni(InPut,UnicodeInput, strlen((const char*)InPut));//转换为Unicode
	StringToUni(InPut,UnicodeInput, InPutlen);//转换为Unicode

	for (int c = 0; c < 10; c++)printf("UnicodeInput[%d]=%x\n", c, UnicodeInput[c]);
	SetTableInformation(mode);

	DevideString(DevideUnicodeOutput, UnicodeInput, InPutlen);
	for (i = 0; i< InPutlen*2; i++) { printf("devide out:DevideUnicodeOutput[%d]=%x\n", i, DevideUnicodeOutput[i]); }

	for (i = 0; DevideUnicodeOutput[i] != 0x00&&i<UNICODESIZE*2; i++) {//###
		isch = isChCharacter(DevideUnicodeOutput[i]);
		if (currentlanguage == 0) { 
			changeflag = 0; 
		}
		else {
			if (currentlanguage == isch)changeflag = 0;
			else changeflag = -1;
			
		}
		
		if (changeflag == 0) {
			UnicodeTemp[cout] = DevideUnicodeOutput[i];
			cout++;
		}
		else {
			if (currentlanguage==1) {
				
				HanZiTranslate(UnicodeTemp, PointOut,cout);
				
				cout = 0;
				
			}
			else {
				
				EnglisfGrade1(UnicodeTemp, PointOut);
				
				cout = 0;
				
			}
			for (j = 0; j < InPutlen; j++) {UnicodeTemp[j] = 0x00;}
			i--;
		}
		currentlanguage = isch;
		
	}
	
	if (currentlanguage == 1) {
		
		for (int c = 0; c < 10; c++)printf("UnicodeTemp[%d]=%x\n", c,UnicodeTemp[c]);

		for (int c = 0; c < 20; c++)printf("DevideUicodeTemp[%d]=%x\n", c, DevideUicodeTemp[c]);
		

		HanZiTranslate(UnicodeTemp, PointOut,cout);
		
		
	}
	else {
		
		EnglisfGrade1(UnicodeTemp, PointOut);
	}

	//EnglisfGrade1(UnicodeInput, PointOut);
	//SetTableInformation(1);
	//HanZiTranslate(UnicodeInput,PointOut);//调用汉语翻译，初步设想分为中文英文，中文包括全角标点，英文包括数字和ASCII码里的标点

	for (int i = 0; i < sizeof(u16) * InPutlen; i++) {
		if (DevideUnicodeOutput[i] == 0x00) {
			*Unicodelen = i;
			break;
		}
		else {
			*Unicodelen = i+1;
		}
		
	}

	for (int i = 0; i < POINTSIZE; i++) {
		if (PointOut[i] == '\0') {
			*Dotlen = i;
			break;
		}
		else {
			*Dotlen = i+1;
		}

	}

	free(UnicodeInput);
	free(UnicodeTemp);
	free(DevideUicodeTemp);
	UnicodeInput = NULL;
	UnicodeTemp = NULL;
	DevideUicodeTemp = NULL;
	return 0;
}