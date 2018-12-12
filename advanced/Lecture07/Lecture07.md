

Linux 中多线程与多进程共享一套内核接口vfork，但传入不同的参数指定共享级别

查看多进程和多线程的命令

多线程也占用PID，在ulimit设置时需要注意

---

多cpu，多核，超线程技术

https://www.zhihu.com/question/20998226

https://www.cnblogs.com/gtarcoder/p/5295281.html

http://www.cnblogs.com/jacksu-tencent/p/3362483.html

https://blog.csdn.net/bigbug_zju/article/details/41044835

---

计时函数

当程序要进行IO时，原程序会等待(睡眠)，内核态进行IO传输

使用clock()函数计算出来的时间就为总的CPU时间。也就是说，clock函数不能区分用户空间和内核空间。

一个clock tick不是CPU的一个时钟周期，而是C/C++的一个基本计时单位，因此只与编译器有关。在TC2.0中硬件每18.2个滴答是一秒，在VC中硬件每1000个滴答是一秒，在标准POSIX中定义为1000000个滴答为一秒。

https://www.cnblogs.com/wfwenchao/p/5195022.html

https://blog.csdn.net/u010821666/article/details/78584603

clock()函数会受多线程的影响，但gettimeofday不会。
不过，如果单核上有很多程序在跑，gettimeofday是否会受睡眠的影响？
可以做实验来检验:)

https://blog.csdn.net/tjcwt2011/article/details/72884617

