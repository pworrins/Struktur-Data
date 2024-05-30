#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
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

// Fungsi untuk menggerakkan cursor ke posisi tertentu di konsol
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Fungsi untuk mendapatkan ukuran konsol
void getConsoleSize(int *width, int *height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    *width = columns;
    *height = rows;
}

void displayPuzzle(puzzle* board){
	Node* currHead = board->head;
	Node* curr = currHead;
	
	gotoxy(27, 1); 
	for (int i = 0; i < 8; i++){	
		printf("%c ", 175);
	}
	printf(" W O R D   S E A R C H   P U Z Z L E ");
	for (int i = 0; i < 8; i++){	
		printf("%c ", 174);
	}
	
    int consoleWidth, consoleHeight;
    getConsoleSize(&consoleWidth, &consoleHeight);

    int boxWidth = 4; // Lebar setiap kotak (termasuk garis vertikal)
    int boxHeight = 2; // Tinggi setiap kotak (termasuk garis horizontal)
    int size = board->size; // Ukuran papan 10x10

    // Hitung offset untuk menempatkan papan di tengah konsol
    int offsetX = (consoleWidth - (size * boxWidth)) / 2;
    int offsetY = (consoleHeight - (size * boxHeight)) / 2;

    int i, j, k;

    // Membuat papan dengan kotak 10x10
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            gotoxy(offsetX + boxWidth * j, offsetY + boxHeight * i);
            if (i < size) {
                // Garis horizontal
                printf("%c", 197); // Titik persilangan
                for (k = 1; k < boxWidth; k++) {
                    gotoxy(offsetX + boxWidth * j + k, offsetY + boxHeight * i);
                    printf("%c", 196); // Garis horizontal
                }
            }

            if (j < size) {
                // Garis vertikal
                for (k = 1; k < boxHeight; k++) {
                    gotoxy(offsetX + boxWidth * j, offsetY + boxHeight * i + k);
                    printf("%c", 179); // Garis vertikal
                }
            }

            if (i < size && j < size) {
                // Huruf di dalam kotak
                gotoxy(offsetX + boxWidth * j + 1, offsetY + boxHeight * i + 1); // Menyesuaikan posisi huruf di dalam kotak
                printf(" %c", curr->data);
                if (curr->right != NULL){
					curr = curr->right;            	
				} else {
					curr = currHead->bottom;
					currHead = currHead->bottom;
				}
            }
        }
    }

    // Membuat garis tepi kanan dan bawah papan
    for (i = 0; i <= size * boxHeight; i++) {
        gotoxy(offsetX + size * boxWidth, offsetY + i);
        printf("%c", 186); // Garis vertikal tepi kanan
    }
    for (i = 0; i <= size * boxWidth; i++) {
        gotoxy(offsetX + i, offsetY + size * boxHeight);
        printf("%c", 205); // Garis horizontal tepi bawah
    }

    // Membuat garis tepi kiri dan atas papan
    for (i = 0; i <= size * boxHeight; i++) {
        gotoxy(offsetX, offsetY + i);
        printf("%c", 186); // Garis vertikal tepi kiri
    }
    for (i = 0; i <= size * boxWidth; i++) {
        gotoxy(offsetX + i, offsetY);
        printf("%c", 205); // Garis horizontal tepi atas
    }

    // Membuat sudut-sudut papan
    gotoxy(offsetX, offsetY);
    printf("%c", 201); // Sudut kiri atas
    gotoxy(offsetX + size * boxWidth, offsetY);
    printf("%c", 187); // Sudut kanan atas
    gotoxy(offsetX, offsetY + size * boxHeight);
    printf("%c", 200); // Sudut kiri bawah
    gotoxy(offsetX + size * boxWidth, offsetY + size * boxHeight);
    printf("%c", 188); // Sudut kanan bawah
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
    srand((unsigned int)time(NULL));
	do {
        row = rand() % (board->size);
        col = rand() % (board->size - strlen(word) + 1);
        direction = ((rand()) * row) % 3;
        node = board->head;
        for (int i = 0; i < row; i++) {
            node = node->bottom;
        }
        for (int j = 0; j < col; j++) {
            node = node->right;
        }
    } while ((direction == 0 && !checkSpaceVertical (node, word)) ||
             (direction == 1 && !checkSpaceDiagonal (node, word)) ||
             (direction == 2 && !checkSpaceHorizontal(node, word)));

    if (direction == 0) {
        insertWordVertical (node, word);
    } else if (direction == 1) {
        insertWordDiagonal (node, word);
    } else {
        insertWordHorizontal(node, word);
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
	system("color 70");
	system ("color FD");
	puzzle board;
	board.head = NULL;
	board.size = 13;
	
	makePuzzle(&board);
	const char* words[5] = {"matematika", "hilyah", "salwa", "fitri", "yaya"};
    for (int i = 0; i < 5; i++) {
        insertWordRandom(&board, words[i]);
    }
    fillEmptySpacesWithRandomLetters(&board);
	
	displayPuzzle(&board);
	
	char word[100]; // Asumsikan panjang maksimum kata adalah 99 + null terminator
    gotoxy(40, 29); printf("Masukkan kata: ");
    scanf("%99s", word); 
    if (findWord(&board, word)) {
        printf("Kata '%s' ditemukan!\n", word);
    } else {
        printf("Kata '%s' tidak ditemukan.\n", word);
    }
}
