#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

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
	
	node->data = NULL;
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
	
	currHead = board->head;
	curr = currHead;

	for (int i = 1; i <= board->size; i++){
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

void makePuzzle (puzzle* board) {
	setRightLinks(*&board);
	setBottomLinks(*&board);
	setDiagonalLinks(*&board);
	
}

/* Menampilkan list secara Horizontal menggunakan pointer right */
void displayList(puzzle* board) {
	Node* currHead = board->head;
	Node* curr = currHead;
	
	printf("\n = = = = = = = = B O A R D  = = = = = = = =\n ");
	printf("\n");
	for (int i = 1; i <= board->size; i++){
		curr = currHead;
		for (int j = 1; j <= board->size; j++){
			printf("%c ", curr->data);
			curr = curr->right;
		}
		currHead = currHead->bottom;
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

int checkSpaceHorizontal(Node* node, const char* word) {
    while (*word && node) {
        if (node->data != '\0') {
            return 0;
        }
        word++;
        node = node->right;
    }
    return *word == '\0';
}

int checkSpaceVertical(Node* node, const char* word) {
    while (*word && node) {
        if (node->data != '\0') {
            return 0;
        }
        word++;
        node = node->bottom;
    }
    return *word == '\0';
}

int checkSpaceDiagonal(Node* node, const char* word) {
    while (*word && node) {
        if (node->data != '\0') {
            return 0;
        }
        word++;
        node = node->cross;
    }
    return *word == '\0';
}

void insertWordHorizontal(Node* node, const char* word) {
    while (*word && node) {
        node->data = *word;
        word++;
        node = node->right;
    }
}


void insertWordVertical(Node* node, const char* word) {
    while (*word && node) {
        node->data = *word;
        word++;
        node = node->bottom;
    }
}

void insertWordDiagonal(Node* node, const char* word) {
    while (*word && node) {
        node->data = *word;
        word++;
        node = node->cross;
    }
}

void insertWordRandom(puzzle* board, const char* word) {
    int row, col;
    Node* node;
	int direction;
    do {
        row = rand() % (board->size - strlen(word) + 1);
        col = rand() % (board->size - strlen(word) + 1);
        direction = ((rand() * rand()) * row) % 3;
        node = board->head;
        for (int i = 0; i < row; i++) {
            node = node->bottom;
        }
        for (int j = 0; j < col; j++) {
            node = node->right;
        }
    } while ((direction == 0 && !checkSpaceHorizontal(node, word)) ||
             (direction == 1 && !checkSpaceVertical(node, word)) ||
             (direction == 2 && !checkSpaceDiagonal(node, word)));

    if (direction == 0) {
        insertWordHorizontal(node, word);
    } else if (direction == 1) {
        insertWordVertical(node, word);
    } else {
        insertWordDiagonal(node, word);
    }
}

void fillEmptySpacesWithRandomLetters(puzzle* board) {
    Node* currHead = board->head;
    Node* curr = currHead;
    for (int i = 0; i < board->size; i++) {
        curr = currHead;
        for (int j = 0; j < board->size; j++) {
            if (curr->data == '\0') {
                curr->data = 'A' + rand() % 26; // Mengisi dengan huruf acak dari 'A' hingga 'Z'
            }
            curr = curr->right;
        }
        currHead = currHead->bottom;
    }
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
    bool find = false;
    for (int i = 0; i < board->size; i++){
        Node* current = row;
        while (current) {
            if (checkHorizontal(current, word) || checkVertical(current, word) || checkDiagonal(current, word)) {
            	find = true;
                return find;
            }
            current = current->right;
        }
        row = row->bottom;
    }
    return find;
}

int main () {
	system ("color FD");
	puzzle board;
	board.head = NULL;
	board.size = 10;
	
	makePuzzle(&board);
	const char* words[5] = {"ZAHRA", "MATEMATIKA", "WORLD", "CROSS", "SALWA"};
    for (int i = 0; i < 5; i++) {
        insertWordRandom(&board, words[i]);
    }
    fillEmptySpacesWithRandomLetters(&board);
	
	displayList(&board);
	
	
	char word[100]; // Asumsikan panjang maksimum kata adalah 99 + null terminator
    printf("Masukkan kata: ");
    scanf("%99s", word); 
    if (findWord(&board, word)) {
        printf("Kata '%s' ditemukan!\n", word);
    } else {
        printf("Kata '%s' tidak ditemukan.\n", word);
    }
}
