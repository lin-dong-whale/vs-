#include<stdio.h>
#include <conio.h>
#include <iostream>
#include"GetEnglishWord.h"
#define SIZE 100

int up(char* buffer, FILE* fp, int* pos, int fpsize,int*printlenth) {
    int i = 0;
    char ch[2] = {'\0'};
    int spaceset = -1;//记录下第一次出现回车的位置
    int enterset = -1;//记录下第一次出现空格等字符的位置
    *pos = *pos - *printlenth-1;//标志位先移动，当前显示的字符个数
   // fseek(fp, *pos, SEEK_SET);
    if (*pos <= 0) {//如果移动后，标志位等于0或者小于0，说明移动到文件开头了，再按上翻就移动到文件末尾
        fseek(fp, 0, SEEK_END);
        *pos = ftell(fp);
    }
    for (i = 0; i < SIZE + 1; i++) buffer[i] = '\0';//清空

    if(*pos>SIZE){//往上翻，到开头，满足SIZE个字节了
        *pos = *pos - SIZE;//文件指针回退SIZE个
        fseek(fp, *pos, SEEK_SET);

        for (i = 0; i < SIZE; i++) {//循环获取SIZE次，用来判断空格和回车在哪
            fgets(ch, 2, fp);//取一个字符，要2，另一个是字符结束符号‘\0’
            if ((ch[0] == '\n') && enterset == -1) { enterset = i; break; }//如果这个字符是回车，且位置变量没新赋值，就给他赋值，这么做是为了获取到第一次出现回车的位置
            if ((ch[0] == ' ' || ch[0] == ',' || ch[0] == '.' || ch[0] == '?' || ch[0] == '!') && spaceset == -1) { spaceset = i;}//取到这几个标点的位置

        }
        fseek(fp, *pos, SEEK_SET);//遍历完先回去刚刚还没遍历的位置
        if (enterset == -1||enterset==SIZE-1) {//如果没有回车
            if(spaceset==-1){//如果没有上述标点，则全部显示
                fgets(buffer, SIZE + 1, fp);
            }
            else {//如果有标点，及显示第一个标点到后面的字符
                fseek(fp, *pos+spaceset+1, SEEK_SET);//文件指针移动到标点的后面，让标点不取到
                fgets(buffer, SIZE + 1- spaceset -1, fp);//

            }

        }
        else {//如果有回车
            fseek(fp, *pos + enterset + 1, SEEK_SET);//文件指针移动到回车后面
            fgets(buffer, SIZE + 1 - enterset - 1, fp);//获取第一个回车到后面的所有字符

        }
        *printlenth = strlen(buffer)-1;
        *pos = ftell(fp);
        printf("%s\n", buffer);
        /*
        if (fgets(buffer, SIZE+1, fp) != NULL) {
            i = 0;
            while (buffer[i] != ',' && buffer[i] != '.' && buffer[i] != '?' && buffer[i] != '!'&& buffer[i] != ';' && buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\r')
            {
                buffer[i] = ' ';
                i++;
            }
            *printlenth= strlen(buffer) - i-1;
            *pos = ftell(fp);
            printf("%s\n", buffer);
        }
        */
    }
    else
    {//往上翻，到开头，不满足SIZE个字节了
        fseek(fp, 0, SEEK_SET);//移动到开头
        if (fgets(buffer, *pos+1, fp) != NULL) {//全部获取显示
            i = 0;
            //while (buffer[i] != ',' && buffer[i] != '.' && buffer[i] != '?' && buffer[i] != '!'&& buffer[i] != ';' && buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\r')
           // {
           //     buffer[i] = ' ';
           //     i++;
           // }
            *printlenth = strlen(buffer) - i;
            *pos = ftell(fp);
            printf("%s\n", buffer);
        }
    }

    return 0;
}
/*
int down(char*buffer,FILE*fp,int *pos, int fpsize,int *printlenth) {
    int i = 0;
    
    if (ftell(fp) == fpsize) { fseek(fp, 0, SEEK_SET); *pos = ftell(fp);}//文件指针如果移动到文件末尾还按下的下翻，就移动到文件开头，继续
    for (i = 0; i < SIZE + 1; i++) buffer[i] = '\0';//循环清空显示数组

    if (fgets(buffer, SIZE + 1, fp) != NULL) {//获取SIZE个字节要+1，最后一个位置需要留给'\0'

        if (ftell(fp) == fpsize) {//如果获取到文件末尾了，就都显示出来，退出
            *pos = 0;
            printf("%s\n", buffer);
            return 0;
        }

        *printlenth = strlen(buffer) - 1;//计算当前显示的长度，printlenth从下标0开始算
       

        if (*printlenth == 0 && buffer[*printlenth] == '\n')return 0;//如果获取只获取了一个回车，有可能上次只取一个换行导致的
        while (buffer[*printlenth] != ',' && buffer[*printlenth] != '.' && buffer[*printlenth] != '?'&& buffer[*printlenth] != '!'&& buffer[*printlenth] != ';' && buffer[*printlenth] != ' ' && buffer[*printlenth] != '\n' && buffer[*printlenth] != '\r')
        {

            buffer[*printlenth] = '\0';//把后面几个不要的字符换成‘\0’
            *printlenth= *printlenth-1;
        }

        printf("%s\n", buffer);
        *pos = *pos + *printlenth + 1;//记录下文件指针应该在的位置，因为printlenth从下标0开始算所以要+1

        //fgetpos(fp, &pos);
        fseek(fp, *pos, 0);//移动文件指针到目前显示完最后一个字符的位置

    }

    return 0;
}*/


