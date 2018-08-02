# 编译
## 编译参数
Makefile中一共有5个参数，分别是CXX、AR、CPPFLAGS、DESTINATION、DEBUG、MODE

CXX：设置g++编译器的具体位置，默认为g++

AR：设置AR的具体位置，默认为ar

CPPFLAGS：设置g++编译器的编译选项，默认项请参考Makefile

DESTINATION：设置安装目录，默认为/usr/local/lib

DEBUG：设置编译时debug选项，选项为TRUE或FALSE，设置其他值都为FALSE，要设置debug时请设置DEBUG=TRUE

MODE：设置编译时所设置的模块名，现阶段只有BESTBUY，当编译BESTBUY工程时请设置MODE=BESTBUY，其他值为Price工程

---

## Linux下编译
进入到工程根目录下执行“make -j8”，等待编译完成即可

例1：make DEBUG=TRUE MODE=BESTBUY 编译debug版的BestBuy工程

例2：make DEBUG=TRUE 编译debug版的Price工程

例3：make 直接编译非debug版的Price工程

---

## Windows下编译
进入到工程目录下，执行“make CXX=../../tools/gcc-4.4.7/bin/x86_64-redhat-linux-g++ AR=../../tools/gcc-4.4.7/bin/x86_64-redhat-linux-ar -j8”，等待编译完成。

CXX设置g++编译器，AR设置ar连接器，如果要编译成debug版增加DEBUG=TRUE选项，如果要编译BESTBUY工程增加MODE=BESTBUY选项。

---

## 编译后的清理

在windows下执行clean进行清理，在linux下在工程根目录下执行“make clean”。

---

## 安装
执行“make DESTINATION=/home/rdtfare/todefare/plugin install”进行安装，make会将编译出来的so文件拷贝至DESTINATION指定的目录里，如果编译的是BestBuy工程，必须增加MODE=BESTBUY选项。

windows下暂不支持。