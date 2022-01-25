#include <stdio.h>
#include <math.h>
#include <string.h>
#include "lab1.h"
// rename to lab1.h

double split_bill ( double base_amount , double tax_rate , double tip_rate , int num_people ) {
	double tax = tax_rate * base_amount;
	double tip = tip_rate * (base_amount + tax);
	double total_amount = base_amount + tax + tip;
	double split_amount = total_amount / num_people;
	split_amount = ((int)(split_amount * 100 )) / 100.0;
	if (split_amount * num_people < total_amount){
		split_amount += .01;
	}
	return split_amount;
}


double adjust_price ( double original_price ) {
	return 10 * pow(original_price, 0.5);
}


int sandy_eats (char menu_item []){
	int letters = 0;
	for (int i = 0; menu_item[i] ; i++){
		if(menu_item[i] > 90){
			if(menu_item[i] - 32 >= 65 && menu_item[i] - 32 <= 90){
				letters++;
			}
		}
		else if(menu_item[i] >= 65 && menu_item[i] <= 90) letters++;
		
		if(menu_item[i] == 74 || menu_item[i] == 106) return 0; // "J/j"
		if(menu_item[i] == 75 || menu_item[i] == 107) return 0; // "K/k"
		if(menu_item[i] == 76 || menu_item[i] == 108) return 0; // "L/l"

		// "F/f"
		if(menu_item[i] == 70 || menu_item[i] == 102){
			// "I/i"
			if(menu_item[i+1] == 73 || menu_item[i+1] == 105){
				// "S/s"
				if(menu_item[i+2] == 83 || menu_item[i+2] == 115){
					// "H/h"
					if(menu_item[i+3] == 72 || menu_item[i+3] == 104){
						return 0;
					}
				}
			}
		}
	}
	if (letters % 2 == 1) {
		return 0;
	}
	
	return 1;
}


void imagine_fish(char thing []) {
	strcat(thing, "fish");
	/*
	int i = 0;
	for (;thing[i]; i++){
	}
	thing[i] = 'f';
	thing[i + 1] = 'i';
	thing[i + 2] = 's';
	thing[i + 3] = 'h';
	thing[i + 4] = '\0';
	*/	
}




	/*
		Question: If result is an int variable and num is a float variable, what does the following line of code do? 
		
		result = (int) (num + 0.5);

		Answer: It rounds num to the nearest integer and assigns result that value.
		((int) rounds down but (num + 0.5) makes it so that if the decimal part of num is greater than .5, it'll "round up")
		For negative numbers, it doesn't round properly. 
	*/
 
	/*
		Question: When and how did you handle rounding the split amount? Explain.

		We handled it after determining split_amount via an if statement. 
	*/
	
	/*
		Question: How would you solve this problem with and without using string.h functions? Explain.

		Answer: Provided as commented out code.
	*/