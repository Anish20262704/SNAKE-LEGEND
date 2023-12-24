#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameEnded;
const int mapWidth = 20;
const int mapHeight = 20;

enum Direction {
    HALT = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

Direction direction;
int xPos, yPos, fruitPosX, fruitPosY, playerScore = 0;

int tailXPositions[500], tailYPositions[500];
int tailLength = 0;

void InitializeGame() {
    gameEnded = false;
    direction = HALT;
    xPos = mapWidth / 2;
    yPos = mapHeight / 2;
    fruitPosX = rand() % mapWidth;
    fruitPosY = rand() % mapHeight;
}

void RenderGame() {
    system("cls");
    for (int i = 0; i < mapWidth + 2; i++) {
        cout << "* ";
    }
    cout << endl;

    for (int j = 0; j < mapHeight; j++) {
        cout << "* ";
        for (int i = 0; i < mapWidth; i++) {
            if (j == yPos && i == xPos) {
                cout << "O ";
            } else if (j == fruitPosY && i == fruitPosX) {
                cout << "@ ";
            } else {
                int z = 1;
                for (int k = 0; k < tailLength; k++) {
                    if (tailXPositions[k] == i && tailYPositions[k] == j) {
                        cout << "o ";
                        z = 0;
                    }
                }
                if (z) {
                    cout << "  ";
                }
            }
        }
        cout << "* ";
        cout << endl;
    }

    for (int i = 0; i < mapWidth + 2; i++) {
        cout << "* ";
    }
}

void CaptureInput() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                direction = LEFT;
                break;
            case 'w':
                direction = UP;
                break;
            case 'd':
                direction = RIGHT;
                break;
            case 's':
                direction = DOWN;
                break;
            case 'x':
                gameEnded = true;
                break;
        }
    }
}

void UpdateLogic() {
    int prevX = tailXPositions[0];
    int prevY = tailYPositions[0];
    int prev2X, prev2Y;
    tailXPositions[0] = xPos;
    tailYPositions[0] = yPos;

    for (int i = 1; i < tailLength; i++) {
        prev2X = tailXPositions[i];
        prev2Y = tailYPositions[i];
        tailXPositions[i] = prevX;
        tailYPositions[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (direction) {
        case LEFT:
            xPos--;
            break;
        case RIGHT:
            xPos++;
            break;
        case UP:
            yPos--;
            break;
        case DOWN:
            yPos++;
            break;
    }

    int k = tailLength - 1;
    int collisionDetected = 0;
    while (k != -1) {
        if (tailXPositions[k] == xPos && tailYPositions[k] == yPos) {
            collisionDetected = 1;
            break;
        }
        k--;
    }

    if (xPos >= mapWidth || xPos < 0 || yPos >= mapHeight || yPos < 0 || collisionDetected == 1) {
        gameEnded = true;
    } else if (xPos == fruitPosX && yPos == fruitPosY) {
        playerScore += 5;
        fruitPosX = rand() % mapWidth;
        fruitPosY = rand() % mapHeight;
        tailLength++;
    }
}

void Pause(int milliSeconds) {
    int startTime = clock();
    while (clock() < startTime + milliSeconds);
}

int main() {
    cout << "          WELCOME TO SNAKE LEGEND" << endl;

    Pause(7000);
    system("cls");
    InitializeGame();
    while (!gameEnded) {
        RenderGame();
        cout << endl << "Score: " << playerScore << endl;
        Pause(100);
        CaptureInput();
        UpdateLogic();
    }

    system("cls");
    cout << "Game Over" << endl << "Final Score: " << playerScore << endl;


  return  0 ;
}