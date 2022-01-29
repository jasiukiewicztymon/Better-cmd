#include "mainext.h"
#include <Windows.h>
#include <string>
#include <iostream>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void showHeader(std::string ExtensionName, std::string Path, bool isUser) {
    SetConsoleTextAttribute(hConsole, 2);
    std::cout << ExtensionName;
    SetConsoleTextAttribute(hConsole, 10);
    std::cout << " " << Path << "\n";
    SetConsoleTextAttribute(hConsole, 15);
    
    if (isUser) {
        SetConsoleTextAttribute(hConsole, 9);
        std::cout << "User";
        SetConsoleTextAttribute(hConsole, 15);
        std::cout << " > ";
    }
    else {
        SetConsoleTextAttribute(hConsole, 12);
        std::cout << "Root";
        SetConsoleTextAttribute(hConsole, 15);
        std::cout << " > ";
    }
}

bool isPath(std::string &path, std::string command) {
    struct  stat buffer;
    if (stat((path + command).c_str(), &buffer) == 0) {
        if (command[command.length() - 1] != '\\')
            path += command + "\\";
        else
            path += command;
        return true;
    }
    else {
        SetConsoleTextAttribute(hConsole, 12);
        std::cout << "The " + path + command + " path doesn't exist...\n";
        SetConsoleTextAttribute(hConsole, 15);
        return false;
    }
}