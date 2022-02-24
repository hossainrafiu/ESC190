#include "a1.h"

/**
	Add your functions to this file.
	Make sure to review a1.h.
	Do NOT include a main() function in this file
	when you submit.
*/

Restaurant* initialize_restaurant(char* name){

	Restaurant *new_restaurant = (Restaurant *) malloc(sizeof(struct Restaurant));

	new_restaurant->name = name;
	new_restaurant->menu = load_menu("menu.txt");
	new_restaurant->num_completed_orders = 0;
	new_restaurant->num_pending_orders = 0;
	
	Queue* new_queue = (Queue *) malloc(sizeof(struct Queue));
	new_queue->head = NULL;
	new_queue->tail = NULL;
	
	new_restaurant->pending_orders = new_queue;

	return new_restaurant;
}

// MAKE SURE THAT STRING ENDS WITH NULL CHARACTER
Menu* load_menu(char* fname){
	FILE* menu_file;
	menu_file = fopen(fname, "r");
	Menu* menu = (Menu *) malloc(sizeof(struct Menu));
	int num_items = 0;
	char c;
	while(c != EOF) {
		c = fgetc(menu_file);
		if (c == '$') {
			num_items++;
		}
	}
	rewind(menu_file);
	menu->num_items = num_items;
	char** item_codes = (char **) malloc(num_items * sizeof(char*));
	char** item_names = (char **) malloc(num_items * sizeof(char*));
	double* item_cost_per_unit = (double *) malloc(num_items * sizeof(double));
	for (int i = 0; i < num_items; i++) {
		char* x;
		char* y;
		char* z;
		char temp[ITEM_CODE_LENGTH + MAX_ITEM_NAME_LENGTH + MAX_ITEM_QUANTITY_DIGITS + 10];
		char* line = fgets(temp, sizeof(temp) , menu_file);
		while(*line == ' ' || *line == '\r' || *line == '\t') {
			line ++;
		}
		x = strtok(line, MENU_DELIM);
		y = strtok(NULL, MENU_DELIM);
		z = strtok(NULL, MENU_DELIM);
		
		char* z_temp = (char*)malloc(strlen(z));
		strncpy(z_temp,&z[1],strlen(z)-1);
		double z_double = atof(z_temp);
		free(z_temp);
		
		item_codes[i] = (char *)calloc(sizeof(char), ITEM_CODE_LENGTH);
		strcpy(item_codes[i],x);
		
		item_names[i] = (char *)calloc(sizeof(char), MAX_ITEM_NAME_LENGTH);
		strcpy(item_names[i],y);
		
		item_cost_per_unit[i] = z_double;
	}
	menu->item_codes = item_codes;
	menu->item_names = item_names;
	menu->item_cost_per_unit = item_cost_per_unit;
	
	fclose(menu_file);
	return menu;
}


Order* build_order(char* items, char* quantities){

	Order* new_order = (Order *) malloc(sizeof(struct Order));
	int num_of_items = strlen(items)/(ITEM_CODE_LENGTH-1);
	char** item_codes = (char **) malloc(sizeof(char*)*num_of_items);
	int* item_quantities = (int *) malloc(sizeof(int)*num_of_items);

	new_order->num_items = num_of_items;
	
	char* item_quan;
	char* temp = strdup(quantities);
	item_quan = strtok(temp,MENU_DELIM);
    int item_num = 0;
	while(item_quan != NULL){
	    item_quantities[item_num] = atoi(item_quan);
        item_quan = strtok(NULL, MENU_DELIM);
        item_num++;
    }
	free(temp);

	new_order->item_quantities = item_quantities;

	for (int i = 0; i < num_of_items ; i++){
		item_codes[i] = (char *)calloc(sizeof(char),ITEM_CODE_LENGTH);
		strncpy(item_codes[i],&items[(ITEM_CODE_LENGTH-1)*i],ITEM_CODE_LENGTH-1);
	}
	new_order->item_codes = item_codes;

	return new_order;
}

