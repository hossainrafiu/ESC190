#include <stdio.h>
#include <stdlib.h>

int main(){

    int y[2] = {1, 5};
    int x [3];
    for (int i = 0; i < 3; i ++){
    x[i] = y[i];
    }
    x[2] = 9;

    fprintf (stdout," Addresses of x 0: %p, 1: %p, 2: %p\n", x, x + 1, x + 2);
    //fprintf (stdout," Addresses of y 0: %p, 1: %p\n", y, y + 1);
    fprintf (stdout," Values of x through dereferencing 0: %d, 1: %d, 2: %d\n",*x, *(x + 1), *(x + 2));
    fprintf (stdout," Values of x through indexing 0: %d, 1: %d, 2: %d\n", x[0] , x[1] , x[2]);
    fprintf (stdout," Indexing out of range : %d\n", x[3]);

    return 0;

    /*
        What happens when you attempt to access an element out of range of the array allocated?

    The code returns the random value that happens to exist at the physical location that the element's memory address points to.

        Attempt to extend the size of the array by doing y[2] = 9. What happens?

    The code does actually assign the value at the address, but since the address has not been alocated, the value will be used by other code or programs.
    This may also be dangerous as doing this may change the value of another variable in memory.


    Complete the following diagram with the memory addresses you get from running
    the above code. Add the memory blocks for y to the diagram. You may wish to
    add print statements to help draw your diagram.

    Variable | Memory Address | Value | Variable De-referenced
    x          0x7fffffffdeac   1       *x / x[0]
    x + 1      0x7fffffffdeb0   5       *(x + 1) / x[1]
    x + 2      0x7fffffffdeb4   9       *(x + 2) / x[2]
    y          0x7fffffffdea4   1       *y / y[0]
    y + 1      0x7fffffffdea8   5       *(y + 1) / y[1]
    */

}