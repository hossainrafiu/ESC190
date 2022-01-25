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
    fprintf (stdout," Values of x through dereferencing 0: %d, 1: %d, 2: %d\n",*x, *(x + 1), *(x + 2));
    fprintf (stdout," Values of x through indexing 0: %d, 1: %d, 2: %d\n", x[0] , x[1] , x[2]);
    fprintf (stdout," Indexing out of range : %d\n", x[3]);

    /*
    What happens when you attempt to access an element out of range of the array
    allocated?

    

    Attempt to extend the size of the array by doing y[2] = 9. What happens?
    Complete the following diagram with the memory addresses you get from running
    the above code. Add the memory blocks for y to the diagram. You may wish to
    add print statements to help draw your diagram.
    */

}
