#include "lab3.h"

//Add TA party item request to the list
int add_request(struct party_node **head, char *item, double price, char *ta){
    //Add code here
}

//Remove the last item added
void remove_request(struct party_node **head){
    //Add code here
}

//Sort party item requests - in place?
void make_sorted(struct party_node **head){
    //Add code here
}

//Trim list to fit the budget
double finalize_list(struct party_node **head, double budget){
    //Add code here
}

//Print the current list - hope this is helpful!
void print_list(struct party_node *head){
    int count = 1;
    printf("The current list contains:\n");
    while(head!=NULL){
        printf("Item %d: %s, %.2lf, requested by %s\n",
            count, head->item, head->price, head->ta);
        count++;
        head = head->next;
    }
    printf("\n\n");
    return;
}