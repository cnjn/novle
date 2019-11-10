#include<stdio.h>
#include<stdlib.h>
#include<regex.h>
#include<string.h>
#include"strrpc.h"

char *get_content(FILE *request){
    fseek(request,0,SEEK_END);
    int size=ftell(request);
    char *content=malloc(size);
    rewind(request);
    while (!feof(request))
    {  
        char tmp[size];
        fgets(tmp,size,request);
        strcat(content,tmp);
    }
    rewind(request);
    return content;

}

void test(){

        //int ch=2
 	FILE *fp=NULL,*fp2=NULL;
    fp=fopen("tmp2","r+");
	char *source=get_content(fp);
    fclose(fp);
    system("rm tmp3 -f");
    fp=NULL;
    fp=fopen("tmp3","w");
     if (fp==NULL){
       perror("出错了");
       exit(-1);
     }
	//struct Compile src=compile(1,"<div id=\"content\">(.*?)<.div>",source);
	//strrpc(src.child[0],"&nbsp;"," ");
	//strrpc(src.child[0],"<br />","\n");
    fputs("你好啊！",fp);
    fclose(fp);

}
void main()
{
    //int ch=2
    /*
 	FILE *fp=NULL,*fp2=NULL;
    fp=fopen("tmp2","r+");
	char *source=get_content(fp);
    fclose(fp);
    system("rm tmp3 -f");
    fp=NULL;
    fp=fopen("tmp3","w");
     if (fp==NULL){
       perror("出错了");
       exit(-1);
     }
	//struct Compile src=compile(1,"<div id=\"content\">(.*?)<.div>",source);
	//strrpc(src.child[0],"&nbsp;"," ");
	//strrpc(src.child[0],"<br />","\n");
    fputs("你好啊！",fp);
    fclose(fp);
    */

   test();

}