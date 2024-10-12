#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "windows.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int bestScore = 0;
void MENU();

void gotoXY(int x, int y) // Hàm dịch con trỏ chuột đến điểm có tọa độ (x, y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

void ShowCur(bool CursorVisibility) // Hàm làm ẩn con trỏ chuột
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}


void tutorial() { // chưa xong
    system("cls");
    int check = 1;
    printf("==================== Tutorial ====================\n\n");
    printf("- Remember to switch Unikey to English.\n");
    printf("- Use the A, W, S, D keys to control the snake: left, up, down, right.\n");
    printf("- After pressing Start Game, you will begin playing immediately.\n");
    printf("- If the snake hits the wall or itself, the game will end.\n");
    printf("- Control the snake and try to eat as much food as possible.\n");
    printf("\nHAVE FUN!!!\n\n");

    printf("Enter to return to the MENU!");
    while (getchar() != '\n');
    getchar();

    MENU();
}


int mapRange = 9; // Độ rộng map
void chooseMap() { // Hàm tạo độ rộng map
    system("cls");
    int check = 1;

    while (check) {
        char choice[10];
        printf("\nSelect map size [ small(s) | medium(m) | large(l) ]\n");
        printf("Your choice: ");
        scanf("%s", &choice);
        
        int i = 0;
        while (choice[i]) {
            choice[i] = tolower(choice[i]);
            i++;
        }

        if (strcmp(choice, "s") == 0 || strcmp(choice, "small") == 0) {
            mapRange = 9;
            check = 0;
        } else if (strcmp(choice, "m") == 0 || strcmp(choice, "medium") == 0) {
            mapRange = 11;
            check = 0;
        } else if (strcmp(choice, "l") == 0 || strcmp(choice, "large") == 0) {
            mapRange = 15;
            check = 0;
        } else {
            printf("Invalid input. Please try again.\n");
        }
    }

    MENU();
}


int gameDiff = 250; // Độ khó của game
int chooseDiff() { // Hàm chọn độ khó cho game
    system("cls");
    int check = 1;
    while (check) {
        char choice[10];
        printf("\nSelect difficulty [ easy(e) | normal(n) | hard(h) ]\n");
        printf("Your choice: ");
        scanf("%s", &choice);

        int i = 0;
        while (choice[i]) {
            choice[i] = tolower(choice[i]);
            i++;
        }

        if (strcmp(choice, "e") == 0 || strcmp(choice, "easy") == 0) {
            gameDiff = 250;
            check = 0;
        } else if (strcmp(choice, "n") == 0 || strcmp(choice, "normal") == 0) {
            gameDiff = 150;
            check = 0;
        } else if (strcmp(choice, "h") == 0 || strcmp(choice, "hard") == 0) {
            gameDiff = 50;
            check = 0;
        } else {
            printf("Invalid input. Please try again.\n");
        }
    }

    MENU();
}


