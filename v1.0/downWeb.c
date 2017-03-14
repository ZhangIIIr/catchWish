#include "sogar.h"


void downWeb(int c, char *v)
{
	char shellCommand[64];
	if(c != 2)
	{
		printf("\n你并没有输入任何商品ID\n");
		printf("用法：程序名+商品ID\n\n");
		exit(0);
	}

	sprintf(shellCommand, "wget -q -O /tmp/webFile https://www.wish.com/c/%s", v);
	printf("正在下载网页\n");
	printf("... ...\n");
	if(0 != system(shellCommand))
	{
		printf("网页文件下载失败\n");
		exit(0);
	}
	printf("网页下载完成\n\n");
}




int getTDK()
{
	FILE *p0 = NULL;
	FILE *pTDK = NULL;
	//FILE *pDsc = NULL;
	FILE *pPic = NULL;
	char c = '%';
	p0 = fopen("/tmp/webFile", "r");
	if(NULL == p0)
	{
		perror("fopen p0");
		exit(0);
	}
	pTDK = fopen("/tmp/tdk", "w+");
	if(NULL == pTDK)
	{
		perror("fopen pTDK");
		exit(0);
	}

//提取标题
//	if(search(p0, "<title>Wish | ") != 0 && search(p0, "<title>Wish - ") != 0)
	if(search(p0, "<title>Wish | ") != 0)
	{
		printf("商品名称截取异常\n");
		exit(0);
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
		exit(0);
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
		exit(0);
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



#if 0
//提取描述写入单独的文件(带换行)
	pDsc = fopen("tmp/pDsc", "w+");
	if(NULL == pDsc)
	{
		perror("fopen pDsc");
		exit(0);
	}
	if(0 != fseek(p0, 0, SEEK_SET))
	{
		perror("fseek p0");
		exit(0);
	}
	c = '%';
	if(search(p0, "\"description\" : \"") != 0)
	{
		printf("商品描述截取异常\n");
		exit(0);
	}
	while(c != '\"')
	{
		fread(&c, 1, 1, p0);
		if(c == '\"')
		{
			fwrite("\t", 1, 1, pDsc);
			break;
		}
		fwrite(&c, 1, 1, pDsc);
	}
	printf("产品描述(带换行)写入pDes完毕\n");
#endif

//提取主图和附图字段并写入pPic文件
	if(0 != fseek(p0, 0, SEEK_SET))
	{
		perror("fseek p0");
		exit(0);
	}
	c = '%';
	pPic = fopen("/tmp/pPic", "w+");
	if(NULL == pPic)
	{
		perror("fopen pPic");
		exit(0);
	}
	if(search(p0, "\"small_picture\": \"") != 0)
	{
		printf("主图字段截取异常\n");
		exit(0);
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
		exit(0);
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
//	fclose(pDsc);
	fclose(pPic);

	return 0;
}



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










