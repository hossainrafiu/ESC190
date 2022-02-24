#include "a1.h"

int main(){

	Order * order = build_order ( "A1B1C1" , "20,17,11" );
    print_order(order);
	
	return 0;
}
