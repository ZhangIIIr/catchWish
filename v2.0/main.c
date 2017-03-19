#include "catchWish.h"


#define THREAD_NUMMBER		13
#define WORK_DERECTORY		"/tmp/catchWish"

static pthread_mutex_t mut1 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mut2 = PTHREAD_MUTEX_INITIALIZER;

static void *ptr_deal_ID(void *p);

int cat(char *a, char *b)
{
	char shellCommand[32];

	sprintf(shellCommand, "cat %s >> %s", b, a);

	if(0 != system(shellCommand))
	{
		return -1;
	}
	puts("haha");

	return 0;
}

int rm_work_dir()
{
	char *s = "rm -rf /tmp/catchWish";
	if(0 != system(s))
	{
		return -1;
	}
	return 0;
}


int main(void)
{
	pthread_t tid[THREAD_NUMMBER];
	FILE *fp_IDs = NULL;
	int i;
	int err;

	if(0 != rm_work_dir())
	{
		puts("rm 失败");
		exit(1);
	}
	mkdir(WORK_DERECTORY);

	//写top
	if(0 != writeTop())
	{
		printf("writeTop error!\n");
		exit(0);
	}
	

	fp_IDs = fopen("/tmp/IDs.txt", "r");
	if(NULL == fp_IDs)
	{
		puts("fopen() IDs.txt failed");
		exit(1);
	}

	for(i = 0; i < THREAD_NUMMBER; i++)
	{
		err = pthread_create(tid+i, NULL, ptr_deal_ID, fp_IDs);
		if(err)
		{
			puts("pthread_create() failed");
			exit(2);
		}

	}

	for(i = 0; i < THREAD_NUMMBER; i++)
	{
		pthread_join(tid[i], NULL);
	}

	pthread_mutex_destroy(&mut1);
	pthread_mutex_destroy(&mut2);

	fclose(fp_IDs);

	exit(0);
}

static void *ptr_deal_ID(void *p)
{
	FILE *fp_final = NULL;
	fp_final = fopen("/tmp/catchWish/final.haha", "a");
	if(NULL == fp_final)
	{
		puts("fopen() final.haha failed");
		exit(2);
	}

	char ID[32];
	char id[32];
	char c1 = '0';
	int j = 0;

	pthread_mutex_lock(&mut1);
	while(1)
	{
		fread(&c1, 1, 1, p);
		if((c1 == '\n' || c1 == '\0' || c1 == '\r') && c1 != EOF)
		{
			fseek(p, SEEK_CUR, 1);							//此处大妙，没这句的话就只有一半的线程可以得到ID
			break;
		}
		sprintf(&ID[j++], "%c", c1);
	}
	sprintf(id, "%s", ID);
	pthread_mutex_unlock(&mut1);

	
	if(0 != chdir("/tmp/catchWish"))
	{
		puts("change dir to catchWish failed");
		exit(3);
	}
	mkdir(id);

	//下载网页
	//为何把此段代码用函数调用实现，在这里调用函数，会出现段错误呢？
	char wgetWeb[64];
	sprintf(wgetWeb, "wget -q -O %s/webFile https://www.wish.com/c/%s", id, id);
	if(0 != system(wgetWeb))
	{
		puts("下载网页失败");
		pthread_exit(NULL);
	}
	sprintf(id, "%s", ID);


	if(0 != single(id))
	{
		puts("single() error");
		pthread_exit(NULL);
	}
	sprintf(id, "%s", ID);

	
	//调试代码
	//printf("%s %d %s: fopen id.haha failed\n", __FILE__, __LINE__, __func__);


	char id_pwd[64];
	sprintf(id_pwd, "/tmp/catchWish/%s/id.haha", id);
	printf("\n%s\n\n", id_pwd);

	pthread_mutex_lock(&mut2);
	//if(0 != cat("/tmp/catchWish/final.haha", id_pwd))			//会段错误
	char shell_cat[32];

	sprintf(shell_cat, "cat %s >> /tmp/catchWish/final.haha", id_pwd);
	if(0 != system(shell_cat))
	{
		puts("cat failed");
	}
	pthread_mutex_unlock(&mut2);

	fclose(fp_final);
	pthread_exit(p);
}

