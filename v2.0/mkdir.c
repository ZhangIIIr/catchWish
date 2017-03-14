#include "catchWish.h"

int mkdir(char *s)
{
	char shellCommand[64];

	sprintf(shellCommand, "mkdir %s", s);
	if(0 != system(shellCommand))
	{
		puts("mkdir failed");
		return -1;
	}

	return 0;
}
