#include <Windows.h>
#include <string>
#include <iostream>
#include <conio.h>
#include <stdio.h>

void CheckKey(void) {
    int key;
    if (_kbhit()) {
        key = _getch();
        if (key == 224) {
            do {
                key = _getch();
            } while (key == 224);
            switch (key) {
            case 72:
                printf("up");
                break;
            case 75:
                printf("left");
                break;
            case 77:
                printf("right");
                break;
            case 80:
                printf("down");
                break;
            }
        }
        else {
            char ch = key;
            std::cout << ch << "\n";
        }
    }
}

int main() {
    while (1) {
        if (_kbhit()) {
            CheckKey();
        }
    }
}
