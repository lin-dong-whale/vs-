#include"USGrade1Trans.h"
#include<malloc.h>

#define CHARMAX 100//一段待翻译英文的最大长度
#define SAMETYPE 10//同种类型字符的最大长度
#define ONEWORDMAX 10//由空格切分的一个词 的最大长度
#define DOTNUMMAX 500

enum MyEnum
{
	PREPUNC,
	POSTPUNC,
	ALWAYS,
	ALWAYS_S,
	WORD,
	MIDWORD,
	ENDWORD,
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
	char unicode;
	char numdot[15];
}Table;

typedef struct TranslateTables {
	char unicode[4];
	char numdot[25];
}Tables;

typedef struct TranslateTabless {
	char unicode[7];
	char numdot[20];
}Tabless;


Tables Prepunc[]{
 {'"','0','0','0',"236-"},
 {'\'','0','0','0',"6-236-"},
{'(','0','0','0',"2356-"},
{'`','`','0','0',"236-"},
{'`','0','0','0',"6-236-"},

{'’','0','0','0',"356-3-"},

/*
{'\'',"6-236-"},
{'[',"6-2356-"},
{'{',"56-2356-"},
*/
};
Tables Postpunc[]{


{'"','0','0','0',"356-"},


{'\'','\'','\'','0',"356-3-356-"},
{'\'','\'','0','0',"356-"},
{'\'','0','0','0',"356-3-"},
{')','0','0','0',"2356-"},
{'`','0','0','0',"6-236-"},
{'’','0','0','0',"356-3-"},

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


Tabless alwayss[]{
	{' ','-','"','0','0','0','0',"36-36-356-"},
{' ','-','”','0','0','0','0',"36-36-356-"},
{'.','.','.','"','0','0','0',"3-3-3-356-"},
{'…','"','0','0','0','0','0',"3-3-3-356-"},
{'.','.','.','”','0','0','0',"3-3-3-356-"},
{'…','”','0','0','0','0','0',"3-3-3-356-"},
{'?','"','0','0','0','0','0',"236-356-"},
{'/','/','0','0','0','0','0',"345-"},
{'-','c','o','m','0','0','0',"36-14-135-134-"},
{'\\','\\','0','0','0','0','0',"5-16-"},
{' ','-',' ','0','0','0','0',"36-36-"},
{' ','-',' ','c','o','m','0',"36-36-14-135-134-"},
{'.','.','.','0','0','0','0',"3-3-3-"},
{'.',' ','.',' ','.','0','0',"3-3-3-"},
{' ','–',' ','0','0','0','0',"36-36-"},
{' ','−',' ','0','0','0','0',"36-36-"},
/*
{'.','.','.','0','0','0','0',"3-3-3-356-3-"},
{'.',' ','.',' ','.','"','0',"36-36-"},


{'.','.','.','.','.','0','0',"0-"},
	{'_','_','_','_','0','0','0',"456-"},
	{'-','-','-','-','0','0','0',"36-"},
	*/
};

Table always[]{
	{'#',"4-3456-"},
	{'/',"456-34-"},
	{'^',"456-126-"},
	{'~',"4-156-"},
{'&',"4-12346-"},
{'[',"6-2356-"},
{']',"2356-3-"},
{'{',"46-2356-"},
{'}',"46-2356-"},
{'%',"25-1234-"},
{'*',"35-35-"},
{'‘',"6-236-"},
{'|',"5-123-"},
{'£',"4-123-"},
{0x2013,"56-36-"},

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
};



Table Word[]{
	{'"',"236-"},
	/*
{'(',"4-2356-"},
{')',"4-2356-"},

{'\'',"4-3-"},
{';',"4-23-"},
{']',"4-2356-3-"},
{',',"4-2-"},
{'.',"4-256-"},
{'?',"4-236-"},
{'[',"4-6-2356-"},
{'{',"4-56-2356-"},
{'}',"4-2356-23-"},
*/
};

Tabless words[]{

	//{'','','','','','','',""},
	{'\'','a','v','e','0','0','0',"3-1-1236-15-"},
	{'’','a','v','e','0','0','0',"3-1-1236-15-"},
	{'c','\'','m','o','n','0','0',"14-3-134-135-1345-"},
	{'c','’','m','o','n','0','0',"14-3-134-135-1345-"},
	{'\'','e','m','0','0','0','0',"3-15-134-"},
{'’','e','m','0','0','0','0',"3-15-134"},
{'\'','e','a','r','0','0','0',"3-15-1-1235"},

{'’','e','a','r','0','0','0',"3-15-1-1235"},

{'g','o','i','n','\'','0','0',"1245-135-24-1345-3-"},

{'g','o','i','n','\'','0','0',"1245-135-24-1345-3-"},
{'\'','o','m','e','0','0','0',"3-135-134-15"},
{'’','o','m','e','0','0','0',"3-135-134-15"},

{'\'','u','n','s','0','0','0',"3-136-1345-234"},
{'’','u','n','s','0','0','0',"3-136-1345-234"},
};


Tabless midendword[]{
	{'\'','a','n','0','0','0','0',"3-1-1345-"},
{'’','a','n','0','0','0','0',"3-1-1345-"},
{'\'','a','m','0','0','0','0',"3-1-134-"},
{'’','a','m','0','0','0','0',"3-1-134-"},
{'e','\'','e','0','0','0','0',"15-3-15-"},
{'e','’','e','0','0','0','0',"15-3-15-"},

};

Table nobackalways[]{
	{'\'',"3-"},
{',',"2-"},
{'.',"256-"},
{';',"23-"},
{':',"25-"},
{'!',"235-"},
{'?',"236-"},
{'?',"236-"},
{'>',"135-"},
{'`',"4-"},
{'(',"2356-"},
{'@',"2346-"},
{'<',"246-"},
{0x2212,"36-"},

{0x201C,"236-"},
{0x201D,"356-"},
{0x201E,"236-"},
{0x201F,"356-"},
};

Tabless endword[]{
	{'\'','a','h','0','0','0','0',"3-1-125-"},
{'’','a','h','0','0','0','0',"3-1-125-"},
{'\'','d','0','0','0','0','0',"3-145-"},
{'’','d','0','0','0','0','0',"3-145-"},
{'\'','l','l','0','0','0','0',"3-123-123-"},
{'’','l','l','0','0','0','0',"3-123-123-"},
{'\'','m','0','0','0','0','0',"3-134-"},
{'’','m','0','0','0','0','0',"3-134-"},
{'\'','n','0','0','0','0','0',"3-1345-"},
{'’','n','0','0','0','0','0',"3-1345-"},
{'\'','r','e','0','0','0','0',"3-1235-15-"},
{'’','r','e','0','0','0','0',"3-1235-15-"},
{'\'','r','y','0','0','0','0',"3-1235-13456-"},
{'’','r','y','0','0','0','0',"3-1235-13456-"},
{'\'','r','0','0','0','0','0',"3-1235-"},
{'’','r','0','0','0','0','0',"3-1235-"},
{'\'','s','0','0','0','0','0',"3-234-"},
{'’','s','0','0','0','0','0',"3-234-"},
{'\'','v','e','0','0','0','0',"3-1236-15-"},
{'’','v','e','0','0','0','0',"3-1236-15-"},
{'\'','t','0','0','0','0','0',"3-2345-"},
{'’','t','0','0','0','0','0',"3-2345-"},
{')','0','0','0','0','0','0',"2356-"},
{'-','t','o','0','0','0','0',"36-2345-135-"},
{'-','b','y','0','0','0','0',"36-12-13456-"},

};

Tables begwords[]{
	{'d','\'','0','0',"145-3-"},
{'d','’','0','0',"145-3-"},
{'h','a','\'','p',"125-1-3-1234-"},
{'h','a','’','p',"125-1-3-1234-"},
{'o','\'','d','0',"135-3-145-"},
{'o','’','d','0',"135-3-145-"},
{'o','\'','l','0',"135-3-123-"},
{'o','’','l','0',"135-3-123-"},


};

Table begword[]{
	{'(',"2356-"},
{'@',"4-2346-"},
{'-',"36-"},
};

Table joinword[]{
{'=',"56-2356-"},
{'×',"56-236-"},
{'+',"56-235-"},
{'÷',"56-256-"},
{'-',"36-"},


};

Table Midnum[]{
	{',',"3-"},
	{'.',"2"},
	{':',"3456-"},
	{'/',"456-34-3456-"},
	{'^',"346-3456-"},
	{'*',"0-56-236-3456-"},
	{'-',"36-3456-"},
	//{0x2013,"36-"},
	{'÷',"0-56-256-3456-"},
	{'+',"0-56-235-3456-"},
	{0x2013,"36-3456-"},
	//{0x00ad,"36-"},
};
Table Deception[]{
	{'.','2-'}
};

Table hyphen[]{
	{'-','36-'}
};

Table endnum[]{

	{'%',"0-25-1234-"},
	/*
	{'s','t','0','0',"34-"},
	{'n','d','0','0',"1345-145-"},
	{'r','d','0','0',"1235-145-"},
	{'t','h','0','0',"1456-"},
	{'\'','s','0','0',"3-234-"},
	*/
};

Table Begnum[]{
	{'#',"4-"},
	{'£',"123-"},
	{'+',"56-235-"},
};

Table joinnum[]{
	{'+',"56-235-"},
	{'=',"56-2356-"},
	{'×',"56-236-"},
	{'÷',"56-256-"},

};


Tables repeated[]{

	{'.','.','.','.',"0-"},
	{'_','_','_','_',"456-"},
	{'-','-','-','-',"36-"},


	{'-','-','-','0',"36-36-36-"},
	//{'_','_','_','0',"78-78-78-"},
	{'_','_','_','0',"46-46-46-"},
	{':',':',':','0',"25-25-25-"},
	{'=','=','=','0',"56-2356-56-2356-56-2356-"},
	{'~','~','~','0',"4-156-4-156-4-156-"},
	{'*','*','*','0',"35-35-0-35-35-0-35-35-"},


};
Table midword[]{
	{'-',"36-"},
};

Table litdigit[]{
{'0',"245-"},
{'1',"1-"},
{'2',"12-"},
{'3',"14-"},
{'4',"145-"},
{'5',"15-"},
{'6',"124-"},
{'7',"1245-"},
{'8',"125-"},
{'9',"24-"},

};


Table capital[]{
{'A',"1-"},
{'B',"12-"},
{'C',"14-"},
{'D',"145-"},
{'E',"15-"},
{'F',"124-"},
{'G',"1245-"},
{'H',"125-"},
{'I',"24-"},
{'J',"245-"},
{'K',"13-"},
{'L',"123-"},
{'M',"134-"},
{'N',"1345-"},
{'O',"135-"},
{'P',"1234-"},
{'Q',"12345-"},
{'R',"1235-"},
{'S',"234-"},
{'T',"2345-"},
{'U',"136-"},
{'V',"1236-"},
{'W',"2456-"},
{'X',"1346-"},
{'Y',"13456-"},
{'Z',"1356-"},

};

Table lower[]{
{'a',"1-"},
{'b',"12-"},
{'c',"14-"},
{'d',"145-"},
{'e',"15-"},
{'f',"124-"},
{'g',"1245-"},
{'h',"125-"},
{'i',"24-"},
{'j',"245-"},
{'k',"13-"},
{'l',"123-"},
{'m',"134-"},
{'n',"1345-"},
{'o',"135-"},
{'p',"1234-"},
{'q',"12345-"},
{'r',"1235-"},
{'s',"234-"},
{'t',"2345-"},
{'u',"136-"},
{'v',"1236-"},
{'w',"2456-"},
{'x',"1346-"},
{'y',"13456-"},
{'z',"1356-"},
};





int changetype(Linklist * head) {//判断修改每个节点的字符类型
	Linklist* currentlink;
	Linklist* nood;
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
			/*
			if (currentlink->OneTypeChar[currentlink->len - 1] == 's' && currentlink->next->len == 1 && currentlink->next->OneTypeChar[0] == '\'') {
				currentlink->len--;
				currentlink->next->len++;
				currentlink->next->OneTypeChar[1] = currentlink->next->OneTypeChar[0];
				currentlink->next->OneTypeChar[0] = 's';
				currentlink->next->CharacterType =ENDWORD;
			}*/

			if (currentlink->next == NULL)endflag = 1;
			currentlink = currentlink->next;
			break;
		case NUM:
			if (currentlink->next == NULL)endflag = 1;
			currentlink = currentlink->next;
			break;
		case PUNC:
			if(currentlink->previous==NULL){
			
				if (currentlink->next == NULL) {
					currentlink->CharacterType = WORD;

				}
				else {
				     currentlink->CharacterType = PREPUNC;
					if (currentlink->next->CharacterType == SPACE)currentlink->CharacterType = WORD;
					if (currentlink->next->CharacterType == NUM)currentlink->CharacterType = BEGNUM;
					if (currentlink->next->CharacterType == NUM && (currentlink->OneTypeChar[0] == '#' || currentlink->OneTypeChar[0] == '$'))currentlink->CharacterType = BEGNUM;
					if (currentlink->OneTypeChar[0] == '.' && currentlink->len == 1 && currentlink->next->CharacterType == NUM)currentlink->CharacterType = DECPINT;
					if (currentlink->OneTypeChar[0] == '-' && currentlink->len == 1 && currentlink->next->CharacterType == NUM)currentlink->CharacterType = HYPHEN;
					if (currentlink->next->len == 1 && currentlink->OneTypeChar[0] == '\'' || currentlink->OneTypeChar[0] == '’') {

					}

				}
			}

			if (currentlink->previous != NULL ) {
				if (currentlink->next == NULL) {
					//if (currentlink->CharacterType == CAPITAL || currentlink->CharacterType == LOWER)currentlink->CharacterType = POSTPUNC;
					currentlink->CharacterType = POSTPUNC;
					if (currentlink->previous->CharacterType == SPACE)currentlink->CharacterType = WORD;
					if (currentlink->previous->CharacterType == NUM)currentlink->CharacterType = ENDNUM;
					
				}
				else {
					if (currentlink->previous ->CharacterType == SPACE)currentlink->CharacterType = PREPUNC;
					//if(currentlink->next->CharacterType==SPACE&&(currentlink->previous-> CharacterType==CAPITAL||currentlink->previous->CharacterType==LOWER))currentlink->CharacterType = POSTPUNC;
					if (currentlink->next->CharacterType == SPACE)currentlink->CharacterType = POSTPUNC;
					if (currentlink->next->CharacterType == NUM&&currentlink->previous->CharacterType!=NUM)currentlink->CharacterType = BEGNUM;
					if (currentlink->previous->CharacterType == NUM && currentlink->next->CharacterType == NUM)currentlink->CharacterType = MIDNUM;
					if (currentlink->OneTypeChar[0] == '.' && currentlink->len == 1 && currentlink->next->CharacterType == NUM)currentlink->CharacterType = DECPINT;
					if (currentlink->OneTypeChar[0] == '-' && currentlink->len == 1 && currentlink->next->CharacterType == NUM)currentlink->CharacterType = HYPHEN;
					if (currentlink->previous->CharacterType == NUM&&currentlink->next->CharacterType==SPACE)currentlink->CharacterType = ENDNUM;
					/*if (currentlink->OneTypeChar[0] == '\'' && currentlink->len == 1 && currentlink->next->OneTypeChar[0] == 's' && currentlink->next->len == 1 &&
					(currentlink->next->next == NULL || currentlink->next->next->CharacterType == SPACE)) {
						currentlink->CharacterType = ENDNUM;
						currentlink->len++;
						currentlink->OneTypeChar[currentlink->len - 1] = currentlink->next->OneTypeChar[0];
						
						nood = currentlink->next;
						currentlink->next = currentlink->next->next;
						currentlink->next->previous = currentlink;
						free(nood);
					}*/

					if ((currentlink->OneTypeChar[0] == '-') && currentlink->len == 1 &&
						(currentlink->previous->CharacterType == CAPITAL || currentlink->previous->CharacterType == LOWER) &&
						(currentlink->next->next == NULL || currentlink->next->next->CharacterType == SPACE) && currentlink->next->CharacterType == LOWER) {
						if (currentlink->next->len == 2) {
							if (
								(currentlink->next->OneTypeChar[0] == 't' && currentlink->next->OneTypeChar[1] == 'o') ||
								(currentlink->next->OneTypeChar[0] == 'b' && currentlink->next->OneTypeChar[1] == 'y')) {
								    currentlink->CharacterType = ENDWORD;
							    	currentlink->len = currentlink->len + 2;
								    currentlink->OneTypeChar[currentlink->len - 2] = currentlink->next->OneTypeChar[0];
								    currentlink->OneTypeChar[currentlink->len - 1] = currentlink->next->OneTypeChar[1];
									nood = currentlink->next;
									currentlink->next = currentlink->next->next;
									currentlink->next->previous = currentlink;
									free(nood);
							}
						}
					
					}
					if ((currentlink->OneTypeChar[0] == '\''||currentlink->OneTypeChar[0]=='’') && currentlink->len == 1 && 
						(currentlink->previous->CharacterType == CAPITAL || currentlink->previous->CharacterType == LOWER)&& 
						(currentlink->next->next == NULL || currentlink->next->next->CharacterType == SPACE)&&currentlink->next->CharacterType==LOWER) {
						if (currentlink->next->len == 1) {
						
							if (currentlink->next->OneTypeChar[0] == 'd' ||
								currentlink->next->OneTypeChar[0] == 'm' ||
								currentlink->next->OneTypeChar[0] == 'n' ||
								currentlink->next->OneTypeChar[0] == 'r' ||  
								currentlink->next->OneTypeChar[0] == 't' ||  
								currentlink->next->OneTypeChar[0] == 's' ){
								currentlink->CharacterType = ENDWORD;
								currentlink->len++;
								currentlink->OneTypeChar[currentlink->len - 1] = currentlink->next->OneTypeChar[0];
								nood = currentlink->next;
								currentlink->next = currentlink->next->next;
								currentlink->next->previous = currentlink;
								free(nood);
							}
							
						}
						if (currentlink->next->len == 2) {
							if (
								(currentlink->next->OneTypeChar[0] == 'a' && currentlink->next->OneTypeChar[1] == 'h') ||
								(currentlink->next->OneTypeChar[0] == 'l' && currentlink->next->OneTypeChar[1] == 'l') ||
								(currentlink->next->OneTypeChar[0] == 'r' && currentlink->next->OneTypeChar[1] == 'e') ||
								(currentlink->next->OneTypeChar[0] == 'r' && currentlink->next->OneTypeChar[1] == 'y') ||
								(currentlink->next->OneTypeChar[0] == 'v' && currentlink->next->OneTypeChar[1] == 'e') ||
								(currentlink->next->OneTypeChar[0] == 'r' && currentlink->next->OneTypeChar[1] == 'y') ||
								(currentlink->next->OneTypeChar[0] == 'r' && currentlink->next->OneTypeChar[1] == 'y') 
								) {
								currentlink->CharacterType = ENDWORD;
								currentlink->len= currentlink->len+2;
								currentlink->OneTypeChar[currentlink->len - 2] = currentlink->next->OneTypeChar[0];
								currentlink->OneTypeChar[currentlink->len - 1] = currentlink->next->OneTypeChar[1];
								nood = currentlink->next;
								currentlink->next = currentlink->next->next;
								currentlink->next->previous = currentlink;
								free(nood);
							}
						}
					}					
						
				
					if (currentlink->OneTypeChar[0] == '\'' && currentlink->len == 1 &&
						(currentlink->next->CharacterType == LOWER || currentlink->next->CharacterType == CAPITAL) &&
						(currentlink->previous->CharacterType == LOWER || currentlink->previous->CharacterType == CAPITAL)) {
						currentlink->CharacterType = MIDWORD;
					}

					if (currentlink->previous->CharacterType == SPACE && currentlink->next->CharacterType == SPACE && currentlink->len == 1 && currentlink->OneTypeChar[0] == '-') {
						currentlink->previous->OneTypeChar[1] = currentlink->OneTypeChar[0];
						currentlink->previous->OneTypeChar[2] = currentlink->next->OneTypeChar[0];

						currentlink->previous->len = 3;
						currentlink->previous->CharacterType = ALWAYS_S;

						
						nood = currentlink->next;
						currentlink->previous->next = currentlink->next->next;
						free(currentlink);
						free(nood);
						
						
					}
				}
			
			}

			if (currentlink->len > 1) {
				if (currentlink->len >= 4) {
					for (int i = 0; i < currentlink->len - 4; i++) {
					    if (currentlink->OneTypeChar[i+0] == '.' && currentlink->OneTypeChar[i + 1] == '.' && currentlink->OneTypeChar[i + 2] == '.' && currentlink->OneTypeChar[i + 3] == '"')currentlink->CharacterType = ALWAYS_S;
					    if (currentlink->OneTypeChar[i+0] == '.' && currentlink->OneTypeChar[i + 1] == '.' && currentlink->OneTypeChar[i + 2] == '.' && currentlink->OneTypeChar[i + 3] == '\'')currentlink->CharacterType = ALWAYS_S;
				    	if (currentlink->OneTypeChar[i+0] == '.' && currentlink->OneTypeChar[i + 1] == '.' && currentlink->OneTypeChar[i + 2] == '.' && currentlink->OneTypeChar[i + 3] == '.')currentlink->CharacterType = ALWAYS_S;
				     	if (currentlink->OneTypeChar[i+0] == '_' && currentlink->OneTypeChar[i + 1] == '_' && currentlink->OneTypeChar[i + 2] == '_' && currentlink->OneTypeChar[i + 3] == '_')currentlink->CharacterType = ALWAYS_S;
				    	if (currentlink->OneTypeChar[i + 0] == '-' && currentlink->OneTypeChar[i + 1] == '-' && currentlink->OneTypeChar[i + 2] == '-' && currentlink->OneTypeChar[i + 3] == '-')currentlink->CharacterType = ALWAYS_S;
				}
				}
				if (currentlink->len ==3) {
					if (currentlink->OneTypeChar[0] == '.' && currentlink->OneTypeChar[0] == '.' && currentlink->OneTypeChar[0] == '.' )currentlink->CharacterType = ALWAYS_S;

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

	return 0;
}

int GetOneCharNumDot(u16 ch,Table tab[],char*OneCharDot,int tablesize) {//对节点里的字符取对应的字典里取寻找对应的盲文
	for (int i=0; i < tablesize; i++) {
		if (ch == tab[i].unicode) { 
			strcat(OneCharDot,tab[i].numdot);
			return 1;
		}
	}
	
	int alwastablesize = sizeof(always) / sizeof(always[0]);

	for (int i = 0; i < alwastablesize; i++) {
		if (ch == always[i].unicode) {
			strcat(OneCharDot, always[i].numdot);
			return 1;
		}
	}
	

	return 0;
}

int GetOneCharNumDot_s(u16 ch[], int len,Tables tab[], char* OneCharDot, int tablesize){
	for (int i = 0; i < tablesize; i++) {
		for (int j = 0; j < len; j++) {
			if (ch[j] != tab[i].unicode[j])break;
			if (tab[i].unicode[j + 1] == '0'&&j==len-1) {
				strcat(OneCharDot, tab[i].numdot);
				return 1;
			}
		}
	}
	return 0;
}

int GetOneCharNumDot_ss(u16 ch[], int len, Tabless tab[], char* OneCharDot, int tablesize) {
	for (int i = 0; i < tablesize; i++) {
		for (int j = 0; j < len; j++) {
			if (ch[j] != tab[i].unicode[j])break;
			if (tab[i].unicode[j + 1] == '0' && j == len - 1) {
				strcat(OneCharDot, tab[i].numdot);
				return 1;
			}
		}
	}
	return 0;
}
int TranslateLinkList(Linklist*head,char*NumDot) {//翻译每个节点得到结果
	Linklist* node;
	node = head;
	char OneNodeNumDot[DOTNUMMAX];

	char letsign[4] = "56-";
	char capsletter[3] = "6-";
	char begcapsword[5] = "6-6-";
	char endcapsword[6] = "4-6-";
	char numsign[6] = "3456-";
	char decpoint[4] = "46-";
	char hyphen[4] = "36-";
	char space[3] = "0-";
	char midword[3] = "3-";
	int i = 0;
	int tablesize = 0;
	int endflag = 0;
	while (1) {
		for (i = 0; i < DOTNUMMAX; i++)OneNodeNumDot[i] = '\0';
		switch (node->CharacterType)
		{

		    case(CAPITAL):
				tablesize = sizeof(capital) / sizeof(capital[0]);
				for (int i = 0; i < node->len; i++) {
					
					GetOneCharNumDot(node->OneTypeChar[i],capital, OneNodeNumDot, tablesize);
				}
				if (node->len== 1) {
					if ((node->next->CharacterType == SPACE || node->next == NULL) && (node->previous == NULL || node->previous->CharacterType == SPACE)) {
						
					    strcat(NumDot, letsign);

					}
					
					strcat(NumDot,capsletter);
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
				if (node->len == 1&&((node->previous==NULL)||(node->previous->CharacterType!=CAPITAL &&node->previous->CharacterType != MIDWORD)) && ((node->next == NULL) || (node->next->CharacterType != CAPITAL))) {
					strcat(NumDot, letsign);
					strcat(NumDot, OneNodeNumDot);
				}
				else strcat(NumDot, OneNodeNumDot);
				if (node->next == NULL)endflag = 1;
				node = node->next;
				break;

			case(WORD):
				tablesize = sizeof(Word) / sizeof(Word[0]);
				for (int i = 0; i < node->len; i++) {
					GetOneCharNumDot(node->OneTypeChar[i], Word, OneNodeNumDot, tablesize);
				}
				strcat(NumDot, OneNodeNumDot);
				if (node->next == NULL)endflag = 1;
				node = node->next;
				break;
			case(PREPUNC):
				tablesize = sizeof(Prepunc) / sizeof(Prepunc[0]);
				
				GetOneCharNumDot_s(node->OneTypeChar, node->len, Prepunc, OneNodeNumDot, tablesize);
			
				strcat(NumDot, OneNodeNumDot);
				if (node->next == NULL)endflag = 1;
				node = node->next;
				break;
			case(POSTPUNC):
				tablesize = sizeof(Postpunc) / sizeof(Postpunc[0]);
				GetOneCharNumDot_s(node->OneTypeChar, node->len, Postpunc, OneNodeNumDot, tablesize);
				strcat(NumDot, OneNodeNumDot);
				if (node->next == NULL)endflag = 1;
				node = node->next;
				break;
			case(MIDWORD):
				strcat(NumDot, midword);
				if (node->next == NULL)endflag = 1;
				node = node->next;
				break;
			case(ENDWORD):
				tablesize = sizeof(endword) / sizeof(endword[0]);
				GetOneCharNumDot_ss(node->OneTypeChar, node->len, endword, OneNodeNumDot, tablesize);
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
			case(ENDNUM):
				tablesize = sizeof(endnum) / sizeof(endnum[0]);
				GetOneCharNumDot(node->OneTypeChar[0],endnum,OneNodeNumDot,tablesize);	
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
				if(node->previous==NULL||
					(node->previous->CharacterType!=MIDNUM&&node->previous->CharacterType!=DECPINT&&node->previous->CharacterType!=HYPHEN))
				     strcat(OneNodeNumDot, numsign);
				for (int i = 0; i < node->len; i++) {
					GetOneCharNumDot(node->OneTypeChar[i], litdigit, OneNodeNumDot, tablesize);
				}
				strcat(NumDot, OneNodeNumDot);
				if (node->next == NULL)endflag = 1;
				node = node->next;
				break;
			case(ALWAYS_S):
				tablesize = sizeof(alwayss) / sizeof(alwayss[0]);
				GetOneCharNumDot_ss(node->OneTypeChar, node->len, alwayss, OneNodeNumDot, tablesize);
				strcat(NumDot, OneNodeNumDot);
				if (node->next == NULL)endflag = 1;
				node = node->next;
				break;

		    default:
				strcat(OneNodeNumDot, space);
				strcat(NumDot, OneNodeNumDot);

				if (node->next == NULL)endflag = 1;
				node = node->next;
				break;
			    
		}
		if (endflag==1)break;
	}

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
	else {
		chartype = SPACE;
		return chartype;
	}
}

int BulidLinkList(unsigned short* unibuf,int lenth, char*NumDot) {//建立双向链表的函数
	Linklist* head, * node, * end;//定义头节点普通节点和尾节点
	head = (Linklist*)malloc(sizeof(Linklist));
	end = head;
	enum MyEnum current, previous;//当前字母的类型，和前面一个字母的类型，用以判断是否塞到同一个节点中
	previous = EMPTY;
	current = EMPTY;
	int samtypecount = 0;//统计一节点中的Unicode存了几个了，应该存在哪了
	
	
	int i = 0;

	//int size = sizeof(CharacterLinkList);
	for (int i = 0; i <=lenth; i++) {
		current = JudgmentType(unibuf[i]);//获取当前字符的类型
		if (previous == EMPTY) {//如果是头节点
			head->OneTypeChar[samtypecount] = unibuf[i];
			head->CharacterType = current;
			head->previous = NULL;
			
			node = head;
			previous = current;
		}
		else {//不是头节点
			if(current==previous){//如果类型相同
				samtypecount++;

				node->OneTypeChar[samtypecount] = unibuf[i];

				previous = current;
			//继续添加
			}
			else {//如果字符类型发生变换，则建立新的节点
				node->len = samtypecount+1;//每个节点的长度这个值是指有几个字符，不是从0开始的下标
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
	TranslateLinkList(head,NumDot);

	
	Linklist* h;
	h = head;
	while (head != NULL) {//释放链表空间
		h = head;
		head = head->next;
		free(h);
	}
	return 0;

}




int EnglisfGrade1() {

	u8 EnglishStr[CHARMAX] = {"a-to"};
	u16 unibuf[CHARMAX] = { 0x0000 };
	u16 OneWord[ONEWORDMAX] = { 0x000 };
	char NumDot[DOTNUMMAX];
	int i = 0,j=0;

	StringToUni(EnglishStr, unibuf, strlen((const char*)EnglishStr));
	for (i = 0; i < DOTNUMMAX; i++)NumDot[i] = '\0';
	for (i = 0; i < CHARMAX; i++) {
		if (unibuf[i] != 0x0020&& unibuf[i]!=0x0000) {
			OneWord[j++] = unibuf[i];
			
		}
		else {
			OneWord[j] = 0x0020;

			BulidLinkList(OneWord, j, NumDot);

			for (j = 0; j < ONEWORDMAX; j++) {
				OneWord[j] = 0x0000;

			}
			j = 0;

			if (unibuf[i] == 0x0000)break;
		}
	

	}


	
	return 0;
}