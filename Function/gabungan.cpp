#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define MAX_WORDS 15 // Jumlah maksimal kata
#define MAX_FILENAME_LENGTH 25 // Panjang maksimal nama file
#define MAX_LEADERBOARD_SIZE 10 // Jumlah maksimal pemain dalam leaderboard

// Struktur untuk pemain
typedef struct Player {
    char name[50];
    int score;
} Player;

//Stuktur untuk Node
typedef struct Node {
	char data;
    Node* right;
    Node* bottom;
    Node* cross;
} Node;

//Struktur untuk puzzle
typedef struct puzzle {
	Node* head;
	int size;
} puzzle;

// Kamus kata untuk level Easy
char easyKamus[][MAX_FILENAME_LENGTH] = {"buah", "hewan", "negara"};
// Kamus kata untuk level Medium
char mediumKamus[][MAX_FILENAME_LENGTH] = {"hukum", "pendidikan", "benda"};
// Kamus kata untuk level Hard
char hardKamus[][MAX_FILENAME_LENGTH] = {"hard_kamus"};



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

// Fungsi untuk mencari kata dalam array kata dan memperbarui skornya
int searchAndUpdateScore(char words[][50], int scores[], int wordCount, char* target) {
    for (int i = 0; i < wordCount; ++i) {
        if (strcmp(words[i], target) == 0) {
            // Kata ditemukan, tambahkan skor
            scores[i]++;
            return 1; // Mengembalikan 1 jika kata ditemukan
        }
    }
    return 0; // Mengembalikan 0 jika kata tidak ditemukan
}

// Fungsi untuk menghitung total skor dari semua kata
int calculateTotalScore(int scores[], int wordCount) {
    int totalScore = 0;
    for (int i = 0; i < wordCount; ++i) {
        totalScore += scores[i];
    }
    return totalScore;
}

// Fungsi untuk menambahkan pemain ke leaderboard
void addToLeaderboard(Player leaderboard[], int* leaderboardSize, char* name, int score) {
    // Cek apakah pemain sudah ada di leaderboard
    for (int i = 0; i < *leaderboardSize; ++i) {
        if (strcmp(leaderboard[i].name, name) == 0) {
            // Update skor jika pemain sudah ada
            leaderboard[i].score += score;
            return;
        }
    }
    // Jika pemain belum ada, tambahkan ke leaderboard
    if (*leaderboardSize < MAX_LEADERBOARD_SIZE) {
        strcpy(leaderboard[*leaderboardSize].name, name);
        leaderboard[*leaderboardSize].score = score;
        (*leaderboardSize)++;
    } else {
        // Jika leaderboard penuh, gantikan pemain dengan skor terendah jika perlu
        int minIndex = 0;
        for (int i = 1; i < MAX_LEADERBOARD_SIZE; ++i) {
            if (leaderboard[i].score < leaderboard[minIndex].score) {
                minIndex = i;
            }
        }
        if (score > leaderboard[minIndex].score) {
            strcpy(leaderboard[minIndex].name, name);
            leaderboard[minIndex].score = score;
        }
    }
    // Urutkan leaderboard berdasarkan skor
    for (int i = 0; i < *leaderboardSize - 1; ++i) {
        for (int j = i + 1; j < *leaderboardSize; ++j) {
            if (leaderboard[j].score > leaderboard[i].score) {
                Player temp = leaderboard[i];
                leaderboard[i] = leaderboard[j];
                leaderboard[j] = temp;
            }
        }
    }
}

