#include "catchWish.h"

//msrp localized_retail_price": {"localized_value":
//price localized_price": {"localized_value":
//post localized_shipping": {"localized_value":

int price(char *id)
{
	char c = '%';
	FILE *p0 = NULL;
	char ptr_webFile[42];
	sprintf(ptr_webFile, "%s/webFile", id);
	p0 = fopen(ptr_webFile, "r");
	if(NULL == p0)
	{
		perror("In price.c fopen webFile");
		return -1;
	}
	FILE *pMSRP = NULL;
	FILE *pPrice = NULL;
	FILE *pPost = NULL;

	char ptr_pMSRP[42];
	sprintf(ptr_pMSRP, "%s/msrp", id);
	pMSRP = fopen(ptr_pMSRP, "w+");
	if(NULL == pMSRP)
	{
		perror("In price.c fopen msrp");
		return -1;
	}
	char ptr_pPrice[42];
	sprintf(ptr_pPrice, "%s/price", id);
	pPrice = fopen(ptr_pPrice, "w+");
	if(NULL == pPrice)
	{
		perror("fopen price");
		return -1;
	}
	char ptr_pPost[42];
	sprintf(ptr_pPost, "%s/post", id);
	pPost = fopen(ptr_pPost, "w+");
	if(NULL == pPost)
	{
		perror("fopen post");
		return -1;
	}

//提取price
	if(search(p0, "localized_price\": {\"localized_value\":") != 0)
	{
		printf("price截取异常\n");
		return -1;
	}
	while(c != '.')
	{
		fread(&c, 1, 1, p0);
		if(c == ' ')
		{
			continue;
		}
		if(c == '.')
		{
			break;
		}
		fwrite(&c, 1, 1, pPrice);
	}
	fseek(p0, -10000, SEEK_CUR);
	printf("price写入完毕\n");

//提取post
	c = '%';
	if(search(p0, "localized_shipping\": {\"localized_value\":") != 0)
	{
		printf("post截取异常\n");
		return -1;
	}
	while(c != '.')
	{
		fread(&c, 1, 1, p0);
		if(c == ' ')
		{
			continue;
		}
		if(c == '.')
		{
			break;
		}
		fwrite(&c, 1, 1, pPost);
	}
	fseek(p0, -10000, SEEK_CUR);
	printf("post写入完毕\n");


//提取msrp
	c = '%';
	if(search(p0, "localized_retail_price\": {\"localized_value\":") != 0)
	{
		printf("MSRP截取异常或此商品没有msrp信息\n");
		return 0;
	}
	while(c != '.')
	{
		fread(&c, 1, 1, p0);
		if(c == ' ')
		{
			continue;
		}
		if(c == '.')
		{
			break;
		}
		fwrite(&c, 1, 1, pMSRP);
	}
	printf("MSRP写入完毕\n");


	printf("\n\n");

	fclose(p0);
	fclose(pMSRP);
	fclose(pPrice);
	fclose(pPost);
	return 0;
}
