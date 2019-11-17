#include<stdio.h>
#include<stdlib.h>
#include<regex.h>
#include<string.h>
#include"strrpc.h"
#define MAX 1000000
struct Chapters{
    char name[100];
    char url[100];
} chapters[7];

struct Compile{
	char *body;
	size_t size;
	int child_num;
	char **child;
	regoff_t rm_eo;
};
 
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

struct Compile compile(int child_num,char *pattern,char *content){
    regex_t preg;
    regcomp(&preg,pattern,REG_EXTENDED|REG_NEWLINE);
    regmatch_t matched[child_num+1];
    int vv=regexec(&preg,content,child_num+1,matched,REG_NOTBOL);
    if(vv!=0){
	    char tmp[500];
	regerror(vv,&preg,tmp,500);
	puts(tmp);
	exit(-1);
    }
    struct Compile res;
    res.body=malloc(MAX);
    res.child=(char **)calloc(1,sizeof(char *));
    res.size=0;
    res.child_num=0;
    char *pos=res.body;
    for (int i=0;i<=child_num;i++){
    	int len=matched[i].rm_eo-matched[i].rm_so;
	char *ptr=&content[matched[i].rm_so];
	strncpy(pos,ptr,len);
	res.size+=(len+1);
	pos[len]='\0';
	res.child_num=i;
	if(i>0){
		res.child[i-1]=pos;
	}
	pos+=(len+1);
    }
    res.rm_eo=matched[0].rm_eo;
    return res;
}

char *read_text(char *path){
    FILE *fp;
    char buff[MAX],*res=calloc(1,MAX);
    if((fp=fopen(path,"r"))==NULL){
    	puts("读取文件失败！");
	exit(-1);
    }
    while(!feof(fp)){
    	fgets(buff,MAX,fp);
	strcat(res,buff);
    }
    fclose(fp);
    return res;
}

int write_text(char path[],char *text){
    FILE *fp;
    if((fp=fopen(path,"w"))==NULL){
    	puts("打开文件失败！");
	exit(-1);
    }
    int ret=fputs(text,fp);
    fclose(fp);
    return ret;
}

char *get_novel(int ch){
    char *source=read_text("./tmp2");
    struct Compile src=compile(1,"<div id=\"content\">(.*?)<.div>",source);
    strrpc(src.child[0],"&nbsp;"," ");
    strrpc(src.child[0],"<br />","\n");
    char *res=malloc(1000000);
    strcpy(res,chapters[ch].name);
    strcat(res,"\n\n");
    strcat(res,src.child[0]);
    return res;
}

void read_novel(int ch){
    char command[200]="/usr/bin/wget -O tmp2  https://www.xbiquge6.com";
    strcat(command,chapters[ch].url);
    system(command);
    char *aa=get_novel(ch);
    write_text("tmp3",aa);
    system("cat tmp3|less");
    int isexist=-1;
    if(ch>1){printf("	(0)、下一章");isexist=0;}
    puts("	(1)、上一章	(2)、退出");
    printf("阅读完毕，请选择下一步操作：");
    int s=2;
    LBA1: scanf("%d",&s);
	  switch(s){
	  	case 0:if(isexist==0) read_novel(ch-1);
		case 1:read_novel(ch+1);//这里都不需break
		case 2:exit(EXIT_SUCCESS);
		default:printf("输入错误！请选择下一步操作：");
			goto LBA1;
	  }
}

int main(){
    system("/usr/bin/wget -O tmp https://www.xbiquge6.com/9_9933/");
    //system("/usr/bin/wget -O tmp https://www.xbiquge6.com/20_20331/");
    char *content=read_text("./tmp");
    //获取最新章节
    struct Compile latest=compile(2,"最新章节：<a href=\"(.*)\" target=\"_blank\">(.*)</a></p>",content);
    strcpy(chapters[0].name,latest.child[1]);
    strcpy(chapters[0].url,latest.child[0]);
    //获取最近章节
    char *content_inverse=inverse(content);
    for (int i=1;i<=6;i++){
	struct Compile recent=compile(2,">dd/<>a/<(.{0,50})>\"(.{0,50})\"=ferh a<>dd<",content_inverse);
	strcpy(chapters[i].name,inverse(recent.child[0]));
	strcpy(chapters[i].url,inverse(recent.child[1]));
	content_inverse+=recent.rm_eo;
    }
    puts("以下是最新章节：");
    printf("	(0)、%s\n",chapters[0].name);
    puts("以下是最近章节：");
    for(int i=1;i<=6;i++){
    	printf("	(%d)、%s",i,chapters[i].name);
	if(i%2==0){
		putchar('\n');
	}
    }
    strrpc(chapters[1].url,"\" class=\"empty"," ");
    printf("请输入章节序号(默认为0)：");
    int ch=0;
    scanf("%d",&ch);
    if (ch>6 ||ch<0){
    	puts("错误的输入！");
	exit(EXIT_FAILURE);
    }

    read_novel(ch);
    return 0;
}
