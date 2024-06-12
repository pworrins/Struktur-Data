#include "WSP.h"

/*  = = =  Player and Leaderboard Functions  = = =   */

/* Fungsi untuk menampilkan leaderboard di konsol
leaderboard: Array dari struktur Player yang berisi leaderboard.
leaderboardSize: Jumlah pemain dalam leaderboard. */
void displayLeaderboard(Player leaderboard[], int leaderboardSize) {
    loading();
    system("cls"); // Membersihkan layar sebelum menampilkan leaderboard
    int x = 30;
    gotoxy(x, 2); printf(" _                    _           _                         _ \n");
    gotoxy(x, 3); printf("| |                  | |         | |                       | |\n");
    gotoxy(x, 4); printf("| |     ___  __ _  __| | ___ _ __| |__   ___   __ _ _ __ __| |\n");
    gotoxy(x, 5); printf("| |    / _ \\/ _` |/ _` |/ _ \\ '__| '_ \\ / _ \\ / _` | '__/ _` |\n");
    gotoxy(x, 6); printf("| |___|  __/ (_| | (_| |  __/ |  | |_) | (_) | (_| | | | (_| |\n");
    gotoxy(x, 7); printf("\\_____/\\___|\\__,_|\\__,_|\\___|_|  |_.__/ \\___/ \\__,_|_|  \\__,_|\n");
    gotoxy(x, 8); printf("===============================================================");
     
    gotoxy(40, 10); printf("No");
    gotoxy(55, 10); printf(" Name");
    gotoxy(75, 10); printf("Score");
    for (int i = 0; i < leaderboardSize; ++i) {
        gotoxy(40, 11 + i); printf("%d.", i + 1);
        gotoxy(55, 11 + i); printf("%s", leaderboard[i].name);
        gotoxy(75, 11 + i); printf(" %d", leaderboard[i].score);
    }
    
    // Tampilkan informasi terupdate
    time_t rawtime;
    struct tm *info;
    char buffer[80];
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(buffer, 80, "%Y-%m-%d", info);
    gotoxy(x, 1 + leaderboardSize  + 13); printf("Leaderboard updated on: %s", buffer);
}

/* Fungsi untuk mencari kata dalam array kata dan memperbarui skornya
words: Array kata yang dicari.
scores: Array skor yang akan diperbarui.
wordCount: Jumlah kata dalam array words.
target: Kata yang dicari. */
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

/* Fungsi untuk menghitung total skor dari semua kata
scores: Array skor kata.
wordCount: Jumlah kata dalam array scores. */
int calculateTotalScore(int scores[], int wordCount) {
    int totalScore = 0;
    for (int i = 0; i < wordCount; ++i) {
        totalScore += scores[i];
    }
    return totalScore;
}

/* Fungsi untuk menambahkan pemain ke leaderboard
leaderboard: Array dari struktur Player yang berisi leaderboard.
leaderboardSize: Pointer ke jumlah pemain dalam leaderboard.
name: Nama pemain yang akan ditambahkan.
score: Skor pemain yang akan ditambahkan. */
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
    // Urutkan leaderboard berdasarkan skor (dari yang terbesar ke terkecil)
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

/* Fungsi untuk menyimpan leaderboard ke file teks
leaderboard: Array dari struktur Player yang berisi leaderboard.
leaderboardSize: Jumlah pemain dalam leaderboard. */
void saveLeaderboard(Player leaderboard[], int leaderboardSize) {
    FILE *file = fopen("Kamus/leaderboard.txt", "w");
    if (file == NULL) {
        printf("\n\n\n			Gagal membuka file leaderboard.\n");
        return;
    }
    time_t rawtime;
    struct tm *info;
    char buffer[80];
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(buffer, 80, "%Y-%m-%d", info);
    fprintf(file, "Leaderboard updated on: %s\n", buffer);
    for (int i = 0; i < leaderboardSize; ++i) {
        fprintf(file, "%s %d\n", leaderboard[i].name, leaderboard[i].score);
    }
    fclose(file);
}

/* Fungsi untuk memuat leaderboard dari file teks
leaderboard: Array dari struktur Player yang berisi leaderboard.
leaderboardSize: Pointer ke jumlah pemain dalam leaderboard. */
void loadLeaderboard(Player leaderboard[], int* leaderboardSize) {
    FILE *file = fopen("Kamus/leaderboard.txt", "r");
    if (file == NULL) {
        printf("\n\n\n			File leaderboard tidak ditemukan, leaderboard kosong.\n");
        return;
    }
    char buffer[100];
    fgets(buffer, sizeof(buffer), file); // baca tanggal terupdate
    while (*leaderboardSize < MAX_LEADERBOARD_SIZE && fscanf(file, "%s %d", leaderboard[*leaderboardSize].name, &leaderboard[*leaderboardSize].score) == 2) {
        (*leaderboardSize)++;
    }
    fclose(file);
}


