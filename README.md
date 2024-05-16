# Word Search Puzzle Implementation using Multi-Linked Lists

This project is a part of the assignment for the Data Structures and Algorithms course in the Diploma IV Program of Informatics Engineering, Department of Computer Engineering and Informatics, at Bandung State Polytechnic. 

## Contributors
- Fitri Salwa (NIM: 231524009)
- Zahra Hilyatul Jannah (NIM: 231425031)

## Introduction
Word Search Puzzle is a game where a number of words are hidden and randomly placed within a grid of letters. These words can be placed horizontally, vertically, or diagonally. The objective of this puzzle is to find and mark all the hidden words on the board.

## Program Specification

### 1. Description of the Program
#### 1.1 Program Definition
Word Search Puzzle, or word search, is a game where words are hidden within a grid of letters. These words can be placed horizontally, vertically, or diagonally. The goal of this puzzle is to find and mark all the hidden words on the board.

#### 1.2 Data Structure
The data structure used in this implementation is the multi-linked list. A multi-linked list is a variation of a linked list where each node has more than one pointer pointing to other nodes. In the Word Search Puzzle application, each node in the multi-linked list represents a letter in the grid, while the pointers on the node point to neighboring nodes in the grid (horizontal, vertical, and diagonal). Below is an illustration of the multi-linked list structure used in the Word Search Puzzle application.


The programming language used in the development of this application is C. Below is an example implementation of the data structure in C that we will use.

```c
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

```

By using the multi-linked list data structure, we can efficiently represent a grid of characters and perform word searches within that grid. This allows for the creation of an interactive and enjoyable Word Search Puzzle application for users.
