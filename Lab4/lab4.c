#include "lab4.h"

typedef struct SearchQueue {
	struct PlayerRecord* player_record;
	struct SearchQueue* next;
	int rank;
} SearchQueue;

void pop(SearchQueue** head) {
	SearchQueue* temp = *head; 
	*head = (*head) -> next;
	free(temp);
}

void push(SearchQueue** tail, PlayerRecord* player_record, int rank) {
	SearchQueue* new_node = (SearchQueue*) malloc(sizeof(SearchQueue));
	(*tail) -> next = new_node;
	new_node -> next = NULL;
	new_node -> player_record = player_record;
	new_node -> rank = rank;
	*tail = new_node;
}

void empty_queue(SearchQueue** head){
	while(*head != NULL){
		pop(head);
	}
}

Player* create_player(char name[], char id[]){
	/**
		Creates and returns a pointer to a newly
		created dynamically allocated Person struct,
		with its <name> and <id> fields initialized
		to the values given by the respectively named 
		parameters.
		
		Hint: strcpy(...) from <string.h> may be helpful.
	*/
	Player* new_player = (Player*) malloc(sizeof(Player));
	strcpy(new_player -> name, name);
	strcpy(new_player -> id, id);
	return new_player;
}

PlayerRecord* create_leaf_record(Player* p){
	/**
		Creates and returns a pointer to a newly created
		dynamically allocated PlayerRecord struct. 
		
		The record created is for the starting bracket
		of a tournament, for player <p>, where <p> is
		a dynamically allocated Player struct as returned
		by create_player(...).
		
		Initializes the new PlayerRecord to have 0 wins 
		and 0 losses; the left_child, right_child, and 
		parent are set to NULL.
		
		The player field should be set to <p>.
	*/
	PlayerRecord* new_record = (PlayerRecord*)malloc(sizeof(PlayerRecord));
	new_record -> player = p;
	new_record -> game_records[0] = 0;
	new_record -> game_records[1] = 0;
	new_record -> parent = NULL;
	new_record -> left_child = NULL;
	new_record -> right_child = NULL;

	return new_record;

}

PlayerRecord* add_match(
	PlayerRecord* p1, PlayerRecord* p2, 
	int p1_wins, int p2_wins
){
	/**
	Creates and returns a pointer to a newly created
	dynamically allocated PlayerRecord struct.
	
	Joins the tournament trees given by <p1> and <p2>, where
	<p1> and <p2> are dynamically allocated PlayerRecord structs
	as returned by create_leaf_record(...).

	Updates <p1->parent> and <p2->parent> to be the newly
	created PlayerRecord. Updates the left_child and right_child 
	of the newly created PlayerRecord to reflect the 
	loser and winner of the match, respectively. Fills the new
	PlayerRecord's game_records field.
	
	<p1->parent> and <p2->parent> are guaranteed to be NULL.
	*/

	PlayerRecord* new_record = (PlayerRecord*)malloc(sizeof(PlayerRecord));
	p1->parent = new_record;
	p2->parent = new_record;
	if (p1_wins > p2_wins){
		new_record -> player = p1 -> player;
		new_record -> game_records[WINS] = p1_wins;
		new_record -> game_records[LOSSES] = p2_wins;
		new_record -> left_child = p1;
		new_record -> right_child = p2;	
	}
	else{
		new_record -> player = p2 -> player;
		new_record -> game_records[WINS] = p2_wins;
		new_record -> game_records[LOSSES] = p1_wins;
		new_record -> left_child = p2;
		new_record -> right_child = p1;
	}
	new_record -> parent = NULL;
	
	return new_record;

}

int get_player_rank(char player_id[], PlayerRecord* root){
	/**
	Get the rank of the player identified by <player_id>.
	<root> refers to the root of a completed tournament.
	
	You may assume that each player has a unique id.
	*/
	
	if(root == NULL) {
		return -1; // queue is empty
	}
	
	SearchQueue* head = (SearchQueue*)malloc(sizeof(SearchQueue));
	SearchQueue* tail = head;
	
	head -> player_record = root;
	head -> rank = 1;
	head -> next = NULL;

	while(head != NULL){
		if(strcmp(head -> player_record -> player -> id, player_id) == 0) {
			int rank = head -> rank;
			empty_queue(&head);
			return rank;
		}
		else{
			if(head -> player_record -> left_child != NULL) {
				push(&tail, head -> player_record -> left_child, head -> rank + 1);

			}
			if(head -> player_record -> right_child != NULL) {
				push(&tail, head -> player_record -> right_child, head -> rank + 1);

			}
			pop(&head);
		}
	}	
	return -1; // could not find it
}

/**

	========== PROVIDED FUNCTIONS BELOW ==========
	DO NOT MODIFY.
*/

