#include <stdio.h> 
#include <stdlib.h> 

int main(int argc, const char* argv[])
{
	int a[10];
	int* b = (int*)malloc(10* sizeof(int));
	//this will output the whole size of the array a
	printf("check: %d\n", sizeof(a));
	//though b is assigned a new space, this output is the size of the pointer
	printf("check: %d\n", sizeof(b));

	return 0;
}