// Fungsi untuk menampilkan leaderboard
void displayLeaderboard(Player leaderboard[], int leaderboardSize) {
    system("cls"); // Membersihkan layar sebelum menampilkan leaderboard
    printf(" _                    _           _                         _ \n");
    printf("| |                  | |         | |                       | |\n");
    printf("| |     ___  __ _  __| | ___ _ __| |__   ___   __ _ _ __ __| |\n");
    printf("| |    / _ \\/ _` |/ _` |/ _ \\ '__| '_ \\ / _ \\ / _` | '__/ _` |\n");
    printf("| |___|  __/ (_| | (_| |  __/ |  | |_) | (_) | (_| | | | (_| |\n");
    printf("\\_____/\\___|\\__,_|\\__,_|\\___|_|  |_.__/ \\___/ \\__,_|_|  \\__,_|\n");
    printf("                                                               \n");
    printf("                                                               \n");
    for (int i = 0; i < leaderboardSize; ++i) {
        printf("%d. %s - %d\n", i + 1, leaderboard[i].name, leaderboard[i].score);
    }
    printf("=======================\n\n");
}
// Fungsi untuk menggambar tabel di tengah konsol
void table() {
    system("cls");

    int tableWidth = 65; // Lebar tabel
    int tableHeight = 13; // Tinggi tabel pertama
    int consoleWidth, consoleHeight;

    getConsoleSize(&consoleWidth, &consoleHeight);

    // Hitung offset untuk menempatkan tabel di tengah konsol
    int offsetX = (consoleWidth - tableWidth) / 2;
    int offsetY = (consoleHeight - 2 * tableHeight) / 2;

    // Membuat kotak pertama (atas)
    // Garis atas
    gotoxy(offsetX, offsetY); printf("%c", 201);
    for (int i = 1; i < tableWidth - 1; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 187);

    // Garis samping dan isi kotak pertama
    for (int i = 1; i < tableHeight; i++) {
        gotoxy(offsetX, offsetY + i); printf("%c", 186);
        gotoxy(offsetX + tableWidth - 1, offsetY + i); printf("%c", 186);
    }

    // Garis bawah kotak pertama (bagian atas kotak kedua)
    gotoxy(offsetX, offsetY + tableHeight); printf("%c", 204);
    for (int i = 1; i < tableWidth - 1; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 185);

    // Membuat kotak kedua (bawah)
    // Garis samping kotak kedua
    tableHeight = 10;
    for (int i = 1; i < tableHeight; i++) {
        gotoxy(offsetX, offsetY + tableHeight + i); printf("%c", 186);
        gotoxy(offsetX + tableWidth - 1, offsetY + tableHeight + i); printf("%c", 186);
    }

    // Garis bawah kotak kedua
    gotoxy(offsetX, offsetY + 2 * tableHeight); printf("%c", 200);
    for (int i = 1; i < tableWidth - 1; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 188);
}

// Fungsi untuk menyimpan leaderboard ke file teks
void saveLeaderboard(Player leaderboard[], int leaderboardSize) {
    FILE *file = fopen("Kamus/leaderboard.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file leaderboard.\n");
        return;
    }
    for (int i = 0; i < leaderboardSize; ++i) {
        fprintf(file, "%s %d\n", leaderboard[i].name, leaderboard[i].score);
    }
    fclose(file);
}

// Fungsi untuk memuat leaderboard dari file teks
void loadLeaderboard(Player leaderboard[], int* leaderboardSize) {
    FILE *file = fopen("Kamus/leaderboard.txt", "r");
    if (file == NULL) {
        printf("File leaderboard tidak ditemukan, leaderboard kosong.\n");
        return;
    }
    while (*leaderboardSize < MAX_LEADERBOARD_SIZE && fscanf(file, "%s %d", leaderboard[*leaderboardSize].name, &leaderboard[*leaderboardSize].score) == 2) {
        (*leaderboardSize)++;
    }
    fclose(file);
}

// Fungsi untuk meminta nama pemain
void inputPlayerName(char* playerName) {
    int x = 48;
    gotoxy(x, 17); printf("Welcome To Game !!!\n");
    gotoxy(x, 18); printf("====================\n");
    gotoxy(x, 19); printf("Masukkan Nama Anda :\n");
    gotoxy(x, 20); scanf("%s", playerName);
}

// Fungsi untuk menampilkan main menu
int displayMainMenu() {
	table();
	int x = 35;
	int y = 48;
    int choice;
    gotoxy(x, 6);printf("  __  __       _         __  __                  \n");
    gotoxy(x, 7);printf(" |  \\/  |     (_)       |  \\/  |                 \n");
    gotoxy(x, 8);printf(" | \\  / | __ _ _ _ __   | \\  / | ___ _ __  _   _ \n");
    gotoxy(x, 9);printf(" | |\\/| |/ _` | | '_ \\  | |\\/| |/ _ \\ '_ \\| | | |\n");
    gotoxy(x,10);printf(" | |  | | (_| | | | | | | |  | |  __/ | | | |_| |\n");
    gotoxy(x,11);printf(" |_|  |_|\\__,_|_|_| |_| |_|  |_|\\___|_| |_|\\__,_|\n");
    gotoxy(y,17);printf("1. Mulai Permainan\n");
    gotoxy(y,18);printf("2. Tampilkan Leaderboard\n");
    gotoxy(y,19);printf("3. Keluar\n");
    gotoxy(y,20);printf("Pilihan Anda? Masukan Angka !");
    gotoxy(y,21);scanf("%d", &choice);
    return choice;
}

