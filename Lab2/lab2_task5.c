#include <stdio.h>
#include <stdlib.h>

int main(){

    int *p = (int *) malloc ( sizeof (int )); 
    int *q = (int *) malloc ( sizeof (int) * 2); 
    *p = 1; 
    *q = 10; 
    
    q = p; 
    free (q); 
    free (p); 

    return 0;

}
/*

Draw a memory model for the above code.

p
0x5555555592a0 --> [a]
q
0x5555555592c0 --> [b]

p
0x5555555592a0 --> [1]
q
0x5555555592c0 --> [10]

p
0x5555555592a0 --> [1]
                    ^
q                   |
0x5555555592a0 -----

p
0x5555555592a0 --> [a]
                    ^
q                   |
0x5555555592a0 -----

ERROR (freeing the same memory address twice)

    Describe the memory malpractice in the above code. 
    You may wish to use Valgrind as described previously.

When we set q = p before freeing it we lose the address of q, 
so when we execute free(q) it does not free that block, meanining it is lost, and instead
the same block is freed twice.

*/