#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int distance;           //路径长度
    char way[200];          //路径
}path;

typedef struct{
    int num;                //顶点序号
    int in;                 //入度
    char name;              //顶点名字
    int come[10];           //存储该顶点前序顶点的序号
    int go[10];             //存储该顶点指向的顶点的序号和权重
    int out;                //表示该节点是否被剔除
    int hour;               //表示该顶点的工作时间
}vertex;


//////////////////用的是深度优先搜索(DFS),这里的int distance 和 int nov个人觉得是关键，一开始用的是int* distance 和 int* nov////////////////

void find_all_path(vertex* Vertex,path* paths,int j,int n,char* way,int distance,int* nop,int nov){
    vertex* cur=Vertex+j;     //cur指向当前顶点
    //if (cur->num==n-1){strcpy(paths[(*nop)++].way,way);paths[(*nop)-1].distance=*distance+Vertex[n-1].hour;memset(way,'\0',100);*distance=0;}
    if (cur->num==n-1){way[nov]='\0';strcpy(paths[(*nop)++].way,way);paths[(*nop)-1].distance=distance+Vertex[n-1].hour;}
    for (int i=0;i<10;i++){
        if (cur->go[i]>0){
            way[nov]=Vertex[cur->go[i]-1].name;
            int new_distance=distance+(cur->hour);
            find_all_path(Vertex,paths,cur->go[i]-1,n,way,new_distance,nop,nov+1);
        }
    }
}


path* find_min_path(path* paths,int* nop){
    int min=0;    //min是最短路径的序号
    for (int i=0;i<*nop;i++){
        if (paths[i].distance<paths[min].distance){
            min=i;
        }
    }
    return paths+min;
}

int find_in(vertex* Vertex,int n){
    for (int i=0;i<n;i++){
        if (Vertex[i].in==0 && Vertex[i].out==0){
            return i;
        }
    }
    return -1;    //若没有入度为0的顶点，说明图中存在回路
}

int is_circle(vertex* Vertex,int n){
    int q,m;
    vertex* v,*vv;
    for (int i=0;i<n;i++){
        if ((q=find_in(Vertex,n))!=-1){
            v=Vertex+q;
            v->out=1;
            m=0;
            while (v->go[m++]!=0){
                vv=Vertex+v->go[m-1]-1;
                vv->in-=1;
            }
        }
    }
    if (q==-1){
        printf("该图中有环，成环的顶点为:");
        for (int i=0;i<n;i++){
            if (!Vertex[i].out){printf("%c ",Vertex[i].name);}
        }
    }
    if (q==-1){return 1;}
    else{return 0;}
}

int main(){
    char name[20];
    printf("请输入文件名：(p02.txt为自带的无环文件  p03.txt为可修改的有环文件)\n");
    scanf("%s",name);
    FILE* fp=fopen(name,"r");
    if (fp == NULL){printf("文件p02.txt打开失败\n");}
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
            if (1<=atoi(token) && atoi(token)<=18){Vertex[n].hour=atoi(token);}
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
        Vertex[i].out=0;
    }


    if (!is_circle(Vertex,n)){
        char way[200];              //暂时存储每次的路径
        int distance=0;             //暂时存储每次路径的长度和
        path paths[100];            //遍历所有的路径，并存到paths中
        int nop=0;                  //num of path 表示第几条路径
        //int nov=0;                  //num of vertex 表示某条路径的第几个顶点
        find_all_path(Vertex,paths,0,n,way,0,&nop,0);
        printf("\n图中无环\n从A到W的最短路径为：A --> ");
        for (int i=0;i<strlen(find_min_path(paths,&nop)->way)-1;i++){
            printf("%c --> ",find_min_path(paths,&nop)->way[i]);
        }
        printf("W\n");
        printf("最短路径为：%d",find_min_path(paths,&nop)->distance);
    }

}

