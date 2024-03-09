#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int num;            //顶点序号
    int in;             //入度
    char name;          //顶点名字
    int come[10];       //存储该顶点前序顶点的序号
    int go[10];         //存储该顶点指向的顶点的序号
}vertex;

int main(){
    FILE* fp=fopen("p01.txt","r");
    if (fp == NULL){printf("文件p01.txt打开失败\n");}
    vertex Vertex[100];
    int n=0,m;          //n是顶点序号，m是顶点入度
    char str[100];
    char* token;
    fgets(str,100,fp);
    while (fgets(str,100,fp)!=NULL){
        token=strtok(str,",");
        Vertex[n].name=token[0];
        memset(Vertex[n].come,0,40);   //初始化come为0
        m=0;  //记录入度
        while ((token=strtok(NULL,","))!=NULL){
            if ('A'<=token[0] && token[0]<='Z'){m++;Vertex[n].come[m-1]=(token[0]-'A'+1);}
        }
        Vertex[n].num=n;
        Vertex[n].in=m;
        n++;
    }

    char go_num[n];   //go_num数组记录每个顶点指向的顶点个数,n其实就是AOV网中顶点总个数
    memset(go_num,0,n);
    for (int i=0;i<n;i++){memset(Vertex[i].go,0,40);}

    for (int i=0;i<n;i++){
        for (int j=0;j<10;j++){
            if (Vertex[i].come[j]!=0){
                Vertex[Vertex[i].come[j]-1].go[go_num[Vertex[i].come[j]-1]++]=i+1;
            }
        }
    }

    //输出
    printf("项目的邻接表为：\n");
    for (int i=0;i<n;i++){
        printf("%d %d %c",i,Vertex[i].in,Vertex[i].name);
        int q=0;
        while (1<=Vertex[i].go[q++] && Vertex[i].go[q-1]<=n){
            printf("->%d",Vertex[i].go[q-1]-1);
        }
        printf("^\n");
    }

}
