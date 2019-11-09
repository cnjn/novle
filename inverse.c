#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char *inverse(char *str){
	char *res=malloc(strlen(str)+1);
	int len=strlen("啊"),i=0,j=strlen(str)-1;
	while(str[i]!='\0'){
		if(str[i]>0x7F){
			strncpy(&res[j-len+1],&str[i],len);
			i+=len;
			j-=len;
	
		}else{
			strncpy(&res[j],&str[i],1);
			i++;
			j--;
		}
	}
	res[strlen(str)]='\0';
	return res;
}
int main(){
	/*
	char str[1000];
	printf("请输入文本：");
	scanf("%s",str);
	puts(inverse(str));
	*/
	puts(inverse("你好啊！"));
	return 0;
}
