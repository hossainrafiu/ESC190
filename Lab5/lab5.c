#include "lab5.h"

/**
Question: Refer to the graph in Figure 1. What is the shortest path from
Kipling station to Don Mills station? Calculate the costs associated with each
vertex in the graph after using Dijkstra’s Algorithm to find the shortest path
between these vertices.

Answer: 
Shortest path: 32
Path: Kipling, Spadina, Bay, Bloor-Yonge, Sheppard_Yonge, Don Mills

Kipling: 0
Spadina: 12
Yorkdale: 20
Bay: 14
Union: 16
Bloor-Yonge: 15 (updated from Bay)
Kennedy: 29
Sheppard_Yonge: 26
Don Mills: 32
Finch: 29
**/

/**
Question: Draw what the graph in Figure 1 would look like after making the
following modifications:
- Add a vertex called Sheppard West.
- Add an edge from Yorkdale to Sheppard West with weight 5.
- Add an edge from Sheppard West to Sheppard-Yonge with weight 4.
- Remove the Bay station vertex (and all the edges connected to it).
What is the shortest path from Kipling to Don Mills after making these modifications? 
Calculate the costs associated with each vertex in the graph after using
Dijkstra’s Algorithm to find the shortest path between these vertices.

Answer:
Shortest path:35
Kipling: 0
Spadina: 12
Yorkdale: 20
Sheppard-West: 25
Sheppard-Yonge: 29
Union: 16
Bloor-Yonge: 19
Kennedy: 33
Don Mills: 35
Finch: 32
**/

typedef struct SearchQueue {
	struct Vnode* station;
	struct SearchQueue* next;
} SearchQueue;

void pop(SearchQueue** head) {
	SearchQueue* temp = *head; 
	*head = (*head) -> next;
	free(temp);
}

void push(SearchQueue** tail, Vnode* station) {
	SearchQueue* new_node = (SearchQueue*) malloc(sizeof(SearchQueue));
	(*tail) -> next = new_node;
	new_node -> next = NULL;
	new_node -> station = station;
	*tail = new_node;
}

// Probably won't use
void empty_queue(SearchQueue** head){
	while(*head != NULL){
		pop(head);
	}
}

char **make_route(Vnode* start, Vnode* dest){
    int max_route_length = 10;
    int route_lenth = 1;
    char **route = (char **)malloc(sizeof(char*)*max_route_length);
    
    Vnode* curr_station = dest;
    route[0] = (char*)malloc(strlen(curr_station->station)+1);
    strcpy(route[0], curr_station->station);
    //printf(" - %s \n",route[route_lenth-1]);
    while(curr_station -> prev != NULL){
        if (route_lenth == max_route_length){
            route = realloc(route, (max_route_length+10)*sizeof(char*));
            max_route_length += 10;
        }
        route[route_lenth] = (char*)malloc(strlen(curr_station->prev->station)+1);
        strcpy(route[route_lenth], curr_station->prev->station);
        //printf(" - %s \n",route[route_lenth]);
        curr_station = curr_station -> prev;
        route_lenth += 1;
    }
    return route;

}

void clear_costs(Graph* gr) {
    for(int i = 0; i < gr -> count; i++) {
        gr -> adj_list[i] -> cost = - 1;
        gr -> adj_list[i] -> visited = 0;
        gr -> adj_list[i] -> prev = NULL;
    }
}

Vnode* find_station(Graph* gr, char *target){
    for(int i = 0; i < gr -> count; i++) {
        if (strcmp(gr->adj_list[i]->station, target) == 0){
            return gr->adj_list[i];
        }
    }
    return NULL;
}

char **plan_route(Graph *gr, char *start, char *dest){
    SearchQueue* head = (SearchQueue*) malloc(sizeof(SearchQueue));
    SearchQueue* tail = head;
        
    Vnode* start_node = find_station(gr, start);
    Vnode* dest_node = find_station(gr, dest);
    
    //printf("%s, %s \n", start_node->station, dest_node->station);
    
    start_node->cost = 0;
    head->station = start_node;
    while(head != NULL){
        Vnode* current_station = head->station;
        Enode* current_edge = current_station->edges;
        //printf("%s \n", current_edge->vertex);
        while(current_edge != NULL){
            Vnode* next_station = find_station(gr, current_edge->vertex);
            if (next_station->cost != -1){
                if(current_station->cost + current_edge->weight < next_station -> cost){
                    next_station->cost = current_station->cost + current_edge->weight;
                    next_station->prev = current_station;
                    push(&tail, next_station); //?
                }
            }
            else{
                next_station->cost = current_station->cost + current_edge->weight;
                next_station->prev = current_station;
                push(&tail, next_station);
            }
            current_edge = current_edge->next;
        }
        pop(&head);
    }

    char** route = make_route(start_node, dest_node);

    clear_costs(gr);

    return route;

}

