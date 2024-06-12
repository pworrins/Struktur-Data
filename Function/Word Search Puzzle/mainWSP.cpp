#include <stdio.h>
#include <stdlib.h>
#include "WSP.h"

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
                getch();
                
                break;
            case 3:
            	// Menampilkan Rules
                mainRules();
                getch();
                break;
            case 4:
                // Keluar dari program
                // Menyimpan leaderboard ke file teks
                saveLeaderboard(leaderboard, leaderboardSize);

                // Menyimpan waktu terakhir leaderboard diperbarui
                time(&lastUpdated);
                printf("\n\n\n			Leaderboard terakhir diperbarui pada: %s \n", ctime(&lastUpdated));
                break;
            default:
                printf("Invalid Choice\n");
                break;
        }
    } while (choice != 4);

    return 0;
}

