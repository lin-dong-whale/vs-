#include<stdio.h>
#include <conio.h>
#include <iostream>
#include"GetEnglishWord.h"
#define SIZE 100

int up(char* buffer, FILE* fp, int* pos, int fpsize,int*printlenth) {
    int i = 0;
    char ch[2] = {'\0'};
    int spaceset = -1;//��¼�µ�һ�γ��ֻس���λ��
    int enterset = -1;//��¼�µ�һ�γ��ֿո���ַ���λ��
    *pos = *pos - *printlenth-1;//��־λ���ƶ�����ǰ��ʾ���ַ�����
   // fseek(fp, *pos, SEEK_SET);
    if (*pos <= 0) {//����ƶ��󣬱�־λ����0����С��0��˵���ƶ����ļ���ͷ�ˣ��ٰ��Ϸ����ƶ����ļ�ĩβ
        fseek(fp, 0, SEEK_END);
        *pos = ftell(fp);
    }
    for (i = 0; i < SIZE + 1; i++) buffer[i] = '\0';//���

    if(*pos>SIZE){//���Ϸ�������ͷ������SIZE���ֽ���
        *pos = *pos - SIZE;//�ļ�ָ�����SIZE��
        fseek(fp, *pos, SEEK_SET);

        for (i = 0; i < SIZE; i++) {//ѭ����ȡSIZE�Σ������жϿո�ͻس�����
            fgets(ch, 2, fp);//ȡһ���ַ���Ҫ2����һ�����ַ��������š�\0��
            if ((ch[0] == '\n') && enterset == -1) { enterset = i; break; }//�������ַ��ǻس�����λ�ñ���û�¸�ֵ���͸�����ֵ����ô����Ϊ�˻�ȡ����һ�γ��ֻس���λ��
            if ((ch[0] == ' ' || ch[0] == ',' || ch[0] == '.' || ch[0] == '?' || ch[0] == '!') && spaceset == -1) { spaceset = i;}//ȡ���⼸������λ��

        }
        fseek(fp, *pos, SEEK_SET);//�������Ȼ�ȥ�ոջ�û������λ��
        if (enterset == -1||enterset==SIZE-1) {//���û�лس�
            if(spaceset==-1){//���û��������㣬��ȫ����ʾ
                fgets(buffer, SIZE + 1, fp);
            }
            else {//����б�㣬����ʾ��һ����㵽������ַ�
                fseek(fp, *pos+spaceset+1, SEEK_SET);//�ļ�ָ���ƶ������ĺ��棬�ñ�㲻ȡ��
                fgets(buffer, SIZE + 1- spaceset -1, fp);//

            }

        }
        else {//����лس�
            fseek(fp, *pos + enterset + 1, SEEK_SET);//�ļ�ָ���ƶ����س�����
            fgets(buffer, SIZE + 1 - enterset - 1, fp);//��ȡ��һ���س�������������ַ�

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
    {//���Ϸ�������ͷ��������SIZE���ֽ���
        fseek(fp, 0, SEEK_SET);//�ƶ�����ͷ
        if (fgets(buffer, *pos+1, fp) != NULL) {//ȫ����ȡ��ʾ
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
    
    if (ftell(fp) == fpsize) { fseek(fp, 0, SEEK_SET); *pos = ftell(fp);}//�ļ�ָ������ƶ����ļ�ĩβ�����µ��·������ƶ����ļ���ͷ������
    for (i = 0; i < SIZE + 1; i++) buffer[i] = '\0';//ѭ�������ʾ����

    if (fgets(buffer, SIZE + 1, fp) != NULL) {//��ȡSIZE���ֽ�Ҫ+1�����һ��λ����Ҫ����'\0'

        if (ftell(fp) == fpsize) {//�����ȡ���ļ�ĩβ�ˣ��Ͷ���ʾ�������˳�
            *pos = 0;
            printf("%s\n", buffer);
            return 0;
        }

        *printlenth = strlen(buffer) - 1;//���㵱ǰ��ʾ�ĳ��ȣ�printlenth���±�0��ʼ��
       

        if (*printlenth == 0 && buffer[*printlenth] == '\n')return 0;//�����ȡֻ��ȡ��һ���س����п����ϴ�ֻȡһ�����е��µ�
        while (buffer[*printlenth] != ',' && buffer[*printlenth] != '.' && buffer[*printlenth] != '?'&& buffer[*printlenth] != '!'&& buffer[*printlenth] != ';' && buffer[*printlenth] != ' ' && buffer[*printlenth] != '\n' && buffer[*printlenth] != '\r')
        {

            buffer[*printlenth] = '\0';//�Ѻ��漸����Ҫ���ַ����ɡ�\0��
            *printlenth= *printlenth-1;
        }

        printf("%s\n", buffer);
        *pos = *pos + *printlenth + 1;//��¼���ļ�ָ��Ӧ���ڵ�λ�ã���Ϊprintlenth���±�0��ʼ������Ҫ+1

        //fgetpos(fp, &pos);
        fseek(fp, *pos, 0);//�ƶ��ļ�ָ�뵽Ŀǰ��ʾ�����һ���ַ���λ��

    }

    return 0;
}*/


int down(char* buffer, FILE* fp, int* pos, int fpsize, int* printlenth) {
    int i = 0;
    int spaceset = -1;//��¼�µ�һ�γ��ֻس���λ��
    int enterset = -1;//��¼�µ�һ�γ��ֿո���ַ���λ��
    int markset = -1;//��¼�µ�һ�γ��ֱ���λ��

    if (ftell(fp) == fpsize) { fseek(fp, 0, SEEK_SET); *pos = ftell(fp); }//�ļ�ָ������ƶ����ļ�ĩβ�����µ��·������ƶ����ļ���ͷ������
    for (i = 0; i < SIZE + 1; i++) buffer[i] = '\0';//ѭ�������ʾ����

    if (fgets(buffer, SIZE + 1, fp) != NULL) {//��ȡSIZE���ֽ�Ҫ+1�����һ��λ����Ҫ����'\0'

        if (ftell(fp) == fpsize) {//�����ȡ���ļ�ĩβ�ˣ��Ͷ���ʾ�������˳�
            *pos = 0;
            printf("%s\n", buffer);
            return 0;
        }
        *printlenth = strlen(buffer) - 1;//���㵱ǰ��ʾ�ĳ��ȣ�printlenth���±�0��ʼ��
        if (*printlenth == 0 && buffer[*printlenth] == '\n') { 
            fseek(fp, *pos+1, SEEK_SET);
            *pos = *pos + 1;
            fgets(buffer, SIZE + 1, fp);
            }//�����ȡֻ��ȡ��һ���س����п����ϴ�ֻȡһ�����е��µ�
        *printlenth = strlen(buffer) - 1;//���㵱ǰ��ʾ�ĳ��ȣ�printlenth���±�0��ʼ��

        

        //����Ǳ����ţ���¼�±����ŵ�λ��
        for (int j = *printlenth; j >= 0; j--) {
            if ((buffer[j] == ',') || (buffer[j] == '.') || (buffer[j] == '?') || (buffer[j] == '!') || (buffer[j] == ';'))
            {
                markset = j;
                break;
            }
        }
        //����ǿո񣬼�¼�µ�һ���ո��λ��
        for (int m = *printlenth; m >= 0; m--) {
            if (buffer[m] == ' ')
            {
                spaceset = m;
                break;
            }
        }
        //��¼���з�λ��
        for (int n = *printlenth; n >= 0; n--) {
            if ((buffer[n] == '\n') || (buffer[n] == '\r'))
            {
                enterset = n;
                break;
            }
        }
        //����
        if (enterset > 0) {//����лس���ȡ���س���λ�ã��ӵ�ǰλ�õ��س���λ��д��buffer

            fseek(fp, *pos, SEEK_SET);
            fgets(buffer, enterset+2, fp);
            *pos = *pos + enterset + 1;
            *printlenth = enterset;

        }
        else {//û�лس��Ļ��������ж���û�б����ţ��еĻ��������һ������λ�ã�д�����飬û�б�������һ���ո�Ϊ���λ�ã�ͬ��д�����顣
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
    int pos=0;//һֱ���㣬�ļ�ָ��Ӧ���ڵ�λ��
    int printlenth = 0;//����Ŀǰ��һ���ж��ٸ��ַ���ʾ�ģ������Ϸ���ʱ������printlenth+1���ֽڣ�����SIZE�����ٻ�ȡ�ж�
    char buffer[SIZE+1] = { '\0' };
    if ((fp = fopen("D:\\LD\\vc-c\\TranslationBaseLiblouis\\test.txt", "rb")) == NULL)//���ļ����ɹ�
    {
        printf("The file can not be opened.\n");
        return 0;//���������ִ��
    }
    fseek(fp, 0, SEEK_END);//�ƶ����ļ�ĩβ�������仰�ǻ�ȡ�ļ��Ĵ�С���ٰ��ļ�ָ���ƶ��ؿ�ͷ
    int fpsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    if (fgets(buffer, SIZE+1, fp) != NULL) {//��ȡSIZE���ֽ�Ҫ+1�����һ��λ����Ҫ����'\0'
        printlenth = strlen(buffer) - 1;//������ʾ�ĳ��ȣ�printlenth���±�0��ʼ��
     
        while (buffer[printlenth] != ',' && buffer[printlenth] != '.' && buffer[printlenth] != '?' && buffer[printlenth] != '!' 
            && buffer[printlenth] != ';' && buffer[printlenth] != ' ' && buffer[printlenth] != '\n' && buffer[printlenth] != '\r')
        {

            buffer[printlenth] = '\0';//�Ѻ��漸����Ҫ���ַ����ɡ�\0��
            printlenth--;
        }

        printf("%s\n", buffer);
        pos = pos + printlenth + 1;//��¼���ļ�ָ��Ӧ���ڵ�λ�ã���Ϊprintlenth���±�0��ʼ������Ҫ+1

        //fgetpos(fp, &pos);
        fseek(fp, pos, 0);//�ƶ��ļ�ָ�뵽posλ

    }

    int ch;

    while (1) {//ѭ����ؼ�������

        if (_kbhit()) {//����а������£���_kbhit()����������
            ch = _getch();//ʹ��_getch()��ȡ���µļ�ֵ

            if (ch == 119) {//���ü��̰�w�Ϸ�
                up(buffer, fp, &pos, fpsize, &printlenth);//�������:��ʾ���顢�ļ�ָ�롢�ļ�ָ���־λ���ļ���С����0Ϊ�±������ÿ����ʾ��Ԫ�ظ���
            }


            if (ch == 115) {//���ü��̰�s�·�
                down(buffer,fp,&pos, fpsize, &printlenth);//�·����ú���
            }
            if (ch == 27) { break; }//������ESCʱ�˳�ѭ����ESC���ļ�ֵ��27.
        }
    }

    return 0;
}