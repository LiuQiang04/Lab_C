#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct{
    unsigned char hz[5];   
    char code[24];
}Node;

void read(FILE* fp,Node* node){
    int i=0;
    char str[30];
    char* token;
    while (fgets(str,30,fp) != NULL){   
        token=strtok(str,":");
        strcpy((node+i)->hz,token);
        token=strtok(NULL,":");
        strcpy((node+i)->code,token);
        (node+i)->code[strlen((node+i)->code)-1]='\0';
        i++;
        memset(str,'\0',30);
    }
}

char* find(Node* node, unsigned char* hanzi) {
	int i; 
    for (i = 0; i < 4005; i++) {
        // 将汉字转换为字符串
        // char hanzi_str[4];
        // sprintf(hanzi_str, "%c%c%c", hanzi[0], hanzi[1], hanzi[2]);

        // 使用字符串比较函数来比较汉字
        if (strcmp(hanzi, node[i].hz) == 0) {
            printf("0");
            return node[i].code;
        }
    }
    printf("\n\n");
    return node[0].code;
}


int main() {

    Node node[4100];

    FILE *fp,*new_fp,*p;
    fp = fopen("The Three Kingdoms.txt", "rb"); // 以二进制方式打开文件
    if (fp == NULL) {
        printf("无法打开文件。\n");
        return 1;
    }

    new_fp = fopen("The zipped.bin", "wb");
    if (new_fp == NULL) {
        printf("无法打开文件。\n");
        return 1;
    }

    p = fopen("D:\\Lab\\C and Cpp\\C08\\C8.3\\The Char_code of the Three Kingdoms.txt", "r");
    if (p == NULL) {
        printf("无法打开文件。\n");
        return 1;
    }

    read(p,node);

    uint8_t byte,byte1=0;
    int i=0,n;
    while (fread(&byte, sizeof(uint8_t), 1, fp) == 1) {
        // 如果是UTF-8编码的中文字符的第一个字节
        if ((byte & 0xF0) == 0xE0) {
            // 读取后续两个字节
            uint8_t byte2, byte3;
            fread(&byte2, sizeof(uint8_t), 1, fp);
            fread(&byte3, sizeof(uint8_t), 1, fp);
            // 输出UTF-8编码的中文字符
            unsigned char hanzi[5] = {byte,byte2,byte3,'\0','\0'};
            char* w_str=find(node,hanzi);
            for (n=0;n<strlen(w_str);n++){
                byte1 << 1;
                i++;
                if (w_str[n] == '1'){byte1 += 1;}
                if (i==8){fwrite(&byte1,1,1,new_fp);byte1=0;i=0;}        
            }
        } else {    //单独处理换行符  110111000
            char ww_str[]={'1','1','0','1','1','1','0','0','0'};  //  '\n'的哈夫曼编码111101110
            for (n=0;n<9;n++){
                byte1 << 1;
                i++;
                if (ww_str[n] == '1'){byte1 += 1;}
                if (i==8){fwrite(&byte1,1,1,new_fp);byte1=0;i=0;}
            }
        }
    }

    // 关闭文件
    fclose(fp);
    fclose(new_fp);
    fclose(p);

    return 0;
}
