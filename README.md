# catchWish
Catching the information of wish.com commodities and generating the table than can be uploaded to dianxiaomi.com directly.

# 使用说明
```
$ ./catchWish + ID
or
$ sudo cp catchWish /usr/local/bin/
$ catchWish + ID
```

# v1.0
## 功能介绍
　　单进程版，每次执行只能够生成包含一条商品信息的表单文件  

# v2.0
## 功能介绍
　　多线程版，每次执行能够处理N个（视ID个数而定）商品，并最终生成包含N个商品信息的表单文件  

# toDo
- 生成表单文件结束后，报告因网络或其他原因处理失败的产品ID
- 进一步模块化代码结构，使功能布局更加清晰
