#include<stdio.h>
int main(){
    FILE *aa=fopen("test","w");
    fputs("你好啊！",aa);
    fclose(aa);

}