void clear_tournament_records_helper(
	PlayerRecord* curr, PlayerRecord** records, 
	int* num_records, int* max_records
){
	/**
		Performs a pre-order traversal to retrieve all
		the player records and stores them in <records>,
		an array of pointer to PlayerRecord.
		
		Updates the dynamic array when needed by doubling the 
		size. If the dynamic array is resized, <*max_records> 
		is updated.
		
		<*num_records> is updated to reflect the total number 
		of records.
	*/
		
	if ((*max_records) == (*num_records)){
		// resize
		(*records) = realloc(*records, sizeof(PlayerRecord*) * (*max_records) * 2);
		(*max_records) *= 2;
	} 
	
	(*records)[*num_records] = curr;
	(*num_records)++;

	if (curr->left_child != NULL){
		clear_tournament_records_helper(
			curr->left_child, records, 
			num_records, max_records
		);
	}
	
	if (curr->right_child != NULL){
		clear_tournament_records_helper(
			curr->right_child, records, 
			num_records, max_records
		);
	}
}

void clear_tournament_records(PlayerRecord** root){
	/**
		Frees all memory associated with the tournament,
		EXCLUDING the Player(s)
	*/
	int num_records = 0;
	int max_records = 10;
	
	PlayerRecord** records = (PlayerRecord**)malloc(sizeof(PlayerRecord*) * max_records);
	if ((*root) != NULL){
		clear_tournament_records_helper(*root, records, &num_records, &max_records);
	}
	
	for (int i=0; i<num_records; i++){
		free(records[i]);
	}
	*root = NULL;
	free(records);
}

void print_tournament_records(PlayerRecord* curr, PlayerRecord* root){
	/**
		Prints out the tournament records as a post-order traversal.
	*/
	if(curr->left_child != NULL){
		print_tournament_records(curr->left_child, root); 
		print_tournament_records(curr->right_child, root);
		
		fprintf(stdout, "%s VS %s\nRESULT: ", curr->left_child->player->id, curr->right_child->player->id);
	}
	
	fprintf(stdout, "%s with Wins: %d Losses: %d\n", 
		curr->player->id, 
		curr->game_records[WINS],
		curr->game_records[LOSSES]
	);
	
}

int player_in_list(Player* p, Player** player_list, int count_el){
	/**
		Returns 1 if <p> is found in <player_list>, returns 0 
		otherwise.
	*/
	for (int i=0; i<count_el; i++){
		if (p->id == (player_list[i])->id) {
			return 1;
		} 
	} return 0;
}

void collect_at_rank(
	PlayerRecord* curr,
	PlayerRecord* root, 
	Player** players_at_curr_rank, 
	int rank,
	int* count_el, 
	int* max_el
){	
	/**
		Collects all players with rank <rank> and stores them in <players_at_curr_rank>,
		updating <*count_el> and <*max_el> as needed.
	*/
	int tmp_rank = get_player_rank(curr->player->id, root);
	if (tmp_rank == rank && !player_in_list(curr->player, players_at_curr_rank, *count_el)){
		if ((*count_el) == (*max_el)){
			// resize
			players_at_curr_rank = realloc(players_at_curr_rank, sizeof(Player*) * (*max_el) * 2);
			(*max_el) *= 2;
		}
		players_at_curr_rank[*count_el] = curr->player;
		(*count_el)++;
	}
	if (curr->left_child != NULL){
		collect_at_rank(curr->left_child, root, players_at_curr_rank, rank, count_el, max_el);
	}
	if (curr->right_child != NULL){
		collect_at_rank(curr->right_child, root, players_at_curr_rank, rank, count_el, max_el);
	}
}

void print_with_rank(PlayerRecord* root){
	/**
	Prints a record of all players and their rank once the tournament
	has concluded. <root> refers to a completed tournament tree.
	
	Warning: very inefficient, do not use on large trees
	*/
	int count_el = 0;
	int max_el = 10;
	int curr_rank = 1;
	Player** players_at_curr_rank = (Player**)malloc(sizeof(Player*) * max_el);
	
	do {
		count_el = 0;
		collect_at_rank(root, root, players_at_curr_rank, curr_rank, &count_el, &max_el); 
		for (int i=0; i<count_el; i++){
			fprintf(stdout, "Rank %d: %s\n", curr_rank, (players_at_curr_rank[i])->id);
		}
		curr_rank++;
	} while (count_el != 0);
	free(players_at_curr_rank);
}


/*

What are the best- and worst- case runtimes of the provided implementations?
Identify any modifications you can make to the implementations to improve their runtimes, if any. Explain to your TA.

-----------------------------------------

For clear_tournament_records(),
Best case Ω(1) when *root == NUll
Worst case O(n) where n is the number of player records
	2(2n-1)
		-> Adding each Player to double pointer + freeing each Player
	n
Though this would not improve complexity, runtime could possibly be improved by freeing within the helper function 
so that one does not to transverse the array again

For print_with_rank(),
Best case is Ω(1)
Worst case is O(n^2*lnn)
	(log 2 n + 1) * (2^(log 2 n + 1) - 1) * (2n)
		-> Num of rank * Num of Player Records * (Compexity of get_player_rank() + player in list())
	2n * log 2 n * (2n + 1)
	n ^ 2 * logn
Complexity could be made O(n) with a similar implimentation as get_player_rank that creates the queue, O(n) and the prints
it, also O(n). To the struct should be added a boolean value that is set to false for right children so that they
are not printed twice.
*/
