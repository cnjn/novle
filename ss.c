#include<stdio.h>

void write_text(char path[],char *text){
    FILE *fp=fopen(path,"w+");
    fputs(text,fp);
    fclose(fp);
}
int main(){
	write_text("tmp3","niahoaa!");
}
	

