compile C with C++

test.cpp and command.c

extern C in defs.h

https://blog.csdn.net/monroed/article/details/54880944

gcc也可以编译C++文件，只是gcc不能自动联接C++程序使用的库，即链接过程我们不能用gcc。
而g++实际上在编译C++文件时也是使用gcc编译器，在链接时才使用g++

g++ will change the name of functions in object files if used for compiling C source files, different from gcc