void enqueue_order(Order* order, Restaurant* restaurant){
	QueueNode* new_queue_node = (QueueNode *)malloc(sizeof(struct QueueNode));
	new_queue_node->order = order;
	if (restaurant->pending_orders->head == NULL) {
		restaurant->pending_orders->head = new_queue_node;
		restaurant->pending_orders->tail = new_queue_node;
	} else {
		restaurant->pending_orders->tail->next = new_queue_node;
		restaurant->pending_orders->tail = new_queue_node;
	}
	restaurant->num_pending_orders++;
}

Order* dequeue_order(Restaurant* restaurant){
	Order* order = restaurant->pending_orders->head->order;
	QueueNode* temp = restaurant->pending_orders->head;
	restaurant->pending_orders->head = restaurant->pending_orders->head->next;
	free(temp);
	// Only one item left in Queue
	if(restaurant->pending_orders->head == NULL){
		restaurant->pending_orders->tail == NULL;
	}
	restaurant->num_pending_orders--;
	restaurant->num_completed_orders++;
	return order;
}


double get_item_cost(char* item_code, Menu* menu){
	int index = 0;
	while (strcmp((menu->item_codes)[index],item_code)!=0){
		index++;
	}
	return (menu->item_cost_per_unit)[index];
}


double get_order_subtotal(Order* order, Menu* menu){
	double subtotal = 0;
	for (int i = 0; i < order->num_items; i++){
		char* item = (order->item_codes)[i];
		double item_cost = get_item_cost(item, menu);
		subtotal += item_cost*(double)(order->item_quantities)[i];
	}
	return subtotal;
}


double get_order_total(Order* order, Menu* menu){
	double subtotal = get_order_subtotal(order, menu);
	return subtotal + subtotal * TAX_RATE / 100;
}


int get_num_completed_orders(Restaurant* restaurant){
	return restaurant->num_completed_orders;
}


int get_num_pending_orders(Restaurant* restaurant){
	return restaurant->num_pending_orders;
}


void clear_order(Order** order){
	free((*order)->item_quantities);
	for (int i = 0; i<(*order)->num_items ; i++){
		free(((*order)->item_codes)[i]);
	}
	free((*order)->item_codes);
	free(*order);
	*order = NULL;
}


void clear_menu(Menu** menu){
	free((*menu)->item_cost_per_unit);
	for (int i = 0; i<(*menu)->num_items ; i++){
		free(((*menu)->item_codes)[i]);
		free(((*menu)->item_names)[i]);
	}
	free((*menu)->item_codes);
	free((*menu)->item_names);
	free(*menu);
	*menu = NULL;
}


void close_restaurant(Restaurant** restaurant){
	clear_menu(&((*restaurant)->menu));
	while((*restaurant)->pending_orders->head != NULL){
		Order* temp = dequeue_order(*restaurant);
		clear_order(&temp);
	}
	free((*restaurant)->pending_orders);
	free(*restaurant);
	*restaurant = NULL;
}


void print_menu(Menu* menu){
	fprintf(stdout, "--- Menu ---\n");
	for (int i = 0; i < menu->num_items; i++){
		fprintf(stdout, "(%s) %s: %.2f\n", 
			menu->item_codes[i], 
			menu->item_names[i], 
			menu->item_cost_per_unit[i]	
		);
	}
}


void print_order(Order* order){
	for (int i = 0; i < order->num_items; i++){
		fprintf(
			stdout, 
			"%d x (%s)\n", 
			order->item_quantities[i], 
			order->item_codes[i]
		);
	}
}


void print_receipt(Order* order, Menu* menu){
	for (int i = 0; i < order->num_items; i++){
		double item_cost = get_item_cost(order->item_codes[i], menu);
		fprintf(
			stdout, 
			"%d x (%s)\n @$%.2f ea \t %.2f\n", 
			order->item_quantities[i],
			order->item_codes[i], 
			item_cost,
			item_cost * order->item_quantities[i]
		);
	}
	double order_subtotal = get_order_subtotal(order, menu);
	double order_total = get_order_total(order, menu);
	
	fprintf(stdout, "Subtotal: \t %.2f\n", order_subtotal);
	fprintf(stdout, "               -------\n");
	fprintf(stdout, "Tax %d%%: \t$%.2f\n", TAX_RATE, order_total);
	fprintf(stdout, "              ========\n");
}