#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    char data;
    struct Node* right;
    struct Node* bottom;
    struct Node* cross;
} Node;

typedef struct puzzle {
    Node* head;
    int size;
} puzzle;

Node* allocation (){
    Node* node = (Node*) malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory Penuh\n");
        exit(EXIT_FAILURE);
    }
    node->data = 'A' + rand() % 26;
    node->right = NULL;
    node->bottom = NULL;
    node->cross = NULL;
    return node;
}

void addNode(puzzle* board, Node* node, int row, int col) {
    if (board->head == NULL) {
        board->head = node;
    } else {
        Node* temp = board->head;
        for (int i = 0; i < row; i++) {
            temp = temp->bottom;
        }
        for (int j = 0; j < col; j++) {
            if (temp->right == NULL) {
                temp->right = node;
                return;
            }
            temp = temp->right;
        }
    }
}

void makePuzzle(puzzle* board) {
    Node* prevRowHead = NULL;
    for (int i = 0; i < board->size; i++) {
        Node* currentRowHead = NULL;
        Node* prevNode = NULL;
        for (int j = 0; j < board->size; j++) {
            Node* node = allocation();
            if (j == 0) {
                currentRowHead = node;
            }
            if (prevNode != NULL) {
                prevNode->right = node;
            }
            if (prevRowHead != NULL) {
                Node* upperNode = prevRowHead;
                for (int k = 0; k < j; k++) {
                    upperNode = upperNode->right;
                }
                upperNode->bottom = node;
            }
            prevNode = node;
        }
        if (i == 0) {
            board->head = currentRowHead;
        }
        prevRowHead = currentRowHead;
    }
}

void displayList(puzzle* board) {
    Node* currentRow = board->head;
    while (currentRow != NULL) {
        Node* current = currentRow;
        while (current != NULL) {
            printf("%c ", current->data);
            current = current->right;
        }
        printf("\n");
        currentRow = currentRow->bottom;
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
    srand(time(0)); // Seed for random number generator
    puzzle board;
    board.head = NULL;
    board.size = 10;
    
    makePuzzle(&board);
    displayList(&board);

    char word[100]; // Asumsikan panjang maksimum kata adalah 99 + null terminator
    printf("Masukkan kata: ");
    scanf("%99s", word); 
    if (findWord(&board, word))  {
        printf("Kata '%s' ditemukan!\n", word);
    } else {
        printf("Kata '%s' tidak ditemukan.\n", word);
    }

    return 0;
}


