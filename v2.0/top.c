#include "catchWish.h"

int writeTop()
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

#if 0
//写入附图段
	fseek(pFinal, -1, SEEK_CUR);			//消除换行错误？这是为什么，我觉得是while fread 的判断问题，流指针指向的问题
	int i = 0;
	int j = 0;
	FILE *pExtraPicNum = NULL;
	pExtraPicNum = fopen("/tmp/extraPicNum", "r");
	if(NULL == pExtraPicNum)
	{
		perror("fopen extraPicNum");
		return -1;
	}
	fscanf(pExtraPicNum, "%d", &i);

	for(j = 1; j <= i; j++)
	{
		fprintf(pFinal, "\t附图%d", j);
	}
	fwrite("\n", 1, 1, pFinal);
//	fwrite("\n", 1, 1, pFinal);
#endif



	fclose(pFinal);
	fclose(pTop);
	return 0;
}
