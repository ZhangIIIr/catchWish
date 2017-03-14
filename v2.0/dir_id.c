#include "catchWish.h"

char dir_id(char *id, char *s)
{
	char dir_s[42];
	sprintf(dir_s, "%s/%s", id, s);

	return dir_s;
}
