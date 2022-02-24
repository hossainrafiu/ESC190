#include "a1.h"

int main(){

	char* name = "andreas";
	Restaurant* new_resturant = initialize_restaurant(name);
	Order * order = build_order ( "A1B1C1" , "20,17,11" );
    print_order(order);
	enqueue_order(order, new_resturant );
    print_order(new_resturant->pending_orders->head->order);
	return 0;
}