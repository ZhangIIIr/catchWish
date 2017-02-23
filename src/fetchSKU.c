#include "sogar.h"

int sku()
{
	char c = '%';
	FILE *p0 = NULL;
	FILE *pSKU = NULL;
	
	p0 = fopen("/tmp/webFile", "r");
	if(NULL == p0)
	{
		perror("fopen p0");
		exit(0);
	}
	pSKU = fopen("/tmp/sku", "w+");
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
