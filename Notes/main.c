#include <stdio.h>
#include "a.h"

int main(){
    printf("main");
    hello();
    return 0;
}

/*
    gcc main.c a.c -o main
    ./main

*/