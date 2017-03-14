#include "catchWish.h"


#if 0									//这三个函数可能有bug
int whetherEmpty(void *fp)
{
	fseek(fp, 0, SEEK_END);
	if(0 == ftell(fp))
		return 1;
	else
	{
		fseek(fp, 0, SEEK_SET);
		return 0;
	}
}

int lineLenth(void * fp, char *s)
{
	int i = 0;
	if(1 == whetherEmpty(fp))
	{
		return 0;
	}
	else
	{
		for(; s[i] != '\n'; i++)	
		return i;
	}
}
#endif

int lineNum(void *fp)
{
	int i = 0;
	char c = '%';
	while(1 == fscanf(fp, "%c", &c))
	{
		if(c == '\n')
		{
			i++;	
		}
	}
	fseek(fp, 0, SEEK_SET);
	if(i == 0)
		return 1;
	else
		return i;
}

int sMulC(int PSKU, char *id)
{
	FILE *pSMulC = NULL;
	FILE *pSize = NULL;
	FILE *pColor = NULL;
	char ptr_pSMulC[42];
	sprintf(ptr_pSMulC, "%s/smulc", id);
	pSMulC = fopen(ptr_pSMulC, "w+");
	if(NULL == pSMulC)
	{
		perror("fopen smulc");
		return -1;
	}
	char ptr_pSize[42];
	sprintf(ptr_pSize, "%s/size", id);
	pSize = fopen(ptr_pSize, "r");
	if(NULL == pSize)
	{
		perror("fopen size");
		return -1;
	}
	char ptr_pColor[42];
	sprintf(ptr_pColor, "%s/color", id);
	pColor = fopen(ptr_pColor, "r");
	if(NULL == pColor)
	{
		perror("fopen color");
		return -1;
	}
	
	int i = 0;
	int lineS = lineNum(pSize);
	int lineC = lineNum(pColor);
	int line = (lineC >= lineS) ? lineC : lineS;
	char size[32];
	char color[32];
	for(i = 0; i < line; i++)
	{
		fprintf(pSMulC, "%d-", PSKU);
		if(NULL == fgets(size, 32, pSize))
		{
			size[0] = '\0';
			fseek(pSMulC, 1, SEEK_CUR);
		}
//		size[lineLenth(pSize, size) + 1] = '-';		//为什么会导致一直在第一行？？？可能是函数有bug
		fprintf(pSMulC, "%s", size);
		fseek(pSMulC, -1, SEEK_CUR);
		fprintf(pSMulC, "-");
//		fscanf(pColor, "%s", color);				//遇到空格就会停下，
		if(NULL == fgets(color, 32, pColor))
		{
			color[0] = '\0';
			fseek(pSMulC, 1, SEEK_CUR);
		}
		fprintf(pSMulC, "%s", color);
		fseek(pSMulC, -1, SEEK_CUR);
		fprintf(pSMulC, "\t");
		
	}
	
	fclose(pSMulC);
	fclose(pSize);
	fclose(pColor);

//	printf("size color 信息合并完成\n");
	return line;
}

//四舍五入函数
int rounding(int n)
{
	if((n%6)/3 == 0)
		return n/6;
	else
		return (n/6)+1;
}
//float版的四舍五入函数
int frounding(int n)
{
	if(n == 1 || n == 2 || n == 3)
	{
		return 1;
	}
	if(((float)n*5/33 - n*5/33) >= 0.45)
		return n*5/33 + 1;
	else
		return n*5/33;
}

