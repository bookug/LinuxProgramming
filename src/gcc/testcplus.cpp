/*=============================================================================
# Filename: restrict.cpp
# Author: bookug 
# Mail: bookug@qq.com
# Last Modified: 2018-10-25 00:06
# Description: 
command line option ‘-std=c99’ is valid for C/ObjC but not for C++
Therefore, some features of C99(and later) can not be used in C++
http://bdxnote.blog.163.com/blog/static/84442352010017185053/
=============================================================================*/

#include <stdlib.h>
#include <stdio.h> 
//NOTICE: if we do not add this(or other C++ specified syntax/library), we can compile the program using gcc directly, even we use using namespace std; 
//(gcc will still treat this file as C++ source file, for example, the name of functions will has prefix and suffix if we use objdump -t to see the information, different from C)
//However, if we add this header, even if we do not use cin/cout, the compilation will report errors due to lacking in C++ library
//but we can use gcc -lstdc++ to compile it, in fact g++ is just a front-end that calls gcc with appropriate options
#include <iostream> 
//NOTICE: in C source file, both iostream and namespace can not be used, it is just C code!
//If you compile C code using g++, then it is treated like C++ file, for example, its function name will be added prefix and suffix
using namespace std; 

int main()
{
    //NOTICE: CRLF and LF, one for windows(\r\n), the latter for Linux/MacOS(\n)
    //Sometimes it will cause problem, like git, you should set on windows like git config --global core.autocrlf true
    printf("use of restrict\n");
    cout<<"just a test for C/C++"<<endl;

    return 0;
}

