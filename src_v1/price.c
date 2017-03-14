#include "sogar.h"

//msrp localized_retail_price": {"localized_value":
//price localized_price": {"localized_value":
//post localized_shipping": {"localized_value":

int price(void)
{
	char c = '%';
	FILE *p0 = NULL;
	p0 = fopen("/tmp/webFile", "r");
	if(NULL == p0)
	{
		perror("In price.c fopen webFile");
		return -1;
	}
	FILE *pMSRP = NULL;
	FILE *pPrice = NULL;
	FILE *pPost = NULL;

	pMSRP = fopen("/tmp/msrp", "w+");
	if(NULL == pMSRP)
	{
		perror("In price.c fopen msrp");
		return -1;
	}
	pPrice = fopen("/tmp/price", "w+");
	if(NULL == pPrice)
	{
		perror("fopen price");
		return -1;
	}
	pPost = fopen("/tmp/post", "w+");
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

#if 0		//这一段是重定义msrp的
	int price;
	int msrp;
	fseek(pPrice, 0, SEEK_SET);
	fseek(pMSRP, 0, SEEK_SET);
	fscanf(pPrice, "%d", price);
	fscanf(pMSRP, "%d", msrp);
	if()
#endif

	printf("\n\n");

	fclose(p0);
	fclose(pMSRP);
	fclose(pPrice);
	fclose(pPost);
	return 0;
}
