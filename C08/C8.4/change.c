#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(){
    FILE *fp1,*fp2;
    fp1 = fopen("codes.txt","r");
    fp2 = fopen("codes1.txt","w");
    char str[40];
    memset(str,'\0',40);
    while (fgets(str,40,fp1) != NULL){
        str[strlen(str)-1]='\\';
        str[strlen(str)]='n';
        fprintf(fp2,"%s",str);
        memset(str,'\0',40);
    }
}