void BannerTheme(){
	int x = 48;
	gotoxy(x, 7);printf(" _____ ________  ___ ___  \n");
    gotoxy(x, 8);printf("|_   _|  ___|  \\/  |/ _ \\ \n");
    gotoxy(x, 9);printf("  | | | |__ | .  . / /_\\ \\\n");
    gotoxy(x,10);printf("  | | |  __|| |\\/| |  _  |\n");
    gotoxy(x,11);printf("  | | | |___| |  | | | | |\n");
    gotoxy(x,12);printf("  \\_/ \\____/\\_|  |_|_| |_/\n");
}
int displayTheme(){
	table();
	int x = 48;
    BannerTheme();
    gotoxy(x, 17);printf("1. Easy\n");
    gotoxy(x, 18);printf("2. Medium\n");
    gotoxy(x, 19);printf("3. Hard\n");
    gotoxy(x, 20);printf("Pilihan Anda: ");
                int levelChoice;
                scanf("%d", &levelChoice);
            	return levelChoice;
}

void header() {
	table();
	int x = 43;
	   gotoxy(x, 3);printf(" __          __           _         \n");
       gotoxy(x, 4);printf(" \\ \\        / /          | |        \n");
       gotoxy(x, 5);printf("  \\ \\  /\\  / /__  _ __ __| |        \n");
       gotoxy(x, 6);printf("   \\ \\/  \\/ / _ \\| '__/ _` |        \n");
       gotoxy(x, 7);printf("    \\  /\\  / (_) | | | (_| |        \n");
       gotoxy(x, 8);printf("    _\\/__\\/ \\___/|_|  \\__,_|  _     \n");
       gotoxy(x, 9);printf("   / ____|                   | |    \n");
       gotoxy(x, 10);printf("  | (___   ___  __ _ _ __ ___| |__  \n");
       gotoxy(x, 11);printf("   \\___ \\ / _ \\/ _` | '__/ __| '_ \\ \n");
       gotoxy(x, 12);printf("   ____) |  __/ (_| | | | (__| | | |\n");
       gotoxy(x, 13);printf("  |_____/ \\___|\\__,_|_|  \\___|_| |_|   \n");
}


void speed(float seconds) {
    clock_t endwait;
    endwait = clock() + seconds * CLOCKS_PER_SEC;
    while (clock() < endwait);
}

