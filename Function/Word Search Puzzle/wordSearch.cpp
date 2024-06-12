#include "WSP.h"

// Kamus kata untuk level Easy - Bahasa Indonesia
char easyKamusID[][MAX_FILENAME_LENGTH] = {"Buah", "Hewan", "Negara"};
// Kamus kata untuk level Medium - Bahasa Indonesia
char mediumKamusID[][MAX_FILENAME_LENGTH] = {"Hukum", "Pendidikan", "Benda"};
// Kamus kata untuk level Hard - Bahasa Indonesia
char hardKamusID[][MAX_FILENAME_LENGTH] = {"Sulit"};

// Kamus kata untuk level Easy - Bahasa Inggris
char easyKamusEN[][MAX_FILENAME_LENGTH] = {"Fruit", "Animal", "Country"};
// Kamus kata untuk level Medium - Bahasa Inggris
char mediumKamusEN[][MAX_FILENAME_LENGTH] = {"Law", "Education", "Object"};
// Kamus kata untuk level Hard - Bahasa Inggris
char hardKamusEN[][MAX_FILENAME_LENGTH] = {"Hard"};

/* = = =  Word Search Functions = = =  */

void playGame(Player *player, Player leaderboard[], int *leaderboardSize) {
    // Inisialisasi Struct Puzzle
    puzzle board;
    board.head = NULL;

    // Pilih bahasa
    int languageChoice = displayLanguage();
    char kamusPath[MAX_FILENAME_LENGTH]; // Path untuk kamus kata berdasarkan pilihan bahasa
    switch (languageChoice) {
        case 1:
            strcpy(kamusPath, "Kamus/EN/"); // Untuk bahasa Inggris
            break;
        case 2:
            strcpy(kamusPath, "Kamus/ID/"); // Untuk bahasa Indonesia
            break;
        default:
            printf("Invalid choice.\n");
            return; // Keluar dari fungsi playGame
    }

    // Pilih tema
    int themeChoice = displayTheme();
    char (*selectedKamus)[MAX_FILENAME_LENGTH]; // Pointer untuk memilih kamus kata berdasarkan tingkat kesulitan
    int kamusSize; // Ukuran kamus kata yang dipilih

    // Memilih kamus kata berdasarkan tingkat kesulitan yang dipilih
    switch (themeChoice) {
        case 1:
            if (languageChoice == 1)
                selectedKamus = easyKamusEN;
            else
                selectedKamus = easyKamusID;
            kamusSize = sizeof(easyKamusEN) / sizeof(easyKamusEN[0]);
            board.size = 8;
            break;
        case 2:
            if (languageChoice == 1)
                selectedKamus = mediumKamusEN;
            else
                selectedKamus = mediumKamusID;
            kamusSize = sizeof(mediumKamusEN) / sizeof(mediumKamusEN[0]);
            board.size = 10;
            break;
        case 3:
            if (languageChoice == 1)
                selectedKamus = hardKamusEN;
            else
                selectedKamus = hardKamusID;
            kamusSize = sizeof(hardKamusEN) / sizeof(hardKamusEN[0]);
            board.size = 12;
            break;
        default:
            printf("Invalid choice.\n");
            return; // Keluar dari fungsi playGame
    }
	
	loading();
    system("cls");
	table();
	int x = 50;
	int y = 19; // Mulai dari baris ke-19
	BannerTheme();
	for (int i = 0; i < kamusSize; ++i) {
	    char buffer[50];
	    sprintf(buffer, "%d. %s", i + 1, selectedKamus[i]);
	    printCentered(buffer, y); // Mencetak nomor dan kata dengan rata tengah
	    y++; // Pindah ke baris berikutnya
	}
	printCentered("Your Choice: ", 18);
	int choice;
	scanf("%d", &choice);

    // Validasi pilihan tema
    if (choice < 1 || choice > kamusSize) {
        printf("Invalid theme choice.\n");
    }

    // Memuat tema dari file
    char filename[MAX_FILENAME_LENGTH]; // Nama file tema yang dipilih
    sprintf(filename, "%s/%s.txt", kamusPath, selectedKamus[choice - 1]);
    FILE *file;
    // Membuka file
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("\n\n\n\tFailed to open the file.\n");
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


    makePuzzle(&board);

    if (board.size <= 10){
        for (int i = 0; i < 5; i++) {
            insertWordRandom(&board, searchWord[i]);
        }
    } else {
        for (int i = 0; i < 5; i++) {
            insertWordRandom(&board, searchWord[i]);
        }
    }

    fillEmptySpacesWithRandomLetters(&board);

    // Loop untuk mencari kata-kata
    player->score = 0; // Inisialisasi total skor
    player->correctWord = 0; // Inisialisasi jumlah kata yang benar
    while (player->correctWord < 5) { // Loop berakhir setelah lima kata yang benar dimasukkan
        // Mencari kata yang dimasukkan oleh pengguna dalam array kata
        displayPuzzle(&board, &*player);

        char input_word[50];
        char findedWord[5][50];
        
	    int consoleWidth, consoleHeight;
	    getConsoleSize(&consoleWidth, &consoleHeight);
		
	    int boxWidth = 4; // Lebar setiap kotak (termasuk garis vertikal)
	    int boxHeight = 2; // Tinggi setiap kotak (termasuk garis horizontal)
	    int size = board.size; 
	
	    // Hitung offset untuk menempatkan papan di tengah konsol
	    int offsetX = (consoleWidth - (size * boxWidth)) / 2;
	    int offsetY = (consoleHeight - (size * boxHeight)) / 2;
	    int lastpuzzle = offsetY + size * boxHeight;

        // Menampilkan teks di tengah konsol
        gotoxy(offsetX + size * boxHeight / 2 - 4, lastpuzzle+2);
    	printf("Input Word : ");

        scanf("%s", input_word);
        int found = 0;

        // Keluar dari loop jika pengguna mengetik "q"
        if (strcmp(input_word, "Q") == 0)
            break;
		
		int titlePosX;
        // Mencari kata dalam array kata dan memperbarui skor
        int k = 0;
        if ((searchAndUpdateScore(words, scores, wordCount, input_word)) && (findWord(&board, input_word))) {
            for (int i = 0; i < 5; i++) {
                if (strcmp(input_word, findedWord[i]) == 0) {
                    printCentered("You have found it O_O", lastpuzzle + 4);
                    getch();
                    found = 1;
                }
            }
            if (!found) {
            	printCentered("AWESOME ^^", lastpuzzle + 4);
                getch();

                player->correctWord++; // Menambahkan jumlah kata yang benar
                player->score =  player->score + 100; // Menambahkan skor jika kata ditemukan
                strcpy(findedWord[k], input_word);
                k++;
            }
        } else {
        	printCentered("TRY AGAIN O_O", lastpuzzle + 4);
        	getch();
		}
    }

    int totalScore = player->score;
    // Menambahkan pemain ke leaderboard
    addToLeaderboard(leaderboard, leaderboardSize, player->name, totalScore);
}


