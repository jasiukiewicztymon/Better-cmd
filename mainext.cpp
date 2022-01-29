#include "mainext.h"
#include <Windows.h>
#include <string>
#include <iostream>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void showHeader(std::string ExtensionName, std::string Path, std::string Name) {
    SetConsoleTextAttribute(hConsole, 2);
    std::cout << ExtensionName;
    SetConsoleTextAttribute(hConsole, 10);
    std::cout << " " << Path << "\n";
    SetConsoleTextAttribute(hConsole, 15);
    

    if (Name == "Root") {
        SetConsoleTextAttribute(hConsole, 12);
        std::cout << Name;
        SetConsoleTextAttribute(hConsole, 15);
    }
    else {
        SetConsoleTextAttribute(hConsole, 9);
        std::cout << Name;
        SetConsoleTextAttribute(hConsole, 15);
    }
    std::cout << " > ";
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

void errorText(std::string text) {
    SetConsoleTextAttribute(hConsole, 12);
    std::cout << text << "\n";
    SetConsoleTextAttribute(hConsole, 15);
}

void showHelp() {
    std::cout << "\tEXTENSIONS\n\n" 
        << "\text set [name] [path]   - copy the file at path and save it as name in the extension file\n"
        << "\text del [name]          - delete the extension\n"
        << "\text run [name]          - run the extension\n"
        << "\text list                - list all extention name and file linked with them\n\n"
        << "\tOTHER\n\n"
        << "\tcat [file]              - view the file content\n"
        << "\tcompare [file1] [file2] - comapre two files and show the differences\n";
}
