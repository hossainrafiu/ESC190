
// This is a single line comment. It is useful for adding short comments
// Start your file with directives (pre-processor commands)
#include <stdio.h> 
// This directive tells the compiler that we want to link the standard 
// input/output library
/* This is a multi-line comment. It is useful for adding documentation.
 * Document: brief description of what the function does, inputs (parameters), 
 * outputs (return values).
 *
 * For example:
 * Description: This main() function prints "Hello World!".
 * Input: the default main() parameters (optional)
 * Output: returns 0
 */
int main(int argc, char **argv) { 
    // int main(void) or int main() would work as well since no arguments 
    //are required
    // This is the function body, statements go here
    // Use ; to end statements and use indenting (tabs or spaces) to make the 
    // code easy to read
    
    // printf() is a function from stdio.h
    printf("Hello World!\n"); // \n is used to print a new-line character

    ////////////////////

    int small_num = 42, overflow_test;
    char a_letter = 'c';
    int unpredictable_num;
    
    //Printing integers and characters
    printf("The value of small_num is: %d\n", small_num);
    printf("We can print small_num as a character: %c\n\n", small_num);
    
    printf("Let's print a_letter: %c\n", a_letter);
    printf("We can print a_letter as an integer: %d\n\n", a_letter);
    
    // Overflow example - avoid this!
    overflow_test = 123456789123456789;
    printf("The value stored in overflow_test is: %d\n", overflow_test);
    
    //The value of predictable_num can vary if we don't assign a value
    printf("unpredictable_num is: %d\n\n", unpredictable_num);
    
    // Integer and floating point casting
    small_num = 42.9999;
    printf("Implicit casting (float value to int variable) - small_num is %d\n", small_num);
    printf("The part of the float value %f was lost during casting \n\n", 42.9999);
    
    printf("Explicit casting (int to float) - (float) %d is %f\n", 2, (float) 2);
    printf("Explicit casting (float to int) - (int) %f is: %d\n\n", 42.9999, (int)42.9999);
    
    printf("We can control the number of decimal places printed:\n");
    printf("42.9999 printed to 2 decimal places is: %.2f\n", 42.9999);
    printf("80.4561 printed to 1 decimal places is: %.1f\n", 123.456-42.9999);
    
    //////////////////

    

    return 0; // return the integer value 0
} // The function body is enclosed in {}
// Note: this is too many comnments, future code demos will have fewer comments.
