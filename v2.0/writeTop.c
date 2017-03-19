#include "catchWish.h"

int writeTop(void)
{
	char c = '%';
	FILE *pFinal = NULL;
	FILE *pTop = NULL;

//写入base段
	pFinal = fopen("/tmp/catchWish/final.haha", "w+");
	if(NULL == pFinal)
	{
		perror("fopen final.haha");
		return -1;
	}
	pTop = fopen("/tmp/topBase", "r");
	if(NULL == pTop)
	{
		perror("fopen topBase");
		return -1;
	}

	while(fread(&c, 1, 1, pTop))
	{
		fwrite(&c,1, 1, pFinal);
	}


	fclose(pFinal);
	fclose(pTop);
	return 0;
}