void drawMap() { // Hàm tạo tường
    for (int i = 0; i <= mapRange; i++) {
        printf("==");
    }
    printf("=\n");

    for (int i = 0; i < mapRange; i++) {
        for (int j = 0; j <= mapRange + 1; j++) {
            if (j == 0 || j == mapRange + 1) {
                printf("| ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i <= mapRange; i++) {
        printf("==");
    }
    printf("=\n");

    printf("Best Score: %d", bestScore);
}


int snakeSize = 4; // Độ dài của con rắn
int snakeShape[15 * 15][2]; // Mảng lưu tọa độ toàn bộ thân của con rắn
void drawStartSnake() { // khởi tạo hình con rắn khi mới bắt đầu chương trình
    gotoXY(snakeShape[0][0], snakeShape[0][1]);
    printf("# ");
    for (int i = 1; i < snakeSize; i++) {
        int snake[2] = {snakeShape[i - 1][0] + 2, snakeShape[i - 1][1]};
        snakeShape[i][0] = snake[0];
        snakeShape[i][1] = snake[1];
        gotoXY(snakeShape[i][0], snakeShape[i][1]);
        printf("o ");
    }
}


int moveDirection = 1; // | 1 = Left | 2 = Up | 3 = Right | 4 = Down |
void snakeControl(int check) { // Tạo hàm điều khiển con rắn
    if (check) {
        int snake[2] = {snakeShape[snakeSize - 1][0], snakeShape[snakeSize - 1][1]};
        snakeShape[snakeSize][0] = snake[0];
        snakeShape[snakeSize][1] = snake[1];
        snakeSize++;
    } else {
        gotoXY(snakeShape[snakeSize - 1][0], snakeShape[snakeSize - 1][1]);
        printf("  ");
    }

    for (int i = snakeSize - 1; i >= 1; i--) {
        int snake[2] = {snakeShape[i - 1][0], snakeShape[i - 1][1]};
        snakeShape[i][0] = snake[0];
        snakeShape[i][1] = snake[1];
        gotoXY(snakeShape[i][0], snakeShape[i][1]);
        printf("o ");
    }

    int headSnake[2] = {snakeShape[0][0], snakeShape[0][1]};
    if (moveDirection == 1) {
        headSnake[0] -= 2;
    }
    else if (moveDirection == 2) {
        headSnake[1] -= 1;
    }
    else if (moveDirection == 3) {
        headSnake[0] += 2;
    }
    else if (moveDirection == 4) {
        headSnake[1] += 1;
    }
    snakeShape[0][0] = headSnake[0];
    snakeShape[0][1] = headSnake[1];
    gotoXY(snakeShape[0][0], snakeShape[0][1]);
    printf("# ");
}


int checkAlive(int headSnake[]) { // Hàm check xem rắn chết chưa
    if ((headSnake[0] == 0) || (headSnake[0] == (mapRange * 2) + 2)) {
        return 0;
    } else if ((headSnake[1] == 0) || (headSnake[1] == mapRange + 1)) {
        return 0;
    }
    
    int x = snakeShape[0][0];
    int y = snakeShape[0][1];
    for (int i = 4; i < snakeSize; i++) {
        if (x == snakeShape[i][0] && y == snakeShape[i][1]) {
            return 0;
        }
    }

    return 1;
}


int hasEatenFood = 0;
int food[2];
void createFood() { // Hàm tạo ra vị trị của mồi và vẽ mồi lên map
    int check = 0;
    while (!check) {
        int overSnake = 0;
        food[0] = rand() % (mapRange) + 1;
        food[1] = rand() % (mapRange) + 1;

        for (int i = 0; i < snakeSize; i++) {
            if (snakeShape[i][0] == (food[0] * 2) && snakeShape[i][1] == food[1]) {
                overSnake = 1;
                break;
            }
        }
        
        if (!overSnake) {
            check = 1;
        }
    }

    gotoXY(food[0] * 2, food[1]);
    printf("$ ");
}


void checkSnakeAte(int headSnake[]) { // Hàm check xem mồi có được ăn hay chưa
    if (headSnake[0] == (food[0] * 2) && headSnake[1] == food[1]) {
        hasEatenFood = 1;
    }
}


int winGame = 0;
int checkSnakeSize() { // Hàm kiểm tra xem rắn dài kín map hay chưa
    if (snakeSize == mapRange * mapRange) {
        winGame = 1;
        return 0;
    } else {
        return 1;
    }
}


void endGame(int win) {
    gotoXY(0, mapRange + 1);
    if (win) {
        printf("\n\n\nYOU WINNNNN!!!!!!\nYour Score : %d\n\n", snakeSize);
    } else {
        printf("\n\n\nGAME OVERRRRR!!!!\nYour Score: %d\n\n", snakeSize);
    }
    if (snakeSize > bestScore) {
        bestScore = snakeSize;
    }

    ShowCur(true);

    int check = 1;
    printf("1. Play again.\n");
    printf("2. Exit.\n");

    int choice;
    while (check) {
        printf("Your choice: ");
        scanf("%d", &choice);

        if (choice == 1 || choice == 2) {
            check = 0;
        } else {
            printf("Invalid input. Please try again.\n");
        }
    }

    if (choice == 1) {
        MENU();
    } else if (choice == 2) {
        system("cls");
    }
}


void startGame() {
    snakeSize = 4;
    system("cls");
    ShowCur(false);
    drawMap();

    int headSnake[2] = {2 + ((mapRange / 2) * 2), (mapRange / 2) + 1};
    snakeShape[0][0] = headSnake[0];
    snakeShape[0][1] = headSnake[1];

    drawStartSnake(snakeShape);
    createFood();

    while (checkAlive(snakeShape[0]) && checkSnakeSize()) {
        if (kbhit()) {
            char kitu = (char) tolower(getch());
            if (kitu == 'a') { // sang trái
                if (moveDirection != 3) {
                    moveDirection = 1;
                }
            } else if (kitu == 'w') { // lên trên
                if (moveDirection != 4) {
                    moveDirection = 2;
                }
            } else if (kitu == 'd') { // sang phải
                if (moveDirection != 1) {
                    moveDirection = 3;
                }
                moveDirection = 3;
            } else if (kitu == 's') { // xuống dưới
                if (moveDirection != 2) {
                    moveDirection = 4;
                }
            } 
        }

        checkSnakeAte(snakeShape[0]);
        snakeControl(hasEatenFood);

        if (hasEatenFood == 1) {
            createFood();
            hasEatenFood = 0;
        }

        Sleep(gameDiff);
    }

    endGame(winGame);
}


void MENU() { // Đơn giản nó là menu thoi
    system("cls");
    int check = 1;

    char map[20];
    char level[20];
    if (mapRange == 9) {
        strcpy(map, "small map");
    } else if (mapRange == 11) {
        strcpy(map, "medium map");
    } else {
        strcpy(map, "large map");
    }

    if (gameDiff == 250) {
        strcpy(level, "easy");
    } else if (gameDiff == 150) {
        strcpy(level, "normal");
    } else {
        strcpy(level, "hard");
    }


    printf("========== Snake Game ==========\n");
    printf("1. Choose the map (%s)\n", map);
    printf("2. Choose the level (%s)\n", level);
    printf("3. How to Play!\n");
    printf("4. Start game!\n");
    printf("5. Exit game.\n");


    int choice;
    while (check) {
        printf("Your choice: ");
        scanf("%d", &choice);
        printf("\n");

        if (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5) {
            check = 0;
        } else {
            printf("Invalid input. Please try again.\n");
        }
    }

    if (choice == 1) {
        chooseMap();
    } else if (choice == 2) {
        chooseDiff();
    } else if (choice == 3) {
        tutorial();
    } else if (choice == 4) {
        startGame();
    }
}


int main() {
    srand(time(NULL));
    system("cls");
    MENU();

    return 0;
}