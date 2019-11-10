#include <stdio.h>
#include <string.h>
 
 
/* 功  能：将str字符串中的oldstr字符串替换为newstr字符串
 * 参  数：str：操作目标 oldstr：被替换者 newstr：替换者
 * 返回值：返回替换之后的字符串
 * 版  本： V0.2
 */
char *strrpc(char *str,char *oldstr,char *newstr){
    char bstr[strlen(str)];//转换缓冲区
    memset(bstr,0,sizeof(bstr));
 
    for(int i = 0;i < strlen(str);i++){
        if(!strncmp(str+i,oldstr,strlen(oldstr))){//查找目标字符串
            strcat(bstr,newstr);
            i += strlen(oldstr) - 1;
        }else{
        	strncat(bstr,str + i,1);//保存一字节进缓冲区
	    }
    }
 
    strcpy(str,bstr);
    return str;
}
 
int main(void)
{
	char str[] = "Hello,中国中国!aaa\n"; 
	strrpc(str,"中国","世界");
	printf("%s",str);
	strrpc(str,"Hello","你好");
	printf("%s",str);
	strrpc(str,"你好,世界","Hello,world");
	printf("%s",str);
	return 0;
}

/*
————————————————

版权声明：本文为CSDN博主「出奇」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。

原文链接：https://blog.csdn.net/qq_41673920/article/details/81390972
*/
