#include<stdio.h>
#include<stdlib.h>
#include<regex.h>
#include<string.h>

struct Chapters{
    /* data */
    char name[20];
    char url[100];
} chapters[7];

char *get_content(FILE *request){
    fseek(request,0,SEEK_END);
    char *content=malloc(ftell(request));
    rewind(request);
    while (!feof(request))
    {  
        char tmp[2000];
        fgets(tmp,2000,request);
        strcat(content,tmp);
    }
    return content;

}

int main(){
    //system("/usr/bin/curl https://www.biquge18.com/book/158683/  >tmp");
    FILE *request=fopen("tmp","r");
    char *content=get_content(request);
    fclose(request);
    //puts(content);
    regex_t latest_chapter_name;
    regex_t latest_chapter_url;
    regex_t recent_cahpters;
    regcomp(&latest_chapter_name,"latest_chapter_name\" content=\".*?\"/>",REG_STARTEND);
    regcomp(&latest_chapter_url,"latest_chapter_url\" content=\".*?\"/>",REG_EXTENDED);
    regcomp(&recent_cahpters,"<dd><a href=\".+?\" target=\"_blank\" title=\".+?\">.+?</a></dd>",REG_EXTENDED);
    regmatch_t matched[6];
    //regexec(&latest_chapter_name,content,1,matched,REG_NOTBOL);
    //regexec(&latest_chapter_url,content,1,matched,REG_NOTBOL);
    regexec(&recent_cahpters,content,6,matched,REG_NOTBOL);

    return 0;
}