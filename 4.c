#include<stdio.h>
#include<stdlib.h>
#include<regex.h>
#include<string.h>
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
    regcomp(&preg,pattern,REG_EXTENDED);
    regmatch_t matched[child_num+1];
    int vv=regexec(&preg,content,child_num+1,matched,REG_NOTBOL);
    if(vv!=0){
	    char tmp[500];
	regerror(vv,&preg,tmp,500);
	puts(tmp);
	exit(-1);
    }
    struct Compile res;
    res.body=malloc(strlen(content)*child_num);
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
    

char *get_content(FILE *request){
    fseek(request,0,SEEK_END);
    char *content=malloc(ftell(request));
    rewind(request);
    while (!feof(request))
    {  
        char tmp[50000];
        fgets(tmp,50000,request);
        strcat(content,tmp);
    }
    rewind(request);
    return content;

}

int main(){
    //system("/usr/bin/curl https://www.xbiquge6.com/9_9933/ >tmp");
    FILE *request=fopen("./tmp","r");
    char *content=get_content(request);
    fclose(request);
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
    printf("请输入章节序号(默认为0)：");
    int ch=0;
    scanf("%d",&ch);
    if (ch>6 ||ch<0){
    	puts("错误的输入！");
	exit(EXIT_FAILURE);
    }
    char command[200]="/usr/bin/curl https://www.xbiquge6.com";
    strcat(command,chapters[ch].url);
    strcat(command," >tmp2");
    puts(command);
    return 0;
}
