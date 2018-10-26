## Linux 平台 C/C++ 内存调试指南

Valgrind

输出日志  log4cplus

---

#### stack

数组太大

递归调用太深，爆栈

类型溢出导致的各种问题，如非法读写

---

#### heap memory

delete/free/delete[]/new/new[]/malloc 不匹配

尝试释放p+10，但p才是分配的内容起始地址

释放之后再去读

double free

free an invalid address

read/write an invalid address


C++中检查new的返回值与C语言中对malloc的检查不同，必须处理异常而不是判断指针是否非空：

https://blog.csdn.net/hbyzl/article/details/8096007

---

