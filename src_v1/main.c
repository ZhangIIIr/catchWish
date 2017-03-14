#include "sogar.h"

int main(int argc, char *argv[])
{
//变量定义

//下载网页到本地文件webFile
	downWeb(argc, argv[1]);
	//提取出标题 描述 关键字 并写入一个文件
	//提取出 描述 图片 两大段以供后文使用
	if(0 != getTDK())
	{
		printf("getTDK error!\n");
		exit(0);
	}

//提取出图片地址和图片数量并保存到文件
	//pageParams字段里面,small_picture为主图；extra_photo_urls为附图
	//重新处理picture文件，把所有的small替换成original
	if(0 != disposeUrl())
	{
		printf("disposeUrl error!\n");
		exit(0);
	}
	

//提取出颜色和尺码
	if(0 != sizeColor())
	{
		printf("get size|color error!\n");
		exit(0);
	}
	

//写入标题行
	if(0 != writeTop())
	{
		printf("writeTop error!\n");
		exit(0);
	}

//抓取msrp 价格 邮费
	if(0 != price())
	{
		printf("main: price error!\n");
		exit(0);
	}

//依次写入 颜色 * 尺码 行
	if(0 != writeRest())
	{
		printf("writeRest error!\n");
		exit(0);
	}

//	printf("all done before cp2win\n");

//cp2win
	if(0 != cp2win(argv[1]))
	{
		printf("main: cp error!\n");
		exit(0);
	}

#if 0
//清除tmp文件
	if(0 != system("rm -rf /tmp/webFile /tmp/color /tmp/extraPicNum /tmp/final.haha /tmp/msrp /tmp/pPic /tmp/post /tmp/price /tmp/size /tmp/smulc /tmp/tdk /tmp/urls*"))
	{
		printf("rm tmpFiles error!\n");
		return -1;
	}
#endif
	


	printf("商品表单信息已生成\n请用Excel打开位于您桌面上的final.haha文件\n");
	printf("请仔细检查该表格，如无误请另存为 .xls 或 .xlsx 格式再行编辑\n");
	printf("\n如遇排版错乱或任何格式问题请使用您已知的任何方式联系张三本人\n");
	printf("\n感谢使用本软件，祝您幸福\n");


	return 0;
}
