#include "WSP.h"

/*  = = =  Node Functions  = = =  */

/* Fungsi untuk mengalokasikan memori untuk node baru dan menginisialisasinya */
Node* allocation (){
	Node* node = (Node*) malloc(sizeof(Node));
	
	if (node == NULL) {
		printf ("\tMemory Penuh");
		exit(EXIT_FAILURE);
	}
	
	node->data = NULL;
	node->right = NULL;
	node->bottom = NULL;
	node->cross = NULL;
	
	return node;
}

/* Fungsi untuk menambahkan node ke board
board: Pointer ke struktur puzzle yang berisi board. */
void addNode(puzzle* board) {
	Node* node = allocation ();
	
	if (board->head == NULL){ //jika tidak ada elemen
		board->head = node;
	} else {
		node->right = board->head;
		board->head = node;
	}
}

/* Fungsi untuk mengatur tautan horizontal antar node
board: Pointer ke struktur puzzle yang berisi board. */
void setRightLinks(puzzle* board) {
	int n = (board->size) * (board->size);
	for (int i = 1; i <= n; i++){
		addNode(&*board);
	}
}

/* Fungsi untuk mengatur tautan vertikal antar node
board: Pointer ke struktur puzzle yang berisi board. */
void setBottomLinks(puzzle* board) {
	Node* currHead = board->head;
	Node* curr = currHead;

	int n = (board->size) * ((board->size) - 1);
	for (int i = 1; i <= n; i++){
		curr = currHead;
		for (int j = 1; j <= board->size; j++){
			if (curr->right != NULL){
				curr = curr->right;
			}
		}
		currHead->bottom = curr;
		currHead = currHead->right;
	}
}

/* Fungsi untuk mengatur tautan diagonal antar node
board: Pointer ke struktur puzzle yang berisi board. */
void setDiagonalLinks(puzzle* board) {
	Node* curr = board->head;
	Node* currHead = board->head;
	
	int n = (board->size) * ((board->size) - 1);;
	for (int i = 1; i <= n; i++){
		curr = currHead;
		for (int j = 1; j <= (board->size) + 1; j++){
			if (curr->right != NULL){
				curr = curr->right;
			}
		}
		currHead->cross = curr;
		currHead = currHead->right;
	}	
	
	currHead = board->head;
	curr = currHead;

	for (int i = 1; i < board->size; i++){
		curr = currHead;
		for (int j = 1; j < board->size; j++){
			if (curr != NULL){
				curr = curr->right;
			}
		}
		curr->cross = NULL;
		curr->right = NULL;
		currHead = currHead->bottom;
	}
}

/* Fungsi untuk membuat puzzle dengan mengatur semua tautan node
board: Pointer ke struktur puzzle yang berisi board. */
void makePuzzle (puzzle* board) {
	setRightLinks(*&board);
	setBottomLinks(*&board);
	setDiagonalLinks(*&board);
}


