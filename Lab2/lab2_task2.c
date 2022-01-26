#include <stdio.h>
#include <stdlib.h>

int main(){

    int x = 0;
    int y = x;
    
    int* ptr_x = &x;
    int* ptr_y = &y;
    int** pptr_x = &ptr_x;
    int** pptr_y = &ptr_y;

    fprintf(stdout,"x contains the value %d at location %p\n", *ptr_x , ptr_x);
    fprintf(stdout , "y contains the value %d at location %p\n", *ptr_y , ptr_y);

}

/*
Draw the memory model for the above piece of code. Include pptr x and pptr y
in your picture. Use the memory addresses you get from running the above
code (you may need to add print statements, if you do, remove these before
submitting).

pptr_x             ptr_x              x
0x7fffffffde80 --> 0x7fffffffde94 --> 0
pptr_y             ptr_y              y
0x7fffffffde88 --> 0x7fffffffde92 --> 0

What are the values of *pptr x, *pptr y, **pptr x, **pptr y?

*pptr x = 0x7fffffffde94
*pptr y = 0x7fffffffde92
**pptr x = 0
**pptr y = 0

How could you make x and y share the same location in memory?

????

*/