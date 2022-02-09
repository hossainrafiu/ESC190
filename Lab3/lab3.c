#include "lab3.h"

/*
Is LIFO a good method for handling the party requests? Why or
why not? It may be easier to answer this question after completing the functions
described below.

LIFO is a good method for handling party requests because it is easy to remove the most recent request,
which is what you most likely want to remove. For example if you add something by accident it will be 
at the top of the stack, so you can remove it without searching.
*/
//Add TA party item request to the list
int add_request(struct party_node **head, char *item, double price, char *ta){
    if (strcmp(item, "IDE") == 0) {
        return -1;
    }
    else {
        struct party_node* new_request = (struct party_node*)malloc(sizeof(struct party_node));
        new_request -> item = item;
        new_request -> price = price;
        new_request -> ta = ta;
        new_request -> next = *head;
        *head = new_request;
        return 0;
    }
}

//Remove the last item added
void remove_request(struct party_node **head){
    struct party_node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

// 
void swap(struct party_node **head, struct party_node *prev,struct party_node *curr, struct party_node *nextt){
    curr -> next = nextt -> next;
    nextt -> next = curr;
    if (prev == NULL){
        *head = nextt;
    } else{
        prev -> next = nextt;
    }
}
/*
a = prev
b = curr
c = next

a -> b -> c -> d

a -> b    c -> d
     L---------^

     v-----
a -> b    c    d
     L---------^

------------
|    v-----V
a    b    c    d
     L---------^


*/

//Sort party item requests - in place?
void make_sorted(struct party_node **head){
    struct party_node *curr = *head, *prev = NULL, *end = NULL, *temp = NULL;
    while(end != *head) {
        while(curr -> next != end) {
            if (curr -> price < (curr -> next) -> price) {
                temp = curr -> next;
                swap(head, prev, curr, curr -> next);
                //print_list(*head);
                prev = temp;
            } else {
                prev = curr;
                curr = curr -> next;
            }
        }
        end = curr;
        curr = *head;
        prev = NULL;
    }
}

//Trim list to fit the budget
double finalize_list(struct party_node **head, double budget){
    double leftover = budget;
    struct party_node* curr = *head,* prev = NULL;
    while(curr != NULL){
        if(curr -> price > leftover){
            if(prev == NULL){
                *head = curr -> next;
                free(curr);
                curr = *head;
            }else{
                prev -> next = curr -> next;
                free(curr);
                curr = prev -> next;
            }
        }else{
            leftover -= curr->price;
            prev = curr;
            curr = curr->next;
            
        }
        //print_list(*head);
    }
    return leftover;
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

/*
What are other ways to sort the data and trim the list? What are the
advantages and disadvantages of these alternatives compared to the approaches
used above?

For sorting, two alternatives are merge sort and quick sort. Both of them have a lower complexity than the bubble sort
that we used, but merge sort cannot be done in place and quick sort requires carefull selection of the pivot or else
it will not have a lower complexity. 

For trimming, we could have inculded an if statement that checks if leftover is 0 or smaller than the cheapest item,
and at that point we could just free the rest of the nodes and return early, instead of continuing to check the price.
Though this may decrease runtime in some cases, it does not provide a signifigant benefit given the size of the list.
*/
}