void loading() {
	system("cls");
    int x = 42;
    // loading 
    gotoxy(x,14); printf("               Loading");
    gotoxy(x,15); printf("     ===========================");
    gotoxy(x,16); printf("    %c                           %c", 186, 186);
    gotoxy(x,17); printf("     ===========================");
    for (int i = 47; i <= 73; i++) {
        gotoxy(i, 16); printf("\xdb");
        speed(0.07);
    }
}
void playGame(Player *player, Player leaderboard[], int *leaderboardSize) {
    // Pilih tema
    int themeChoice = displayTheme();
    char (*selectedKamus)[MAX_FILENAME_LENGTH]; // Pointer untuk memilih kamus kata berdasarkan tingkat kesulitan
    int kamusSize; // Ukuran kamus kata yang dipilih

    // Memilih kamus kata berdasarkan tingkat kesulitan yang dipilih
    switch (themeChoice) {
        case 1:
            selectedKamus = easyKamus;
            kamusSize = sizeof(easyKamus) / sizeof(easyKamus[0]);
            break;
        case 2:
            selectedKamus = mediumKamus;
            kamusSize = sizeof(mediumKamus) / sizeof(mediumKamus[0]);
            break;
        case 3:
            selectedKamus = hardKamus;
            kamusSize = sizeof(hardKamus) / sizeof(hardKamus[0]);
            break;
        default:
            printf("Pilihan tidak valid.\n");
            return; // Keluar dari fungsi playGame
   			 }
				system("cls");
				table();
  				 // Pilih tema
  				 int x = 45;
                BannerTheme();
                for (int i = 0; i < kamusSize; ++i) {
                   gotoxy(x,17+i);printf("%d. %s\n", i + 1, selectedKamus[i]);
                }
                gotoxy(x,16);printf("Pilihan Anda: ");
                int choice;
                scanf("%d", &choice);

                // Validasi pilihan tema
                if (themeChoice < 1 || themeChoice > kamusSize) {
                    printf("Pilihan tema tidak valid.\n");
                }

                // Memuat tema dari file
                char filename[MAX_FILENAME_LENGTH]; // Nama file tema yang dipilih
                sprintf(filename, "Kamus/%s.txt", selectedKamus[themeChoice - 1]);
				FILE *file;
                // Membuka file
                file = fopen(filename, "r");
                if (file == NULL) {
                    printf("Gagal membuka file.\n");
                }

                // Membaca kata-kata dari file dan menyimpannya dalam array
                char words[MAX_WORDS][50];
                int scores[MAX_WORDS] = {0}; // Array untuk menyimpan skor setiap kata
                int wordCount = 0;
                while (wordCount < MAX_WORDS && fscanf(file, "%49s", words[wordCount]) == 1) {
                    wordCount++;
                }

                // Menutup file
                fclose(file);

                // Mengacak urutan kata-kata dalam array
                srand((unsigned int)time(NULL)); // Menggunakan nilai hash dari waktu saat ini sebagai bibit
                for (int i = wordCount - 1; i > 0; i--) {
                    int j = rand() % (i + 1);
                    if (i != j) {
                        char temp[50];
                        strcpy(temp, words[i]);
                        strcpy(words[i], words[j]);
                        strcpy(words[j], temp);
                    }
                }	
                
                // Menampilkan lima kata yang telah diacak ke dalam array baru
                int numWordsToDisplay = 5; // Jumlah kata yang akan ditampilkan
                char *searchWord[5];
                for (int i = 0; i < numWordsToDisplay && i < wordCount; i++) {
                	searchWord[i] = words[i];
                }
                printf("\n");
			                
			    puzzle board;
				board.head = NULL;
				board.size = 10;
				
				makePuzzle(&board);
				
			    for (int i = 0; i < 5; i++) {
			        insertWordRandom(&board, searchWord[i]);
			    }
			    
			    fillEmptySpacesWithRandomLetters(&board);
				
				displayList(&board);

                // Loop untuk mencari kata-kata
                int totalScore = 0; // Inisialisasi total skor
                int correctWords = 0; // Inisialisasi jumlah kata yang benar
                while (correctWords < 5) { // Loop berakhir setelah lima kata yang benar dimasukkan
                    // Mencari kata yang dimasukkan oleh pengguna dalam array kata
                    char input_word[50];
                    printf("Masukkan kata (tekan 'q' untuk keluar): ");
                    scanf("%s", input_word);

                    // Keluar dari loop jika pengguna mengetik "q"
                    if (strcmp(input_word, "q") == 0)
                        break;

                    // Mencari kata dalam array kata dan memperbarui skor
                    if ((searchAndUpdateScore(words, scores, wordCount, input_word)) && (findWord(&board, input_word))) {
                        totalScore++; // Menambahkan skor jika kata ditemukan
                        correctWords++; // Menambahkan jumlah kata yang benar
                    }
                }

                printf("Total skor: %d\n", totalScore);

                // Menambahkan pemain ke leaderboard
                addToLeaderboard(leaderboard, leaderboardSize, player->name, totalScore);
}

int main() {
    Player leaderboard[MAX_LEADERBOARD_SIZE]; // Leaderboard
    int leaderboardSize = 0; // Ukuran leaderboard
    time_t lastUpdated; // Waktu terakhir leaderboard diperbarui

    // Memuat leaderboard dari file teks
    loadLeaderboard(leaderboard, &leaderboardSize);
    system("color F0");
    header();
    // Meminta nama pemain
    Player player;
    inputPlayerName(player.name);
    loading();
    player.score = 0;
    system("cls");
    // Main loop
    int choice;
    do {
        choice = displayMainMenu();
        loading();
        switch (choice) {
            case 1: {
                system("cls"); // Membersihkan layar sebelum memulai permainan
                playGame(&player, leaderboard, &leaderboardSize); // Memulai permainan
            }
            case 2:
                // Menampilkan leaderboard
                displayLeaderboard(leaderboard, leaderboardSize);
                system("pause");
                break;

            case 3:
                // Keluar dari program
                // Menyimpan leaderboard ke file teks
                saveLeaderboard(leaderboard, leaderboardSize);

                // Menyimpan waktu terakhir leaderboard diperbarui
                time(&lastUpdated);
                printf("Leaderboard terakhir diperbarui pada: %s\n", ctime(&lastUpdated));
                break;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}

