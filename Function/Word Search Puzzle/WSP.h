#ifndef WSP_h
#define WSP_h

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

// Konstanta
#define MAX_WORDS 15 // Jumlah maksimal kata
#define MAX_FILENAME_LENGTH 25 // Panjang maksimal nama file
#define MAX_LEADERBOARD_SIZE 10 // Jumlah maksimal pemain dalam leaderboard

// Struktur untuk pemain
typedef struct Player {
    char name[50];
    int correctWord;
    int score;
} Player;

// Struktur untuk Node
typedef struct Node {
    char data;
    Node* right;
    Node* bottom;
    Node* cross;
} Node;

// Struktur untuk puzzle
typedef struct puzzle {
    Node* head;
    int size;
} puzzle;


/*  = = =  Display Functions  = = =  */

/* Fungsi untuk mengatur posisi kursor di konsol
x: Posisi horizontal.
y: Posisi vertikal. */
void gotoxy(int x, int y);

/* Fungsi untuk mendapatkan ukuran konsol
width: Pointer untuk menyimpan lebar konsol.
height: Pointer untuk menyimpan tinggi konsol. */
void getConsoleSize(int *width, int *height);

/* Fungsi untuk mengatur kecepatan dalam game berdasarkan waktu yang diberikan.
seconds: Waktu dalam detik untuk menentukan kecepatan. */
void speed(float seconds);

/* Fungsi untuk menampilkan animasi loading.
Tidak ada parameter yang diperlukan untuk fungsi ini.*/
void loading();

/* Fungsi untuk menampilkan list secara horizontal menggunakan pointer right
board: Pointer ke struktur puzzle yang berisi board. */
void displayList(puzzle* board);

/* Fungsi untuk menampilkan puzzle di konsol
board: Pointer ke struktur puzzle yang berisi board. */
void displayPuzzle(puzzle* board, Player *player);

/* Fungsi untuk menggambar tabel di tengah konsol */
void table();

/* Fungsi untuk menampilkan header di konsol */
void header();

/* Fungsi untuk menampilkan banner theme di konsol */
void BannerTheme();

/* Fungsi untuk menampilkan main menu dan mengembalikan pilihan pengguna */
int displayMainMenu();

/* Fungsi untuk menampilkan menu pilihan tema dan mengembalikan pilihan pengguna */
int displayTheme();



/*  = = =  Node Functions  = = =  */

/* Fungsi untuk mengalokasikan memori untuk node baru dan menginisialisasinya */
Node* allocation();

/* Fungsi untuk menambahkan node ke board
board: Pointer ke struktur puzzle yang berisi board. */
void addNode(puzzle* board);

/* Fungsi untuk mengatur tautan horizontal antar node
board: Pointer ke struktur puzzle yang berisi board. */
void setRightLinks(puzzle* board);

/* Fungsi untuk mengatur tautan vertikal antar node
board: Pointer ke struktur puzzle yang berisi board. */
void setBottomLinks(puzzle* board);

/* Fungsi untuk mengatur tautan diagonal antar node
board: Pointer ke struktur puzzle yang berisi board. */
void setDiagonalLinks(puzzle* board);

/* Fungsi untuk membuat puzzle dengan mengatur semua tautan node
board: Pointer ke struktur puzzle yang berisi board. */
void makePuzzle(puzzle* board);



/* = = =  Word Search Functions = = =  */

/* Fungsi untuk memulai permainan, memperbarui status pemain, dan memperbarui leaderboard.
player: Pointer ke struktur Player yang mewakili pemain saat ini.
leaderboard: Array dari struktur Player yang berisi pemain dalam leaderboard.
leaderboardSize: Pointer ke integer yang menyimpan ukuran leaderboard. */
void playGame(Player *player, Player leaderboard[], int *leaderboardSize);

/* Fungsi untuk mengecek kata secara horizontal dari node awal
node: Pointer ke node awal.
word: Kata yang akan dicari. */
int checkHorizontal(Node* node, const char* word);

/* Fungsi untuk mengecek kata secara vertikal dari node awal
node: Pointer ke node awal.
word: Kata yang akan dicari. */
int checkVertical(Node* node, const char* word);

