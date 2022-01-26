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

/*
Would you be able to implement this function if the first parameter was changed
to int* x? Explain why or why not.



Would you be able to implement this function if the second parameter was
changed to int n? Explain why or why not.



*/