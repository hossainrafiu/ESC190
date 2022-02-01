#include <stdio.h>
#include <stdlib.h>

int main(){

    int *p = (int *) malloc ( sizeof (int ));
    fprintf (stdout , " Value stored at address %p: %d\n", p, *p);
    *p = 1;
    fprintf (stdout , " Value stored at address %p: %d\n", p, *p);
    free (p);
    fprintf (stdout , " Value stored at address %p: %d\n", p, *p);

    return 0;

}

/*
    Explain what is happening in this code. Is there a memory leak?

The first line alocates memory space to p to fit one int (4 bytes).
The first print statement prints whatever garbage value was in memory.
The value at the address of p is then changed to 1, changing *p to 1. 
Finally free(p) frees the memory at p, changing it back to the value that 
memory address had before it was allocated.
There is not memory leak.

    What parts of Valgrind’s output helps you identify the problem in the code?

Near the end of its output Valgrind either says no leaks are possible or it lists what was lost.

    Try compiling your executable with the -g flag, and rerun the command above.
    What is the difference between compiling with vs. without the -g flag?

When using the -g flag, valgrind is able to tell us exactly where warnings or errors (events) 
are occuring (exact line number in the c file).
Without the -g flag, valgrind would only say what was happening (e.g. block allocation) from 
the .exe file. 

UWaterloo:
    If you compile your program with the -g flag, Valgrind will show you the function names and 
    line numbers where errors occur. Sometimes the actual bug occurs on a different line 
    (particularly for uninitialized value errors) but the line number Valgrind tells you is a 
    good starting point.
*/