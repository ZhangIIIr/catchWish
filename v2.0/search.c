#include "catchWish.h"

//用于定位起始截取点
int search(void *fp, char *s)
{
	int i = 0;
	int j = 0;
	int k = 1;
	char c = '%';
	for(i = 0; *(s+i) != '\0'; i++);
	j = i;

	while(fread(&c, 1, 1, fp))
	{
//		if(c == *s || c == *s-32)			//不区分大小写
		if(c == *s)
		{
			while(i-- != 1)
			{
				fread(&c, 1, 1, fp);
//				if(c == *(s+(k++)) || c == *(s+k-1)-32)		//不区分大小写
				if(c == *(s+(k++)))
				{
					if(i == 1)
					{
						//printf("找到了,在第%ld个字符处\n", ftell(fp)-(j-1));
						//printf("当前流指针在 %ld 处,当前字符为 \"%c\"\n", ftell(fp), c);
						return 0;
					}
					continue;
				}
				else
				{
					i = j;
					k = 1;
					break;
				}
			}
		}
		
	}
//	fseek(fp, 0, SEEK_SET);
	return -1;
}