void add(Graph *gr, char *station){
    //Add code here
    if (find_station(gr, station) != NULL){
        return;
    }
    gr->adj_list = realloc(gr -> adj_list, (gr -> count + 1) * sizeof(Vnode *));
    gr->adj_list[gr->count] = (Vnode *) malloc(sizeof(Vnode));
    
    strcpy(gr->adj_list[gr->count] -> station, station);
    gr->adj_list[gr->count] -> edges = NULL;
    gr->adj_list[gr->count] -> cost = -1;
    gr->adj_list[gr->count] -> visited = 0;
    gr->adj_list[gr->count] -> prev = NULL;
    gr->count += 1;
}

void update(Graph *gr, char *start, char *dest, int weight){
    Vnode* start_node = find_station(gr, start);
    if (start_node == NULL){
        if (weight == 0) {
            return; //?
        }
        else {
            add(gr, start);
            start_node = find_station(gr, start);
        }
    }
    if (find_station(gr, dest) == NULL){
        if (weight == 0) {
            return; //?
        }
        else {
            add(gr, dest);
        }
    }
    Enode* current_edge = start_node -> edges;
    if(current_edge != NULL) {
        if(strcmp(current_edge-> vertex, dest) == 0) {
            if(weight != 0) {
                current_edge -> weight = weight;
            }
            else {
                start_node -> edges = current_edge -> next;
                // free(current_edge -> vertex); //?
                free(current_edge);
            }
            return;
        }
        while(current_edge -> next != NULL) {
            if(strcmp(current_edge -> next -> vertex, dest) == 0) {
                if(weight != 0) {
                    current_edge -> next -> weight = weight;
                }
                else {
                    Enode* temp = current_edge -> next;
                    current_edge -> next = current_edge -> next -> next;
                    //free(temp -> vertex); //?
                    free(temp);
                }
                return;
            }
            current_edge = current_edge -> next;
        }
    }
    if(weight != 0) {
        Enode* new_edge = (Enode *) malloc(sizeof(Enode));
        strcpy(new_edge -> vertex, dest);
        new_edge -> weight = weight;
        new_edge -> next = start_node -> edges;
        start_node -> edges = new_edge;

    }
}

void disrupt(Graph *gr, char *station){
    if(find_station(gr, station) == NULL){
        return;
    }
    for(int i = 0; i < gr -> count; i++) {
        Enode* edge = gr->adj_list[i] -> edges;
        if (edge != NULL){
            if(strcmp(edge->vertex, station) == 0){
                gr->adj_list[i] -> edges = edge->next;
                //free(edge->vertex); //?
                free(edge);
                edge = gr->adj_list[i] -> edges;
            }
            while (edge != NULL && edge->next != NULL){
                if (strcmp(edge->next->vertex, station) == 0){
                    Enode* temp = edge -> next;
                    edge->next = edge->next->next;
                    //free(temp -> vertex); //?
                    free(temp);
                }
                edge = edge -> next;
            }
        }
    }
    // free the node and the edges going from it

    Vnode* station_node;
    int station_index = -1;

    for(int i = 0; i < gr -> count; i++) {
        if (strcmp(gr->adj_list[i]->station, station) == 0){
            station_node = gr->adj_list[i];
            station_index = i;
        }
    }

    while(station_node->edges != NULL){
        Enode* temp = station_node->edges;
        station_node->edges = station_node->edges->next;
        //free(temp -> vertex); //?
        free(temp);
    }
    //free(station_node->station); //?
    free(station_node);

    for(int i = station_index; i < gr->count-1; i++){
        gr->adj_list[i] = gr->adj_list[i+1];
    }
    gr->count -= 1;
    gr->adj_list = realloc(gr->adj_list, gr->count*sizeof(Vnode*));
    
}