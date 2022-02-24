#include "a1.h"

int main(){

	Order* order = build_order("L1L2L3", "10,11,12");
    print_order(order);
    clear_order(&order);
	return 0;
}