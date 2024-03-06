#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct 
{
    unsigned char name[5];  //该节点对应的字符
    int w;  //权重(weight)
    int num;  //该节点在数组中的序号
    int f_num;  //父节点在数组中的序号(father num)
    int lk_num;  //左孩子节点在数组中的序号(left kid num)
    int rk_num;  //右孩子节点在数组中的序号(right kid num)
    bool is_up_node;  //是否为根节点
}Node;

void read(Node* node,int* i);
int find_min(Node* node, int i);
int find_sub_min(Node* node, int i,int min);
void combine_node(Node* node, int* i);
void encode(Node* current_node,Node* first_node,char code[], int index,FILE* p);


int main(){
    int i=0;  //i表示当前的所有节点个数，实时更新!
    Node node[8500];   
    memset(node,-1,8500*sizeof(Node));
    read(node,&i);
    combine_node(node,&i);
    FILE* p = fopen("The Char_code of the Three Kingdoms.txt","w");
    if (p==NULL){
        printf("文件打开失败\n");
    }
    char code[100];
    encode(node+i-1,node,code,0,p);
}


//read函数用于读入数据到结构体数组node
void read(Node* node,int* i){  //i是叶子节点数，也就是初始树的总数
    FILE* fp=fopen("The Char of the Three Kingdoms.txt","r");
    if (fp==NULL){
        printf("文件打开失败\n");
    }
    char str[20];
    while (fgets(str,20,fp) != NULL){
        char* token = strtok(str,",");
        while (token != NULL){
            //Node* a=(node+*i);
            strcpy((node+*i)->name,token);
            token=strtok(NULL,",");
            (node+*i)->w=atoi(token);
            (node+*i)->is_up_node=true;
            (node+*i)->num=*i;
            token=NULL;
            (*i)++;
        }
        memset(str,'\0',20);
    }
}

int find_min(Node* node, int i){
    int n,min;
    //初始化min
    for (n=0;n<i;n++){
        if ((node+n)->is_up_node){
            min=n;
            break;
        }
    }
    //遍历所有节点找到min
    for (n=0;n<i;n++){
        //b=*(node+n);
        if ((node+n)->is_up_node && (node+n)->w < (node+min)->w){
            min=n;
        }
    }

    return min;
}

int find_sub_min(Node* node, int i,int min){
    int n,sub_min;
    //初始化sub_min
    for (n=0;n<i;n++){
        if ((node+n)->is_up_node && n!=min){
            sub_min=n;
            break;
        }
    }
    //遍历所有节点找到sub_min
    for (n=0;n<i;n++){
        //b=*(node+n);
        if ((node+n)->is_up_node && (node+n)->w < (node+sub_min)->w && n!=min){
            sub_min=n;
        }
    }

    return sub_min;
}


//combine_node函数用于创建哈夫曼树
void combine_node(Node* node, int* i){     //i是目前节点总个数
    int j=*i;              //j是当前树的个数
    int min,sub_min;     //min是lk(left kid)的序号，sub_min是rk(right kid)的序号
    //Node b;                              
    while (j>1){      //每个while循环表示一轮操作
        min=find_min(node,*i);
        sub_min=find_sub_min(node,*i,min);

        (node+*i)->w=(node+min)->w+(node+sub_min)->w;  //(node+*i)指向新增的节点
        (node+*i)->num=*i;
        (node+*i)->lk_num=(node+min)->num;
        (node+*i)->rk_num=(node+sub_min)->num;
        (node+min)->f_num=(node+*i)->num;
        (node+sub_min)->f_num=(node+*i)->num;
        (node+*i)->is_up_node=true;
        (node+min)->is_up_node=false;
        (node+sub_min)->is_up_node=false;

        (*i)++;  //节点总数+1
        j--;  //树-1
    }
}


void encode(Node* current_node,Node* first_node,char code[], int index,FILE* p){

    if (current_node->lk_num == -1 && current_node->rk_num == -1){
        code[index]='\0';
        if (current_node->num==0){fprintf(p,"\\n:%s\n",code);}
        else {fprintf(p,"%s:%s\n",current_node->name,code);}
    }else{
        code[index]='0';
        encode(first_node+(current_node->lk_num),first_node,code,index+1,p);
        code[index]='1';
        encode(first_node+(current_node->rk_num),first_node,code,index+1,p);
    }

}