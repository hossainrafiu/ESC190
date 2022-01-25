#include <stdio.h>

int main(){

    int temp = 1;
    int *test = &temp, count = 0;

    printf("%d", *test);

    while (!(count == 100)){

        count ++;
        test = test + 1;
        printf("%d \n",*test);

    }

    return 0;
}