#include "WSP.h"
#include <stdio.h>
#include <conio.h>

#include "WSP.h"
#include <stdio.h>
#include <conio.h>

void BannerRules() {
    printCentered(" _____                      \n", 4);
    printCentered("|  __ \\                     \n", 5);
    printCentered("| |  \\/ __ _ _ __ ___   ___ \n", 6);
    printCentered("| | __ / _` | '_ ` _ \\ / _ \\\n", 7);
    printCentered("| |_\\ \\ (_| | | | | | |  __/\n", 8);
    printCentered(" \\____/\\__,_|_| |_| |_|\\___|\n", 9);
    printCentered("______      _           \n", 10);
    printCentered("| ___ \\    | |          \n", 11);
    printCentered("| |_/ /   _| | ___  ___ \n", 12);
    printCentered("|    / | | | |/ _ \\/ __|\n", 13);
    printCentered("| |\\ \\ |_| | |  __/\\__ \\\n", 14);
    printCentered("\\_| \\_\\__,_|_|\\___||___/\n", 15);
}

void Rules () {
	printCentered("______      _           \n", 1);
    printCentered("| ___ \\    | |          \n", 2);
    printCentered("| |_/ /   _| | ___  ___ \n", 3);
    printCentered("|    / | | | |/ _ \\/ __|\n", 4);
    printCentered("| |\\ \\ |_| | |  __/\\__ \\\n", 5);
    printCentered("\\_| \\_\\__,_|_|\\___||___/\n", 6);
    printCentered(" = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ", 7);
}

// Fungsi untuk menampilkan aturan permainan dalam bahasa Indonesia
void displayRulesIndonesian() {
    loading();
	system("cls");
    Rules();
    printCentered("Selamat datang di Word Search Puzzle!\n", 11);
    printCentered("Word Search Puzzle adalah permainan di mana Anda mencari kata yang tersembunyi di dalam grid huruf.\n", 12);
    printCentered("Berikut adalah aturan permainan:\n", 13);
    printCentered("1. Pilih Tema Bahasa.\n", 14);
    printCentered("2. Pilih tingkat kesulitan: Mudah, Sedang, atau Sulit\n", 15);
    printCentered("3. Pilih tema permainan.\n", 16);
    printCentered("4. Cari kata-kata yang tersembunyi di dalam grid huruf.\n", 17);
    printCentered("5. Ketikkan kata yang ditemukan untuk mencari tahu apakah itu benar.\n", 18);
    printCentered("6. Jika kata yang dimasukkan benar dan ditemukan di dalam grid, Anda akan mendapatkan skor 100.\n", 19);
    printCentered("7. Permainan berakhir ketika anda menekan huruf q pada pilihan atau\n", 20);
    printCentered("8. Permainan berakhir ketika semua kata telah ditemukan.\n", 21);
    printCentered("9. Skor Anda akan ditampilkan di leaderboard.\n", 22);
    printCentered("10. Nikmati bermain Word Search Puzzle!\n", 23);
}

// Fungsi untuk menampilkan aturan permainan dalam bahasa Inggris
void displayRulesEnglish() {
	loading();
    system("cls");
    Rules();
    printCentered("Welcome to Word Search Puzzle!\n", 11);
    printCentered("Word Search Puzzle is a game where you search for hidden words in a grid of letters.\n", 12);
    printCentered("Here are the game rules:\n", 13);
    printCentered("1. Choose the Language Theme.\n", 14);
    printCentered("2. Choose the difficulty level: Easy, Medium, or Hard.\n", 15);
    printCentered("3. Select the game theme.\n", 16);
    printCentered("4. Find the hidden words in the grid of letters.\n", 17);
    printCentered("5. Type the found words to check if they are correct.\n", 18);
    printCentered("6. If the entered word is correct and found in the grid, you will earn a score of 100.\n", 19);
    printCentered("7. The game ends when you press the letter 'q' on the selection or\n", 20);
    printCentered("8. The game ends when all words have been found.\n", 21);
    printCentered("9. Your score will be displayed on the leaderboard.\n", 22);
    printCentered("10. Enjoy playing Word Search Puzzle!\n", 23);
}

// Fungsi utama
int mainRules() {
	loading();
    system("cls");
    table();
    BannerRules();
    int languageChoice;
    int x = 46;
    // Pilihan bahasa
    printCentered("Pilih bahasa / Choose language:\n", 19);
    printCentered("1. Bahasa Indonesia\n", 20);
    printCentered("2. English\n", 21);
    printCentered("Your choice: ", 18);
    scanf("%d", &languageChoice);
    system("cls");
    // Menampilkan aturan permainan sesuai dengan bahasa yang dipilih
    switch(languageChoice) {
        case 1:
            system("cls");
            displayRulesIndonesian();
            break;
        case 2:
            system("cls");
            displayRulesEnglish();
            getch();
            break;
        default:
            printf("Pilihan bahasa tidak valid.\n");
    }

    return 0;
}

