#include "WSP.h"

/*  = = =  Display Functions  = = =  */

/* Fungsi untuk mengatur posisi kursor di konsol
x: Posisi horizontal.
y: Posisi vertikal. */
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/* Fungsi untuk mendapatkan ukuran konsol
width: Pointer untuk menyimpan lebar konsol.
height: Pointer untuk menyimpan tinggi konsol. */
void getConsoleSize(int *width, int *height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    *width = columns;
    *height = rows;
}

void printCentered(char *text, int y) {
    int consoleWidth, consoleHeight;
    getConsoleSize(&consoleWidth, &consoleHeight);

    // Hitung posisi horizontal untuk teks
    int posX = (consoleWidth - strlen(text)) / 2;

    // Menampilkan teks di tengah konsol
    gotoxy(posX, y);
    printf("%s", text);
}

void speed(float seconds) {
    clock_t endwait;
    endwait = clock() + seconds * CLOCKS_PER_SEC;
    while (clock() < endwait);
}

void loading() {
	system("cls");
    // loading 
    printCentered("Loading", 14);
    printCentered("===========================", 15);
    printCentered("|                           |", 16);
    printCentered("===========================", 17);
    
    int consoleWidth, consoleHeight;
    getConsoleSize(&consoleWidth, &consoleHeight);

    int startPos = ((consoleWidth - 30) / 2) + 1; // Menghitung posisi awal loop
    int endPos = startPos + 26; // Menghitung posisi akhir loop

    for (int i = startPos; i <= endPos; i++) {
        gotoxy(i, 16);
        printf("\xdb");
        Sleep(100); // Waktu jeda (ms)
    }
}