int down(char* buffer, FILE* fp, int* pos, int fpsize, int* printlenth) {
    int i = 0;
    int spaceset = -1;//记录下第一次出现回车的位置
    int enterset = -1;//记录下第一次出现空格等字符的位置
    int markset = -1;//记录下第一次出现标点的位置

    if (ftell(fp) == fpsize) { fseek(fp, 0, SEEK_SET); *pos = ftell(fp); }//文件指针如果移动到文件末尾还按下的下翻，就移动到文件开头，继续
    for (i = 0; i < SIZE + 1; i++) buffer[i] = '\0';//循环清空显示数组

    if (fgets(buffer, SIZE + 1, fp) != NULL) {//获取SIZE个字节要+1，最后一个位置需要留给'\0'

        if (ftell(fp) == fpsize) {//如果获取到文件末尾了，就都显示出来，退出
            *pos = 0;
            printf("%s\n", buffer);
            return 0;
        }
        *printlenth = strlen(buffer) - 1;//计算当前显示的长度，printlenth从下标0开始算
        if (*printlenth == 0 && buffer[*printlenth] == '\n') { 
            fseek(fp, *pos+1, SEEK_SET);
            *pos = *pos + 1;
            fgets(buffer, SIZE + 1, fp);
            }//如果获取只获取了一个回车，有可能上次只取一个换行导致的
        *printlenth = strlen(buffer) - 1;//计算当前显示的长度，printlenth从下标0开始算

        

        //如果是标点符号，记录下标点符号的位置
        for (int j = *printlenth; j >= 0; j--) {
            if ((buffer[j] == ',') || (buffer[j] == '.') || (buffer[j] == '?') || (buffer[j] == '!') || (buffer[j] == ';'))
            {
                markset = j;
                break;
            }
        }
        //如果是空格，记录下第一个空格的位置
        for (int m = *printlenth; m >= 0; m--) {
            if (buffer[m] == ' ')
            {
                spaceset = m;
                break;
            }
        }
        //记录换行符位置
        for (int n = *printlenth; n >= 0; n--) {
            if ((buffer[n] == '\n') || (buffer[n] == '\r'))
            {
                enterset = n;
                break;
            }
        }
        //处理
        if (enterset > 0) {//如果有回车，取到回车的位置，从当前位置到回车的位置写进buffer

            fseek(fp, *pos, SEEK_SET);
            fgets(buffer, enterset+2, fp);
            *pos = *pos + enterset + 1;
            *printlenth = enterset;

        }
        else {//没有回车的话，首先判断有没有标点符号，有的话记下最后一个标点的位置，写进数组，没有标点以最后一个空格为最后位置，同样写进数组。
            if (markset > 0) {
                fseek(fp, *pos, SEEK_SET);
                fgets(buffer, markset+2, fp);
                *pos = *pos + markset + 1;
                *printlenth = markset;
            }
            else {
                if (spaceset > 0) {
                    fseek(fp, *pos, SEEK_SET);
                    fgets(buffer, spaceset + 2, fp);
                    *pos = *pos + spaceset + 1;
                    *printlenth = spaceset;
                }
            }
        }
        printf("%s\n", buffer);
    }
}

int inint() {
    FILE* fp;
    int i=0;
    int pos=0;//一直计算，文件指针应该在的位置
    int printlenth = 0;//计算目前这一段有多少个字符显示的，用以上翻的时候先退printlenth+1个字节，再退SIZE个，再获取判断
    char buffer[SIZE+1] = { '\0' };
    if ((fp = fopen("D:\\LD\\vc-c\\TranslationBaseLiblouis\\test.txt", "rb")) == NULL)//打开文件不成功
    {
        printf("The file can not be opened.\n");
        return 0;//结束程序的执行
    }
    fseek(fp, 0, SEEK_END);//移动到文件末尾，这三句话是获取文件的大小，再把文件指针移动回开头
    int fpsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    if (fgets(buffer, SIZE+1, fp) != NULL) {//获取SIZE个字节要+1，最后一个位置需要留给'\0'
        printlenth = strlen(buffer) - 1;//计算显示的长度，printlenth从下标0开始算
     
        while (buffer[printlenth] != ',' && buffer[printlenth] != '.' && buffer[printlenth] != '?' && buffer[printlenth] != '!' 
            && buffer[printlenth] != ';' && buffer[printlenth] != ' ' && buffer[printlenth] != '\n' && buffer[printlenth] != '\r')
        {

            buffer[printlenth] = '\0';//把后面几个不要的字符换成‘\0’
            printlenth--;
        }

        printf("%s\n", buffer);
        pos = pos + printlenth + 1;//记录下文件指针应该在的位置，因为printlenth从下标0开始算所以要+1

        //fgetpos(fp, &pos);
        fseek(fp, pos, 0);//移动文件指针到pos位

    }

    int ch;

    while (1) {//循环监控键盘输入

        if (_kbhit()) {//如果有按键按下，则_kbhit()函数返回真
            ch = _getch();//使用_getch()获取按下的键值

            if (ch == 119) {//设置键盘按w上翻
                up(buffer, fp, &pos, fpsize, &printlenth);//传入参数:显示数组、文件指针、文件指针标志位、文件大小、以0为下标计数的每次显示的元素个数
            }


            if (ch == 115) {//设置键盘按s下翻
                down(buffer,fp,&pos, fpsize, &printlenth);//下翻调用函数
            }
            if (ch == 27) { break; }//当按下ESC时退出循环，ESC键的键值是27.
        }
    }

    return 0;
}