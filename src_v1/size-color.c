#include "sogar.h"

int sizeColor()
{
	char c = '%';
	FILE *p0 = NULL;
	FILE *pSize = NULL;
	FILE *pColor = NULL;
	
	p0 = fopen("/tmp/webFile", "r");
	if(NULL == p0)
	{
		perror("fopen p0");
		return -1;
	}
	pSize = fopen("/tmp/size", "w+");
	if(NULL == pSize)
	{
		perror("fopen pSize");
		return -1;
	}
	pColor = fopen("/tmp/color", "w+");
	if(NULL == pColor)
	{
		perror("fopen pColor");
		return -1;
	}

	while(fread(&c, 1, 1, p0))
	{
		if(search(p0, "\"size\": \"") == 0)
		{
			c = '%';
			while(c != '\"')
			{
				fread(&c, 1, 1, p0);
				if(c == '\"')
				{
					fwrite("\n", 1, 1, pSize);
					break;
				}
				fwrite(&c, 1, 1, pSize);
			}
		}
	}
	if(0 == ftell(pSize))
	{
		printf("这个商品并没有size信息，大概是均码。我猜的昂\n");
	}
	c = '%';
	fseek(p0, 0, SEEK_SET);
	while(fread(&c, 1, 1, p0))
	{
		if(search(p0, "\"color\": \"") == 0)
		{
			c = '%';
			while(c != '\"')
			{
				fread(&c, 1, 1, p0);
				if(c == '\"')
				{
					fwrite("\n", 1, 1, pColor);
					break;
				}
				fwrite(&c, 1, 1, pColor);
			}
		}
	}
	if(0 == ftell(pColor))
	{
		printf("这个商品并没有color信息，可能是单色\n");
	}
//	if(0 == ftell(pColor) && 0 == ftell())

	printf("颜色和尺码提取完成\n");

	
	fclose(p0);
	fclose(pSize);
	fclose(pColor);

	return 0;
}
