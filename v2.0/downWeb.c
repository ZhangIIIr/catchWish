#include "catchWish.h"


void downWeb(char *id)
{
	char shellCommand[64];

	//sprintf(shellCommand, "wget -q -O %s/webFile https://www.wish.com/c/%s", id, id);
	sprintf(shellCommand, "wget -O %s/webFile https://www.wish.com/c/%s", id, id);
	if(0 != system(shellCommand))
	{
		printf("system() failed\n");
	}

	printf("\nbefore downWeb()return: 网页下载完成\n");

}

