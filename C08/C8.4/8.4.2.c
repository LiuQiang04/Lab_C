#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    unsigned char hz[5];   
    char code[30];
}Node;

void read(FILE* fp,Node* node){
    int i=0;
    char str[40];
    char* token;
    while (fgets(str,40,fp) != NULL){   
        token=strtok(str," ");
        strcpy((node+i)->hz,token);
        token=strtok(NULL," ");
        strcpy((node+i)->code,token);
        (node+i)->code[strlen((node+i)->code)-1]='\0';
        i++;
        memset(str,'\0',40);
    }
}

bool is_find(Node* node, char* code,int* p) {
    for (int i = 0; i < 3947; i++) {
        // 使用字符串比较函数来比较汉字
        if (strcmp(code, node[i].code) == 0) {
            *p=i;
            return true;
        }
    }
    return false;
}


int main() {

    Node node[4100];

    FILE *fp,*new_fp,*p;
    //fp = fopen("The zipped.bin", "rb");
    fp = fopen("D:\\Lab\\C and Cpp\\C08\\C8.4\\yasuo.bin","rb");
    if (fp == NULL) {
        printf("无法打开The zipped.bin文件。\n");
        return 1;
    }

    new_fp = fopen("The zipped.txt", "w");
    if (new_fp == NULL) {
        printf("无法创建三国演义压缩文件。\n");
        return 1;
    }

    //p = fopen("D:\\Lab\\C and Cpp\\C08\\C8.3\\The Char_code of the Three Kingdoms.txt", "r");
    p = fopen("D:\\Lab\\C and Cpp\\C08\\C8.4\\codes.txt","r");
    if (p == NULL) {
        printf("无法打开哈夫曼编码文件。\n");
        return 1;
    }

    read(p,node);

    uint8_t byte;
    char c[30];
    memset(c,'\0',30);
    int n=0,i,m;
    while (fread(&byte, 1, 1, fp) == 1){
        for (i=0;i<8;i++){
            c[n++] = '0' + ((byte >> (7-i))&1);
            if (n>=4){
                if (is_find(node,c,&m)){
                    if (strcmp(node[m].hz,"\\n")==0){fprintf(new_fp,"\n");}
                    else {fprintf(new_fp,"%s",node[m].hz);}
                    memset(c,'\0',30);n=0;
                }
            }
        }
    }

    // 关闭文件
    fclose(fp);
    fclose(new_fp);
    fclose(p);

    return 0;
}
