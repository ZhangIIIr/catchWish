#include "catchWish.h"

int cp2win(char *v)
{
	char shellCommand[128];

	sprintf(shellCommand, "cp /tmp/catchWish/final.haha /mnt/c/Users/Administrator/Desktop/%s.haha", v);
	if(0 != system(shellCommand))
	{
		printf("cp2win error!\n");
		return -1;
	}
	printf("\n\n");
	
	return 0;
}
