#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char* a = "hello";
    char* b = strstr(a, "l");
    printf("%s,%s",a,b);
    //b = 'a';
    printf("%s,%s",a,b);

    return 0;
}