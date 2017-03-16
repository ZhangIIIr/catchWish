#include "catchWish.h"

int disposeUrl(char *id)
{
	int i = 0;
	char c = '%';
	FILE *pPic = NULL;
	FILE *pExtraPicNum = NULL;
	FILE *pUrls = NULL;

	char ptr_pPic[42];
	sprintf(ptr_pPic, "%s/pPic", id);
	pPic = fopen(ptr_pPic, "r");
	if(NULL == pPic)
	{
		perror("fopen pPic");
		return -1;
	}
	char ptr_extraPicNum[42];
	sprintf(ptr_extraPicNum, "%s/extraPicNum", id);
	pExtraPicNum = fopen(ptr_extraPicNum, "w+");
	if(NULL == pExtraPicNum)
	{
		perror("fopen extraPicNum");
		return -1;
	}
	char ptr_urls[42];
	sprintf(ptr_urls, "%s/urls", id);
	pUrls = fopen(ptr_urls, "w+");
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
	char ptr_urls_1[42];
	sprintf(ptr_urls_1, "%s/urls_1", id);
	pUrls_1 = fopen(ptr_urls_1, "w+");
	if(pUrls_1 == NULL)
	{
		perror("fopen urls_1");
		return -1;
	}

	i = 0;
	while(fread(&c, 1, 1, pUrls))
	{
		if(c == '\n')
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
