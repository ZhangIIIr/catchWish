#include "catchWish.h"

int single(char *id)
{
	char id_bak[32];
	sprintf(id_bak, "%s", id);

	printf("single() begin\n");
					
#if 0
//下载网页到本地文件webFile
	if(0 != downWeb(id))
	{
		puts("网页下载失败");
		return -1;
	}
	printf("\n网页下载完成\n");
#endif

//提取出标题 描述 关键字 并写入一个文件
//提取出 描述 图片 两大段以供后文使用
	if(0 != getTDK(id))
	{
		puts("getTDK error!");
		exit(0);
	}

//提取出图片地址和图片数量并保存到文件
//pageParams字段里面,small_picture为主图；extra_photo_urls为附图
//重新处理picture文件，把所有的small替换成original
	sprintf(id, "%s", id_bak);
	if(0 != disposeUrl(id))
	{
		printf("\ndisposeUrl error!\n");
		exit(0);
	}
	

//提取出颜色和尺码
	sprintf(id, "%s", id_bak);
	if(0 != sizeColor(id))
	{
		printf("\nget size|color error!\n");
		exit(0);
	}
	

#if 0
//写入标题行
	if(0 != writeTop())
	{
		printf("writeTop error!\n");
		exit(0);
	}
#endif



//抓取msrp 价格 邮费
	sprintf(id, "%s", id_bak);
	if(0 != price(id))
	{
		printf("\nmain: price error!\n");
		exit(0);
	}

//依次写入 颜色 * 尺码 行
	sprintf(id, "%s", id_bak);
	if(0 != writeRest(id))
	{
		printf("\nwriteRest error!\n");
		exit(0);
	}

#if 0
//	printf("all done before cp2win\n");

//cp2win
	if(0 != cp2win(argv[1]))
	{
		printf("main: cp error!\n");
		exit(0);
	}

//清除tmp文件
	if(0 != system("rm -rf /tmp/webFile /tmp/color /tmp/extraPicNum /tmp/final.haha /tmp/msrp /tmp/pPic /tmp/post /tmp/price /tmp/size /tmp/smulc /tmp/tdk /tmp/urls*"))
	{
		printf("rm tmpFiles error!\n");
		return -1;
	}
#endif
	

#if 0
	printf("商品表单信息已生成\n请用Excel打开位于您桌面上的final.haha文件\n");
	printf("请仔细检查该表格，如无误请另存为 .xls 或 .xlsx 格式再行编辑\n");
	printf("\n如遇排版错乱或任何格式问题请使用您已知的任何方式联系张三本人\n");
	printf("\n感谢使用本软件，祝您幸福\n");
#endif

	printf("\nsingle() end\n");
	puts("one single finished\n\n");

	return 0;
}
