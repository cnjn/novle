#include<stdio.h>
void inverse_stack(wchar_t *str1,wchar_t *buf)
{
	if (str1 == NULL || buf == NULL)  //递归结束的异常条件
	{
		return;
	}
	if (*str1 == '\0')  //递归结束的正常条件
	{
		return;
	}
	inverse_stack(str1 + 1,buf);
	strncat(buf, str1, 1);
}

