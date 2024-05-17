#include <stdio.h>
#include <stdlib.h>
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

// Kamus kata untuk level Easy
char easyKamus[][MAX_FILENAME_LENGTH] = {"buah", "hewan", "negara"};
// Kamus kata untuk level Medium
char mediumKamus[][MAX_FILENAME_LENGTH] = {"hukum", "pendidikan", "benda"};
// Kamus kata untuk level Hard
char hardKamus[][MAX_FILENAME_LENGTH] = {"hard_kamus"};


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
    printf("Masukkan Nama Anda: ");
    scanf("%s", playerName);
}

// Fungsi untuk menampilkan main menu
int displayMainMenu() {
	system("cls");
    int choice;
    printf("  __  __       _         __  __                  \n");
    printf(" |  \\/  |     (_)       |  \\/  |                 \n");
    printf(" | \\  / | __ _ _ _ __   | \\  / | ___ _ __  _   _ \n");
    printf(" | |\\/| |/ _` | | '_ \\  | |\\/| |/ _ \\ '_ \\| | | |\n");
    printf(" | |  | | (_| | | | | | | |  | |  __/ | | | |_| |\n");
    printf(" |_|  |_|\\__,_|_|_| |_| |_|  |_|\\___|_| |_|\\__,_|\n");
    printf("                                                 \n");
    printf("==================================================\n");
    printf("1. Mulai Permainan\n");
    printf("2. Tampilkan Leaderboard\n");
    printf("3. Keluar\n");
    printf("Pilihan Anda: ");
    scanf("%d", &choice);
    return choice;
}

void printBanner() {
    printf(" __          __           _         \n");
    printf(" \\ \\        / /          | |        \n");
    printf("  \\ \\  /\\  / /__  _ __ __| |        \n");
    printf("   \\ \\/  \\/ / _ \\| '__/ _` |        \n");
    printf("    \\  /\\  / (_) | | | (_| |        \n");
    printf("    _\\/__\\/ \\___/|_|  \\__,_|  _     \n");
    printf("   / ____|                   | |    \n");
    printf("  | (___   ___  __ _ _ __ ___| |__  \n");
    printf("   \\___ \\ / _ \\/ _` | '__/ __| '_ \\ \n");
    printf("   ____) |  __/ (_| | | | (__| | | |\n");
    printf("  |_____/ \\___|\\__,_|_|  \\___|_| |_|   \n\n\n");
    printf(" _    _      _                            _____       _   _            _____  ___ ___  ________ _ \n");
    printf("| |  | |    | |                          |_   _|     | | | |          |  __ \\/ _ \\|  \\/  |  ___| |\n");
    printf("| |  | | ___| | ___ ___  _ __ ___   ___    | | ___   | |_| |__   ___  | |  \\/ /_\\ \\ .  . | |__ | |\n");
    printf("| |\\/| |/ _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\   | |/ _ \\  | __| '_ \\ / _ \\ | | __|  _  | |\\/| |  __|| |\n");
    printf("| |  | |  __/ | (_| (_) | | | | | |  __/   | | (_) | | |_| | | |  __/ | |_\\ \\ | | | |  | | |___|_|\n");
    printf("\\_/  |_/\\___|_|\\___\\___/|_| |_| |_|\\___|   \\_/\\___/   \\__|_| |_|\\___|  \\____|_| \\_\\_|  |_|____/(_)\n");
}

int main() {
    Player leaderboard[MAX_LEADERBOARD_SIZE]; // Leaderboard
    int leaderboardSize = 0; // Ukuran leaderboard
    time_t lastUpdated; // Waktu terakhir leaderboard diperbarui

    // Memuat leaderboard dari file teks
    loadLeaderboard(leaderboard, &leaderboardSize);
    system("color FD");
    printBanner();
    // Meminta nama pemain
    char playerName[50];
    inputPlayerName(playerName);
    system("cls");
    // Main loop
    int choice;
    do {
        choice = displayMainMenu();
        switch (choice) {
            case 1: {
                system("cls"); // Membersihkan layar sebelum memulai permainan

                // Meminta pengguna untuk memilih tema
                printf(" _____ ________  ___ ___  \n");
                printf("|_   _|  ___|  \\/  |/ _ \\ \n");
                printf("  | | | |__ | .  . / /_\\ \\\n");
                printf("  | | |  __|| |\\/| |  _  |\n");
                printf("  | | | |___| |  | | | | |\n");
                printf("  \\_/ \\____/\\_|  |_|_| |_/\n");
                printf("                          \n");
                printf(" =========================\n");
                printf("=========================\n");
			    printf("1. Easy\n");
			    printf("2. Medium\n");
			    printf("3. Hard\n");
			    printf("Pilihan Anda: ");
			    int levelChoice;
			    scanf("%d", &levelChoice);
 

    char (*selectedKamus)[MAX_FILENAME_LENGTH]; // Pointer untuk memilih kamus kata berdasarkan tingkat kesulitan
    int kamusSize; // Ukuran kamus kata yang dipilih

    // Memilih kamus kata berdasarkan tingkat kesulitan yang dipilih
    switch (levelChoice) {
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
            return 1; // Keluar dari program dengan kode kesalahan
    }

    // Pilih tema
    printf("=========================\n");
    printf("Pilih tema:\n");
    for (int i = 0; i < kamusSize; ++i) {
        printf("%d. %s\n", i + 1, selectedKamus[i]);
    }
    printf("Pilihan Anda: ");
    int themeChoice;
    scanf("%d", &themeChoice);

    // Validasi pilihan tema
    if (themeChoice < 1 || themeChoice > kamusSize) {
        printf("Pilihan tema tidak valid.\n");
        return 1; // Keluar dari program dengan kode kesalahan
    }

    // Memuat tema dari file
    char filename[MAX_FILENAME_LENGTH]; // Nama file tema yang dipilih
    sprintf(filename, "Kamus/%s.txt", selectedKamus[themeChoice - 1]);

                FILE *file;
                // Membuka file
                file = fopen(filename, "r");
                if (file == NULL) {
                    printf("Gagal membuka file.\n");
                    break;
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

                // Menampilkan lima kata yang telah diacak
                printf("Kata-kata yang telah diacak:\n");
                int numWordsToDisplay = 5; // Jumlah kata yang akan ditampilkan
                for (int i = 0; i < numWordsToDisplay && i < wordCount; i++) {
                    printf("%s\n", words[i]);
                }
                printf("\n");

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
                    if (searchAndUpdateScore(words, scores, wordCount, input_word)) {
                        totalScore++; // Menambahkan skor jika kata ditemukan
                        correctWords++; // Menambahkan jumlah kata yang benar
                    }
                }

                printf("Total skor: %d\n", totalScore);

                // Menambahkan pemain ke leaderboard
                addToLeaderboard(leaderboard, &leaderboardSize, playerName, totalScore);
                break;
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

