#ifndef _SOGAR_H_
#define _SOGAR_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>


int single(char *id);
int mkdir(char *s);
//int downWeb(char *id);
void downWeb(char *id);
int getTDK(char *id);
int search(void *fp, char *s);
int sku(char *id);
int sizeColor(char *id);
int disposeUrl(char *id);
int writeTop(void);
int writeRest(char *id);
int cp2win(char *v);
int price(char *id);

//char dir_id(char *id, char *s);



#endif
