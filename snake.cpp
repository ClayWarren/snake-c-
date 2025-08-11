#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <thread>   // For sleep_for
#include <chrono>   // For milliseconds

#ifdef _WIN32
#include <conio.h>   // Windows: _kbhit() and _getch()
#include <windows.h> // Not needed anymore, but kept for compatibility
#else
#include <termios.h> // Unix: For terminal modes
#include <unistd.h>  // For STDIN_FILENO
#include <sys/types.h>
#include <sys/time.h> // For select()
#include <fcntl.h>    // For fcntl()
#endif

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y;  // Snake head
int fruitX, fruitY;
int score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

#ifndef _WIN32
// Unix kbhit() implementation using select()
void changemode(int dir) {
    static struct termios oldt, newt;
    if (dir == 1) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

int kbhit() {
    struct timeval tv;
    fd_set rdfs;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&rdfs);
    FD_SET(STDIN_FILENO, &rdfs);
    select(STDIN_FILENO + 1, &rdfs, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &rdfs);
}
#endif

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
}

void Draw() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    // Top border
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#";
            if (i == y && j == x) cout << "O";
            else if (i == fruitY && j == fruitX) cout << "#";
            else {
                bool printTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (i == tailY[k] && j == tailX[k]) {
                        cout << "o";
                        printTail = true;
                    }
                }
                if (!printTail) cout << " ";
            }
            if (j == width - 1) cout << "#";
        }
        cout << endl;
    }

    // Bottom border
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
}

void Input() {
    if (kbhit()) {
        char key;
#ifdef _WIN32
        key = _getch();
#else
        key = getchar();
#endif
        switch (key) {
            case 'a': if (dir != RIGHT) dir = LEFT; break;
            case 'd': if (dir != LEFT) dir = RIGHT; break;
            case 'w': if (dir != DOWN) dir = UP; break;
            case 's': if (dir != UP) dir = DOWN; break;
            case 'x': gameOver = true; break;
        }
    }
}

void Logic() {
    // Move tail
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Move head
    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
        default: break;
    }

    // Wall collision
    if (x >= width || x < 0 || y >= height || y < 0) gameOver = true;

    // Tail collision
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) gameOver = true;
    }

    // Eat fruit
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main() {
    srand(time(NULL));  // Seed random
#ifndef _WIN32
    changemode(1);  // Set non-blocking, no-echo mode on Unix
#endif
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        this_thread::sleep_for(chrono::milliseconds(100));  // Delay
    }
#ifndef _WIN32
    changemode(0);  // Reset terminal mode on Unix
#endif
    cout << "Game Over! Final Score: " << score << endl;
    return 0;
}
