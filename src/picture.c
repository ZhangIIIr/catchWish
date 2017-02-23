#include "sogar.h"

int disposeUrl()
{
	int i = 0;
	char c = '%';
	FILE *pPic = NULL;
	FILE *pExtraPicNum = NULL;
	FILE *pUrls = NULL;

	pPic = fopen("/tmp/pPic", "r");
	if(NULL == pPic)
	{
		perror("fopen pPic");
		return -1;
	}
	pExtraPicNum = fopen("/tmp/extraPicNum", "w+");
	if(NULL == pExtraPicNum)
	{
		perror("fopen extraPicNum");
		return -1;
	}
	pUrls = fopen("/tmp/urls", "w+");
	if(NULL == pUrls)
	{
		perror("fopen urls");
		return -1;
	}

//把所有的非url内容去掉
	while(fread(&c, 1, 1, pPic))
	{
		//去掉所有的逗号和空格
		if(c == '\"' || c == ' ')
			continue;
		//把所有的small换成original
		i = (int)ftell(pPic);	
		if(search(pPic, "small") == 0 && i == (int)ftell(pPic) - 5)
		{
			fwrite(&c, 1, 1, pUrls);
			fread(&c, 1, 1, pPic);
			fprintf(pUrls, "original");
		}
		else
		{
			fseek(pPic, i - (int)ftell(pPic), SEEK_CUR);
		}
		fwrite(&c, 1, 1, pUrls);
	}


	fseek(pUrls, 0, SEEK_SET);
	FILE *pUrls_1 = NULL;
	pUrls_1 = fopen("/tmp/urls_1", "w+");
	if(pUrls_1 == NULL)
	{
		perror("fopen urls_1");
		return -1;
	}
	i = 0;
#if 0
	while(fread(&c, 1, 1, pUrls))						//这样写为啥会死循环？？？！！！
	{
		if(c == '\n')
		{
			fwrite("\n", 1, 1, pUrls_1);
			while(c != 'h')
			{
				fread(&c, 1, 1, pUrls);
				printf("%d	%c\n", i, c);
			}
		}
		fwrite(&c, 1, 1, pUrls_1);
	}
#else
	while(fread(&c, 1, 1, pUrls))
	{
		if(c == '\n')									//这个if为什么会多进入一次???!!!
		{	
			fwrite("\n", 1, 1, pUrls_1);
			while(fread(&c, 1, 1, pUrls))
			{
				if(c == 'h')
				{
					break;
				}
			}
		}
		fwrite(&c, 1, 1, pUrls_1);
	}
#endif







	fseek(pUrls, 0, SEEK_SET);
	i = 0;
	while(fread(&c, 1, 1, pUrls))
	{
		if(c == '\n')
			i++;
	}
	fprintf(pExtraPicNum, "%d", i - 1);


	fclose(pPic);
	fclose(pExtraPicNum);
	fclose(pUrls);
	fclose(pUrls_1);

	return 0;
}
