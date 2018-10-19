#include <stdio.h>
#include <malloc.h>
#include "defs.h"
#include <iostream>

using namespace std;

class Test
{
	public:
		int x;
};

int main(){
    point    *p;
    
    p = (point*)malloc(sizeof(point));
    if (p != NULL){
        p->x = 0;
        p->y = 0;
    }
    else {
        printf("p is a NULL pointer.\n");
        return 1;
    }

    input(p);
    display(p);
    
    free(p);

	func();
    
    return 0;
}