/* Fungsi untuk mengecek kata secara horizontal dari node awal
node: Pointer ke node awal.
word: Kata yang akan dicari. */
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

/* Fungsi untuk mengecek kata secara vertikal dari node awal
node: Pointer ke node awal.
word: Kata yang akan dicari. */
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

/* Fungsi untuk mengecek kata secara diagonal dari node awal
node: Pointer ke node awal.
word: Kata yang akan dicari. */
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

/* Fungsi untuk mencari kata di dalam board
board: Pointer ke struktur puzzle yang berisi board.
word: Kata yang akan dicari. */
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

/* Fungsi untuk mengecek ruang kosong secara horizontal dari node awal
node: Pointer ke node awal.
word: Kata yang akan dimasukkan. */
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

/* Fungsi untuk mengecek ruang kosong secara vertikal dari node awal
node: Pointer ke node awal.
word: Kata yang akan dimasukkan. */
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

/* Fungsi untuk mengecek ruang kosong secara diagonal dari node awal
node: Pointer ke node awal.
word: Kata yang akan dimasukkan. */
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

/* Fungsi untuk memasukkan kata secara horizontal dari node awal
node: Pointer ke node awal.
word: Kata yang akan dimasukkan. */
void insertWordHorizontal(Node* node, const char* word) {
    while (*word && node) {
        node->data = *word;
        word++;
        node = node->right;
    }
}

/* Fungsi untuk memasukkan kata secara vertikal dari node awal
node: Pointer ke node awal.
word: Kata yang akan dimasukkan. */
void insertWordVertical(Node* node, const char* word) {
    while (*word && node) {
        node->data = *word;
        word++;
        node = node->bottom;
    }
}

/* Fungsi untuk memasukkan kata secara diagonal dari node awal
node: Pointer ke node awal.
word: Kata yang akan dimasukkan. */
void insertWordDiagonal(Node* node, const char* word) {
    while (*word && node) {
        node->data = *word;
        word++;
        node = node->cross;
    }
}

/* Fungsi untuk memasukkan kata secara acak ke dalam board
board: Pointer ke struktur puzzle yang berisi board.
word: Kata yang akan dimasukkan. */
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

/* Fungsi untuk mengisi ruang kosong di board dengan huruf acak
board: Pointer ke struktur puzzle yang berisi board. */
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

