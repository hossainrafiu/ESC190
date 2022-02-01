#include <stdio.h>
#include <stdlib.h>

void append (int ** x, int * n, int val ){
/**
<*x> refers to a dynamically allocated integer array
of size <*n> * sizeof (int ).
Modifies <*x> such that it has val added to the end.
The modified array should be of length <*n> + 1.
Modifies <*n> such that it is updated to be the value
of the new length of the array <*x >.
HINT : you may find the function realloc (...) helpful
*/
    fprintf (stdout," %p\n", *x);
    fprintf (stdout," %d\n", **x);
    fprintf (stdout," %d\n", *n);
    *x = realloc(*x, (*n + 1)*sizeof(int));
    *(*x + *n) = val;
    *n += 1;
    for(int j = 0; j < *n; j++) {
        fprintf(stdout, "%d\n", *(*x + j));
    }
}

/*
int main(){

    int n = 0;
    int *x = (int *) calloc(n, sizeof(int));
    // *x = 5;
    //(x + 1) = 7;
    int val = 10;
    append(&x, &n, val);
    append(&x, &n, val);
    append(&x, &n, val);
    fprintf (stdout," Values of x through dereferencing 0: %d, 1: %d, 2: %d\n",*x, *(x + 1), *(x + 2));

}
*/

/*
    Would you be able to implement this function if the first parameter was changed
    to int* x? Explain why or why not.

Yes because you still pass the value of x to the function which is the 
first memory location of the allocated memory of x which can be modified with realloc.
Essentially, all that would be needed is to get rid of a star from each location of x
in the function and it SEEMS!!!!! to function the same.

    Would you be able to implement this function if the second parameter was
    changed to int n? Explain why or why not.

No because you do not have access to the address of n as you do not have a pointer 
so you cannot modify the value outside the function,
only the copy that was passed into the function.

No because even if you pass the address of the integer to the function, you can't de-refernce 
and change the value at the memory address because n isn't a pointer. The value of n is just
the integer value of the memory address.
*/