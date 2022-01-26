#include <stdio.h>
#include <stdlib.h>

int main(){

    int ** p;

    int x = 10; 
    int y = 11; 
    int z = 12; 

    int * ptr = (int *) malloc ( sizeof (int) * 3); 
    *ptr = x; 
    *( ptr + 1) = y; 
    *( ptr + 2) = z; 

    p = &ptr;

    free(ptr);

    return 0;

}

/*

Draw a memory model for the above code. You may use arbitrary memory
addresses to simplify the task.

p         *p
0x004 --> [a]
x         *x
0x008 --> [10]
y         *y
0x012 --> [11]
z         *z
0x016 --> [12]
ptr                     *ptr
0x020 (and next 2) --> [b][c][d]

ptr                     *ptr
0x020 (and next 2) --> [10][c][d]

ptr                     *ptr
0x020 (and next 2) --> [10][11][d]

ptr                     *ptr
0x020 (and next 2) --> [10][11][12]

p         *p
0x004 --> [0x020]

*/