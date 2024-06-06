#include "WSP.h"

// Kamus kata untuk level Easy
char easyKamus[][MAX_FILENAME_LENGTH] = {"buah", "hewan", "negara"};
// Kamus kata untuk level Medium
char mediumKamus[][MAX_FILENAME_LENGTH] = {"hukum", "pendidikan", "benda"};
// Kamus kata untuk level Hard
char hardKamus[][MAX_FILENAME_LENGTH] = {"hard_kamus"};

/* = = =  Word Search Functions = = =  */

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
  				int x = 50;
                BannerTheme();
                for (int i = 0; i < kamusSize; ++i) {
                   gotoxy(x, 18+i);printf("%d. %s\n", i + 1, selectedKamus[i]);
                }
                gotoxy(x,17);printf("Pilihan Anda: ");
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
				board.size = 13;
				
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
                    char inputWord[] = "Input Word : ";
					
					int consoleWidth, consoleHeight;
    				getConsoleSize(&consoleWidth, &consoleHeight);
					// Hitung posisi horizontal untuk teks
					int titlePosX = ((consoleWidth - strlen(inputWord)) / 2) - 8;
					
					// Menampilkan teks di tengah konsol
					gotoxy(titlePosX, consoleHeight - 2);
					printf("%s", inputWord);
                    scanf("%s", input_word);
                    int found = 0;
                    

                    // Keluar dari loop jika pengguna mengetik "q"
                    if (strcmp(input_word, "q") == 0)
                        break;

                    // Mencari kata dalam array kata dan memperbarui skor
                    int k = 0;
                    if ((searchAndUpdateScore(words, scores, wordCount, input_word)) && (findWord(&board, input_word))) {
                        for (int i = 0; i < 5; i++) {
	                		if (strcmp(input_word, findedWord[i]) == 0) {
		                		printf("\n						You have found it O_O");
		                		getch();
		                		found = 1;
							} 
						}
						if (!found) {
							printf("\n							AWESOME ^^");
							getch();
							player->correctWord++; // Menambahkan jumlah kata yang benar
	                        player->score =  player->score + 100; // Menambahkan skor jika kata ditemukan
					        strcpy(findedWord[k], input_word);
					        k++;
					    }
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

