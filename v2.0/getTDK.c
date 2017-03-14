#include "catchWish.h"


int getTDK(char *id)
{
	printf("getTDK() begin");

	FILE *p0 = NULL;
	FILE *pTDK = NULL;
	FILE *pPic = NULL;
	char c = '%';
	char ptr_webFile[42];
	sprintf(ptr_webFile, "%s/webFile", id);
	printf("\n\n%s\n\n", ptr_webFile);
	p0 = fopen(ptr_webFile, "r");
	if(NULL == p0)
	{
		perror("fopen p0 eeeee");
		return -1;
	}
	char ptr_tdk[42];
	sprintf(ptr_tdk, "%s/tdk", id);
	pTDK = fopen(ptr_tdk, "w+");
	if(NULL == pTDK)
	{
		perror("fopen pTDK");
		return -1;
	}

//提取标题
	if(search(p0, "<title>Wish | ") != 0)
	{
		printf("商品名称截取异常\n");
		return -1;
	}
	while(c != '<')
	{
		fread(&c, 1, 1, p0);
		if(c == '\t')
		{
			continue;
		}
		if(c == '<')
		{
			fwrite("\t", 1, 1, pTDK);
			break;
		}
		fwrite(&c, 1, 1, pTDK);
	}
	printf("商品名称写入完毕\n");
//提取描述 追加写入TDK文件
	c = '%';
	if(search(p0, "\"description\" : \"") != 0)
	{
		printf("商品描述截取异常\n");
		return -1;
	}
	while(c != '\"')
	{
		fread(&c, 1, 1, p0);
		if(c == '\t')
		{
			continue;
		}
		if(c == '\"')
		{
			fwrite("\t", 1, 1, pTDK);
			break;
		}
		if(c == '\n')
		{
			fwrite("      ", 1, 1, pTDK);
			continue;
		}
		if(c == '\r')
		{
			fwrite(" ", 1, 1, pTDK);
			continue;
		}
		fwrite(&c, 1, 1, pTDK);
	}
	printf("商品描述写入完毕\n");
//提取关键词
	c = '%';
	if(search(p0, "\"keywords\": \"") != 0)
	{
		printf("商品关键词截取异常\n");
		return -1;
	}
	while(c != '\"')
	{
		fread(&c, 1, 1, p0);
		if(c == '\t')
		{
			continue;
		}
		if(c == '\"')
		{
			fwrite("\t", 1, 1, pTDK);
			break;
		}
		fwrite(&c, 1, 1, pTDK);
	}
	printf("商品关键词写入完毕\n");


//提取主图和附图字段并写入pPic文件
	if(0 != fseek(p0, 0, SEEK_SET))
	{
		perror("fseek p0");
		return -1;
	}
	c = '%';
	char ptr_pPic[42];
	sprintf(ptr_pPic, "%s/pPic", id);
	pPic = fopen(ptr_pPic, "w+");
	if(NULL == pPic)
	{
		perror("fopen pPic");
		return -1;
	}
	if(search(p0, "\"small_picture\": \"") != 0)
	{
		printf("主图字段截取异常\n");
		return -1;
	}
	while(c != '\"')
	{
		fread(&c, 1, 1, p0);
		if(c == '\"')
		{
			fwrite("\n", 1, 1, pPic);
			break;
		}
		fwrite(&c, 1, 1, pPic);
	}
	printf("主图链接获取完成\n");
	c = '%';
	if(search(p0, "\"extra_photo_urls\": {") != 0)
	{
		printf("附图字段截取异常\n");
		return -1;
	}
	while(c != '}')
	{
		fread(&c, 1, 1, p0);
		if(c == '}')
		{
			fwrite("\n", 1, 1, pPic);
			break;
		}
		if(c == ',')
		{
			fwrite("\n", 1, 1, pPic);
			continue;
		}
		fwrite(&c, 1, 1, pPic);
	}
	printf("附图链接获取完成\n");
	

	fclose(p0);
	fclose(pTDK);
	fclose(pPic);

	printf("getTDK() end");
	return 0;
}