/* Fungsi untuk mengecek kata secara diagonal dari node awal
node: Pointer ke node awal.
word: Kata yang akan dicari. */
int checkDiagonal(Node* node, const char* word);

/* Fungsi untuk mencari kata di dalam board
board: Pointer ke struktur puzzle yang berisi board.
word: Kata yang akan dicari. */
int findWord(puzzle* board, const char* word);

/* Fungsi untuk mengecek ruang kosong secara horizontal dari node awal
node: Pointer ke node awal.
word: Kata yang akan dimasukkan. */
int checkSpaceHorizontal(Node* node, const char* word);

/* Fungsi untuk mengecek ruang kosong secara vertikal dari node awal
node: Pointer ke node awal.
word: Kata yang akan dimasukkan. */
int checkSpaceVertical(Node* node, const char* word);

/* Fungsi untuk mengecek ruang kosong secara diagonal dari node awal
node: Pointer ke node awal.
word: Kata yang akan dimasukkan. */
int checkSpaceDiagonal(Node* node, const char* word);

/* Fungsi untuk memasukkan kata secara horizontal dari node awal
node: Pointer ke node awal.
word: Kata yang akan dimasukkan. */
void insertWordHorizontal(Node* node, const char* word);

/* Fungsi untuk memasukkan kata secara vertikal dari node awal
node: Pointer ke node awal.
word: Kata yang akan dimasukkan. */
void insertWordVertical(Node* node, const char* word);

/* Fungsi untuk memasukkan kata secara diagonal dari node awal
node: Pointer ke node awal.
word: Kata yang akan dimasukkan. */
void insertWordDiagonal(Node* node, const char* word);

/* Fungsi untuk memasukkan kata secara acak ke dalam board
board: Pointer ke struktur puzzle yang berisi board.
word: Kata yang akan dimasukkan. */
void insertWordRandom(puzzle* board, const char* word);

/* Fungsi untuk mengisi ruang kosong di board dengan huruf acak
board: Pointer ke struktur puzzle yang berisi board. */
void fillEmptySpacesWithRandomLetters(puzzle* board);



/*  = = =  Player and Leaderboard Functions  = = =   */


/* Fungsi untuk menampilkan leaderboard di konsol
leaderboard: Array dari struktur Player yang berisi leaderboard.
leaderboardSize: Jumlah pemain dalam leaderboard. */
void displayLeaderboard(Player leaderboard[], int leaderboardSize);

/* Fungsi untuk mencari kata dalam array kata dan memperbarui skornya
words: Array kata yang dicari.
scores: Array skor yang akan diperbarui.
wordCount: Jumlah kata dalam array words.
target: Kata yang dicari. */
int searchAndUpdateScore(char words[][50], int scores[], int wordCount, char* target);

/* Fungsi untuk menghitung total skor dari semua kata
scores: Array skor kata.
wordCount: Jumlah kata dalam array scores. */
int calculateTotalScore(int scores[], int wordCount);

/* Fungsi untuk menambahkan pemain ke leaderboard
leaderboard: Array dari struktur Player yang berisi leaderboard.
leaderboardSize: Pointer ke jumlah pemain dalam leaderboard.
name: Nama pemain yang akan ditambahkan.
score: Skor pemain yang akan ditambahkan. */
void addToLeaderboard(Player leaderboard[], int* leaderboardSize, char* name, int score);

/* Fungsi untuk menyimpan leaderboard ke file teks
leaderboard: Array dari struktur Player yang berisi leaderboard.
leaderboardSize: Jumlah pemain dalam leaderboard. */
void saveLeaderboard(Player leaderboard[], int leaderboardSize);

/* Fungsi untuk memuat leaderboard dari file teks
leaderboard: Array dari struktur Player yang berisi leaderboard.
leaderboardSize: Pointer ke jumlah pemain dalam leaderboard. */
void loadLeaderboard(Player leaderboard[], int* leaderboardSize);

/* Fungsi untuk meminta nama pemain
playerName: Pointer ke array karakter yang akan menyimpan nama pemain. */
void inputPlayerName(char* playerName);
int displayLanguage();
void displayRulesIndonesian();
void displayRulesEnglish();
void BannerRules();
int mainRules();
void printCentered(char *text, int y) ;

#endif // HEADER_H
