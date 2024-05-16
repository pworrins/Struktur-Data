#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct Node {
	char data;
    Node* right;
    Node* bottom;
    Node* cross;
} Node;

typedef struct puzzle {
	Node* head;
	int size;
} puzzle;

Node* allocation (){
	Node* node = (Node*) malloc(sizeof(Node));
	
	if (node == NULL) {
		printf ("\tMemory Penuh");
		exit(EXIT_FAILURE);
	}
	
	node->data = 'A' + rand() % 26;
	node->right = NULL;
	node->bottom = NULL;
	node->cross = NULL;
	
	return node;
}

void addNode(puzzle* board) {
	Node* node = allocation ();
	
	if (board->head == NULL){ //jika tidak ada elemen
		board->head = node;
	} else {
		node->right = board->head;
		board->head = node;
	}
}

void setRightLinks(puzzle* board) {
	int n = (board->size) * (board->size);
	for (int i = 1; i <= n; i++){
		addNode(&*board);
	}
}

void setBottomLinks(puzzle* board) {
	Node* currHead = board->head;
	Node* curr = currHead;

	int n = (board->size) * (board->size);
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

void setDiagonalLinks(puzzle* board) {
	Node* curr = board->head;
	Node* currHead = board->head;
	
	int n = (board->size) * (board->size);
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
}

void makePuzzle (puzzle* board) {
	setRightLinks(*&board);
	setBottomLinks(*&board);
	setDiagonalLinks(*&board);
	
	Node* currHead = board->head;
	Node* curr = currHead;

	for (int i = 1; i <= board->size; i++){
		curr = currHead;
		for (int j = 1; j < board->size; j++){
			if (curr != NULL){
				curr = curr->right;
			}
		}
		curr->cross = NULL;
		currHead = currHead->bottom;
	}
	
}

/* Menampilkan list secara Horizontal menggunakan pointer right */
void displayList(puzzle* board) {
	Node* curr = board->head;
	
	printf("\n = = = = = = = = B O A R D  = = = = = = = =\n ");
	printf("\n");
	while (curr != NULL){
		for (int i = 1; i <= board->size; i++){
			printf("%c ", curr->data);
			curr = curr->right;
		}
		printf("\n");
	}
	printf("\n\n");
}

/* Menampilkan list secara diagonaL menggunakan pointer bottom */
void displayListVertikal(puzzle* board) {
	Node* currHead = board->head;
	Node* curr = currHead;
	
	printf("\n = = = = = = = =  L I S T  V E R T I K A L  = = = = = = = =\n ");
	printf("\n");
	for (int i = 1; i <= board->size; i++){
		curr = currHead;
		for (int j = 1; j <= board->size; j++){
			printf("%c ", curr->data);
			curr = curr->bottom;
		}
		currHead = currHead->right;
		printf("\n");
	}
	printf("\n\n");
}

/* Menampilkan list secara diagonaL menggunakan pointer cross */
void displayListUpperDiagonal(puzzle* board) {
	Node* currHead = board->head;
	Node* curr = currHead;
	
	printf("\n = = = = = = = =  L I S T  D I A G O N A L  U P P E R  = = = = = = = =\n\n");

	for (int i = 1; i <= board->size; i++){
		curr = currHead;
		while (curr != NULL) {
			printf("%c ", curr->data);
			curr = curr->cross;
		}
		currHead = currHead->right;
		printf("\n");
	}
	printf("\n\n");
}

/* Menampilkan list secara diagonaL menggunakan pointer cross */
void displayListLowerDiagonal(puzzle* board) {
	Node* currHead = board->head->bottom;
	Node* curr = currHead;
	
	printf("\n = = = = = = = =  L I S T  D I A G O N A L  L O W E R  = = = = = = = =\n\n");

	for (int i = 1; i <= board->size; i++){
		curr = currHead;
		while (curr->right != NULL) {
			printf("%c ", curr->data);
			curr = curr->cross;
		}
		currHead = currHead->bottom;
		printf("\n");
	}
	printf("\n\n");
}


int checkHorizontal(Node* node, const char* word) {
    while (*word && node) {
        if (node->data != *word) {
            return 0;
        }
        word++;
        node = node->right;
    }
    return *word == '\0';
}

int checkVertical(Node* node, const char* word) {
    while (*word && node) {
        if (node->data != *word) {
            return 0;
        }
        word++;
        node = node->bottom;
    }
    return *word == '\0';
}

int checkDiagonal(Node* node, const char* word) {
    while (*word && node) {
        if (node->data != *word) {
            return 0;
        }
        word++;
        node = node->cross;
    }
    return *word == '\0';
}

int findWord(puzzle* board, const char* word) {
    Node* row = board->head;
    while (row) {
        Node* current = row;
        while (current) {
            if (checkHorizontal(current, word) || checkVertical(current, word) || checkDiagonal(current, word)) {
                return 1;
            }
            current = current->right;
        }
        row = row->bottom;
    }
    return 0;
}

int main () {
	puzzle board;
	board.head = NULL;
	board.size = 10;
	
	makePuzzle(&board);
	
	displayList(&board);
//	displayListVertikal(&board);
//	displayListUpperDiagonal(&board);
//	displayListLowerDiagonal(&board);
	
	char word[100]; // Asumsikan panjang maksimum kata adalah 99 + null terminator
    printf("Masukkan kata: ");
    scanf("%99s", word); 
    if (findWord(&board, word))  {
        printf("Kata '%s' ditemukan!\n", word);
    } else {
        printf("Kata '%s' tidak ditemukan.\n", word);
    }

}