int writeRest(char *id)
{
	int i = 0;
	int lineRest = 0;
	//char SKU[32];
	char c = '%';
	FILE *pFinal = NULL;
	char ptr_pFinal[42];
	sprintf(ptr_pFinal, "%s/id.haha", id);
	pFinal = fopen(ptr_pFinal, "a+");
	if(NULL == pFinal)
	{
		printf("%s %d %s: fopen id.haha failed\n", __FILE__, __LINE__, __func__);
		perror("fopen id.haha");
		return -1;
	}
	FILE *pTDK = NULL;
	char ptr_pTDK[42];
	sprintf(ptr_pTDK, "%s/tdk", id);
	pTDK = fopen(ptr_pTDK, "r");
	if(NULL == pTDK)
	{
		perror("fopen tdk");
		return -1;
	}
	FILE *pSize = NULL;
	FILE *pColor = NULL;
	char ptr_pSize[42];
	sprintf(ptr_pSize, "%s/size", id);
	pSize = fopen(ptr_pSize, "r");
	if(NULL == pSize)
	{
		perror("fopen size");
		return -1;
	}
	char ptr_pColor[42];
	sprintf(ptr_pColor, "%s/color", id);
	pColor = fopen(ptr_pColor, "r");
	if(NULL == pColor)
	{
		perror("fopen color");
		return -1;
	}
	FILE *pUrls_1 = NULL;
	char ptr_pUrls[42];
	sprintf(ptr_pUrls, "%s/urls_1", id);
	pUrls_1 = fopen(ptr_pUrls, "r");
	if(NULL == pUrls_1)
	{
		perror("fopen urls_1");
		return -1;
	}
	
	FILE *pMSRP = NULL;
	FILE *pPrice = NULL;
	FILE *pPost = NULL;
	char ptr_pMSRP[42];
	sprintf(ptr_pMSRP, "%s/msrp", id);
	pMSRP = fopen(ptr_pMSRP, "r");
	if(NULL == pMSRP)
	{
		perror("fopen msrp");
		return -1;
	}
	char ptr_pPrice[42];
	sprintf(ptr_pPrice, "%s/price", id);
	pPrice = fopen(ptr_pPrice, "r");
	if(NULL == pPrice)
	{
		perror("fopen price");
		return -1;
	}
	char ptr_pPost[42];
	sprintf(ptr_pPost, "%s/post", id);
	pPost = fopen(ptr_pPost, "r");
	if(NULL == pPost)
	{
		perror("fopen post");
		return -1;
	}
	int msrp = 0;
	int price = 0;
	int post = 0;
	fscanf(pMSRP, "%d", &msrp);
	msrp = frounding(msrp);
	fscanf(pPrice, "%d", &price);
	price = frounding(price);
	fscanf(pPost, "%d", &post);
	post = frounding(post);

	//char *ParentSKU = "jinlin";
	//用当前系统时间值来替换jinlin，做到数值唯一
	int ParentSKU = (int)time(NULL);
	int storage = 200;
	int minDay = 5;
	int maxDay = 20;
	//printf("请输入ParentSKU:\n");
	//scanf("%s", ParentSKU);
	lineRest = sMulC(ParentSKU, id);
	FILE *pSMulC = NULL;
	char ptr_pSMulC[42];
	sprintf(ptr_pSMulC, "%s/smulc", id);
	pSMulC = fopen(ptr_pSMulC, "r");
	if(NULL == pSMulC)
	{
		perror("fopen smulc");
		return -1;
	}


	for(i = 0; i < lineRest; i++)
	{
		//写入PSKU
		fprintf(pFinal, "%d\t", ParentSKU);
		//写入SKU
#if 0							//幽灵般的换行符
		fgets(SKU, 32, pSMulC);
		fprintf(pFinal, "%s", SKU);
		//fseek(pFinal, 0, SEEK_END);
		fprintf(pFinal, "\t");
#endif
		c = '%';
		while(fread(&c, 1, 1, pSMulC))
		{
			if(c == '\t')
			{
				fwrite(&c, 1, 1, pFinal);	
				break;
			}
			fwrite(&c, 1, 1, pFinal);
		}
		//写入tdk
		c = '%';
		while(fread(&c, 1, 1, pTDK))
		{
			fwrite(&c, 1, 1, pFinal);
		}
		fseek(pTDK, 0, SEEK_SET);
		//空 品牌 UPC LandingPageUrl
		fprintf(pFinal, "\t\t\t");
		//写入MSRP
		fprintf(pFinal, "%d\t", msrp);
		//写入颜色
		c = '%';
		while(fread(&c, 1, 1, pColor))
		{
			if(c == '\n')
			{
				break;
			}
			fwrite(&c, 1, 1, pFinal);
		}
		fwrite("\t", 1, 1, pFinal);	
		//写入尺寸
		c = '%';
		while(fread(&c, 1, 1, pSize))
		{
			if(c == '\n')
			{
				break;
			}
			fwrite(&c, 1, 1, pFinal);
		}
		fwrite("\t", 1, 1, pFinal);	
		//空 来源Url
		fprintf(pFinal, "\t");
		//价格
		fprintf(pFinal, "%d\t", price);
		//运费
		fprintf(pFinal, "%d\t", post);
		//数量 最小/大送达时间
		fprintf(pFinal, "%d\t%d\t%d\t", storage, minDay, maxDay);
		//写入图片url
		c = '%';
		while(fread(&c, 1, 1, pUrls_1))
		{
			if(c == '\n')
			{
				fwrite("\t", 1, 1, pFinal);
				continue;
			}
			fwrite(&c, 1, 1, pFinal);
		}
		fprintf(pFinal, "\n");
		fseek(pUrls_1, 0, SEEK_SET);
	}
		


	fclose(pFinal);
	fclose(pSMulC);
	fclose(pTDK);
	fclose(pSize);
	fclose(pColor);
	fclose(pUrls_1);
	fclose(pMSRP);
	fclose(pPrice);
	fclose(pPost);
	return 0;
}