/* Fungsi untuk menggambar tabel di tengah konsol */
void table() {
    system("cls");

    int tableWidth = 65; // Lebar tabel
    int tableHeight = 13; // Tinggi tabel pertama
    int consoleWidth, consoleHeight;

    getConsoleSize(&consoleWidth, &consoleHeight);

    // Hitung offset untuk menempatkan tabel di tengah konsol secara horizontal
    int offsetX = (consoleWidth - tableWidth) / 2;
    int offsetY = 3; // Posisi vertikal tetap (misalnya, 3 baris dari atas)

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

/* Fungsi untuk menampilkan header di konsol */
void header() {
    table();
    printCentered(" __          __           _         \n", 4);
    printCentered(" \\ \\        / /          | |        \n", 5);
    printCentered("  \\ \\  /\\  / /__  _ __ __| |        \n", 6);
    printCentered("   \\ \\/  \\/ / _ \\| '__/ _` |        \n", 7);
    printCentered("    \\  /\\  / (_) | | | (_| |        \n", 8);
    printCentered("    _\\/__\\/ \\___/|_|  \\__,_|  _     \n", 9);
    printCentered("   / ____|                   | |    \n", 10);
    printCentered("  | (___   ___  __ _ _ __ ___| |__  \n", 11);
    printCentered("   \\___ \\ / _ \\/ _` | '__/ __| '_ \\ \n", 12);
    printCentered("   ____) |  __/ (_| | | | (__| | | |\n", 13);
    printCentered("  |_____/ \\___|\\__,_|_|  \\___|_| |_|\n", 14);
}


/* Fungsi untuk meminta nama pemain */
void inputPlayerName(char* playerName) {
    int x = 48;
    gotoxy(40, 17); printf("WELCOME TO WORD SEARCH PUZZLE GAME ");
    gotoxy(x, 19); printf("Input your name: ");
    scanf("%s", playerName);
}

/* Fungsi untuk menampilkan banner theme di konsol */
void BannerTheme(){
    printCentered(" _____ _                         \n", 7);
    printCentered("|_   _| |                        \n", 8);
    printCentered("  | | | |__   ___ _ __ ___   ___ \n", 9);
    printCentered("  | | | '_ \\ / _ \\ '_ ` _ \\ / _ \\\n", 10);
    printCentered("  | | | | | |  __/ | | | | |  __/\n", 11);
    printCentered("  \\_/ |_| |_|\\___|_| |_| |_|\\___|\n", 12);
    printCentered("                                 \n", 13);
}


/* Fungsi untuk menampilkan main menu dan mengembalikan pilihan pengguna */
int displayMainMenu() {
	table();

    int choice;
    printCentered("  __  __       _         __  __                  \n", 6);
    printCentered(" |  \\/  |     (_)       |  \\/  |                 \n", 7);
    printCentered(" | \\  / | __ _ _ _ __   | \\  / | ___ _ __  _   _ \n", 8);
    printCentered(" | |\\/| |/ _` | | '_ \\  | |\\/| |/ _ \\ '_ \\| | | |\n", 9);
    printCentered(" | |  | | (_| | | | | | | |  | |  __/ | | | |_| |\n", 10);
    printCentered(" |_|  |_|\\__,_|_|_| |_| |_|  |_|\\___|_| |_|\\__,_|\n", 11);
    printCentered("1. Start\n", 18);
    printCentered("2. Leaderboard\n", 19);
    printCentered("3. Rules\n", 20);
    printCentered("4. Quit", 21);
    printCentered("Your Input: ", 17);
    scanf("%d", &choice);
    return choice;
}

/* Fungsi untuk menampilkan menu pilihan tema dan mengembalikan pilihan pengguna */
int displayTheme(){
    table();
    BannerTheme();
    printCentered("1. Easy\n", 19);
    printCentered("2. Medium\n", 20);
    printCentered("3. Hard\n", 21);
    printCentered("Your Input: ", 18);

    int levelChoice;
    scanf("%d", &levelChoice);
    return levelChoice;
}

/* Fungsi untuk menampilkan menu pilihan Bahasa dan mengembalikan pilihan pengguna */
int displayLanguage(){
    table();
    BannerTheme();
    printCentered("1. English\n", 19);
    printCentered("2. Indonesia\n", 20);
    printCentered("Your Input: ", 18);

    int LanguageChoice;
    scanf("%d", &LanguageChoice);
    return LanguageChoice;
} 

/* Fungsi untuk menampilkan list secara horizontal menggunakan pointer right
board: Pointer ke struktur puzzle yang berisi board. */
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

/* Fungsi untuk menampilkan puzzle di konsol
board: Pointer ke struktur puzzle yang berisi board. */
void displayPuzzle(puzzle* board, Player *player){
	system("cls");
	Node* currHead = board->head;
	Node* curr = currHead;
	
    int consoleWidth, consoleHeight;
    getConsoleSize(&consoleWidth, &consoleHeight);
	
    int boxWidth = 4; // Lebar setiap kotak (termasuk garis vertikal)
    int boxHeight = 2; // Tinggi setiap kotak (termasuk garis horizontal)
    int size = board->size; 

    // Hitung offset untuk menempatkan papan di tengah konsol
    int offsetX = (consoleWidth - (size * boxWidth)) / 2;
    int offsetY = (consoleHeight - (size * boxHeight)) / 2;
	
	char puzzleTitle[] = " W O R D   S E A R C H   P U Z Z L E ";

	// Hitung posisi horizontal untuk teks
	int titlePosX = (consoleWidth - strlen(puzzleTitle)) / 2;
	
	// Menampilkan teks di tengah konsol
	gotoxy(titlePosX, offsetY-2);
	printf("%s", puzzleTitle);
	
	gotoxy(offsetX + size * boxWidth + 3, offsetY+1);
    printf("%s's game ^^", player->name);
    gotoxy(offsetX + size * boxWidth + 3, offsetY+3);
    printf("You found %d words", player->correctWord);
    gotoxy(offsetX + size * boxWidth + 3, offsetY+4);
    printf("Total Score: %d", player->score);
    
    gotoxy(offsetX + size * boxWidth + 3, offsetY+7);
    printf("Press 'Q' to quit the game");

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

