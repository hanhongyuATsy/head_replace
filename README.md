## 目录说明：
    *include     头文件
    *src         c++ 源码文件
    *unit_test   单元测试目录
    *Common      存放打开文件，读取文件公共代码，为解析xml使用
    *Common/RapidXml  解析xml文件代码
    *lib         存放gtest 静态库文件
    *include     存放gtest 头文件
    *unittest.sh  单元测试生成覆盖率脚本
    *Makefile_demo 存储了海哥写的price 项目的Makefile及子目录,留着以后学习模板；

    

## src 源码说明：
### 工程目前有三个类：
	1. class ListFile 类 提供了遍历目录的方法：需要一个路径名作为类初始化的一个参数；
	遍历路径下所有文件，并保存文件名到私有的vecotr中，然后通过文件名后缀将文件分类，
	目前只分了后缀为.h和.cc .cpp 的文件。
	2. class TextQuery 类 提供了读取一个文本文件的方法，可以查询文本文件中是否包含某个字符，
	获取文件的行数，获取文件的编码格式，用某个字符替换某个字符；
	3. ReplaceHeadFile类，调用了前面两类，通过查询#include"xxx.h",来确定头文件名，
    通过遍历目录提供的文件名的vector，把头文件名，和目录做了一个map，再通过TextQuery类的替换函数，
    将头文件名字符串替换为包含路径名的字符串。由于不同路径下有相同的头文件名，
    用宏做开关，定义了multimap，一个头文件名映射多个路径名，替换时选择路径名靠近cpp文件名的路径进行替换。
	4. main 函数，做了三件事， 一是替换头文件名，二是统计每个文件的编码格式，三是统计总的代码行数
## 编译说明：
    make 

## 运行说明：
    ./main

## 运行测试说明：
    ./main_test





