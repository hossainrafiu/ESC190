#include<stdio.h>
#include<math.h>
int main() {
double a = 7.5 ;//  assigning values to the declared variables a,b.
double b = 3.0 ;
double power ;  // this variable will store the value of power
power = pow (a, b) ; // calling power function for calculation
printf ( " The value of a raised to the power b is : %lf " , power );
return 0 ;
}