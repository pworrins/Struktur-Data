#include "WSP.h"
#include <stdio.h>

// Fungsi untuk menampilkan aturan permainan dalam bahasa Indonesia
void displayRulesIndonesian() {
	system("cls");
    printf("===== Aturan Permainan Word Search Puzzle =====\n");
    printf("Selamat datang di Word Search Puzzle!\n");
    printf("Word Search Puzzle adalah permainan di mana Anda mencari kata yang tersembunyi di dalam grid huruf.\n");
    printf("Berikut adalah aturan permainan:\n");
    printf("1. Pilih Tema Bahasa.\n");
    printf("2. Pilih tingkat kesulitan: Mudah, Sedang, atau Sulit\n");
    printf("3. Pilih tema permainan.\n");
    printf("4. Cari kata-kata yang tersembunyi di dalam grid huruf.\n");
    printf("5. Ketikkan kata yang ditemukan untuk mencari tahu apakah itu benar.\n");
    printf("6. Jika kata yang dimasukkan benar dan ditemukan di dalam grid, Anda akan mendapatkan skor 100.\n");
    printf("7. Permainan berakhir ketika anda menekan huruf q pada pilihan atau\n");
    printf("8. Permainan berakhir ketika semua kata telah ditemukan.\n");
    printf("9. Skor Anda akan ditampilkan di leaderboard.\n");
    printf("10. Nikmati bermain Word Search Puzzle!\n");
}

// Fungsi untuk menampilkan aturan permainan dalam bahasa Inggris
void displayRulesEnglish() {
    system("cls");
    printf("===== Word Search Puzzle Game Rules =====\n");
    printf("Welcome to Word Search Puzzle!\n");
    printf("Word Search Puzzle is a game where you search for hidden words in a grid of letters.\n");
    printf("Here are the game rules:\n");
    printf("1. Choose the Language Theme.\n");
    printf("2. Choose the difficulty level: Easy, Medium, or Hard.\n");
    printf("3. Select the game theme.\n");
    printf("4. Find the hidden words in the grid of letters.\n");
    printf("5. Type the found words to check if they are correct.\n");
    printf("6. If the entered word is correct and found in the grid, you will earn a score of 100.\n");
    printf("7. The game ends when you press the letter 'q' on the selection or\n");
    printf("8. The game ends when all words have been found.\n");
    printf("9. Your score will be displayed on the leaderboard.\n");
    printf("10. Enjoy playing Word Search Puzzle!\n");
}


// Fungsi utama
int mainRules() {
	system("cls");
    int languageChoice;
    // Pilihan bahasa
    printf("Pilih bahasa / Choose language:\n");
    printf("1. Bahasa Indonesia\n");
    printf("2. English\n");
    printf("Your choice: ");
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
        default:
            printf("Pilihan bahasa tidak valid.\n");
    }
    
    return 0;
}
