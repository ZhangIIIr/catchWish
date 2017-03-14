#include "catchWish.h"

int sku(char *id)
{
	char c = '%';
	FILE *p0 = NULL;
	FILE *pSKU = NULL;
	
	char ptr_webFile[42];
	sprintf(ptr_webFile, "%s/", id);
	p0 = fopen(ptr_webFile, "r");
	if(NULL == p0)
	{
		perror("fopen p0");
		exit(0);
	}
	char ptr_pSKU[42];
	sprintf(ptr_pSKU, "%s/sku", id);
	pSKU = fopen(ptr_pSKU, "w+");
	if(NULL == pSKU)
	{
		perror("fopen pSKU");
		exit(0);
	}

	while(fread(&c, 1, 1, p0))
	{
		if(search(p0, "\"manufacturer_id\": \"") == 0)
		{
			c = '%';
			while(c != '\"')
			{
				fread(&c, 1, 1, p0);
				if(c == '\"')
				{
					fwrite("\n", 1, 1, pSKU);
					break;
				}
				fwrite(&c, 1, 1, pSKU);
			}
		}
	}

	
	fclose(p0);
	fclose(pSKU);

	return 0;
}
