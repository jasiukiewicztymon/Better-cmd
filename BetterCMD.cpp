#include <iostream>
#include <Windows.h>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>
#include <fstream>

#include <direct.h>
#include <limits.h>
#include <process.h>

#include "mainext.h"

int main() {
    bool isUser = system("call :isAdmin");
    system("cls");

    SetConsoleTitleA("BetterCMD");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::string command = "", extention = "Main", path ="C:\\";

    SetConsoleTextAttribute(hConsole, 7);

    std::cout << "\n     ____       __  __               ________  _______ \n";
    std::cout << "    / __ )___  / /_/ /____  _____   / ____/  |/  / __ \\\n";
    std::cout << "   / __  / _ \\/ __/ __/ _ \\/ ___/  / /   / /|_/ / / / /\n";
    std::cout << "  / /_/ /  __/ /_/ /_/  __/ /     / /___/ /  / / /_/ / \n";
    std::cout << " /_____/\\___/\\__/\__/\\____/_/      \\____/_/  /_/_____/  \n";
    std::cout << "\n Github: jasiukiewicztymon\n\n\n";

    SetConsoleTextAttribute(hConsole, 15);

    do {
        showHeader(extention, path, isUser);
        getline(std::cin, command);
  
        std::cout << std::endl;

        std::stringstream ss(command);
        std::string splitstr;
        std::vector<std::string> args;

        while (ss >> splitstr) {
            args.emplace_back(splitstr);
        }
        
        if (args[0] == "ext") {
            if (args[1] == "set") {
                std::string name = args[2], spath = "", filename = "";
                for (int i = 3; i < args.size(); i++) {
                    spath += args[i] + " ";
                }
                if (args[3][1] != ':') {
                    spath = path + "\\" + spath;
                }

                std::ifstream extfile;
                extfile.open("extlist");
                std::string line;
                std::vector<std::string> Content;
                bool exist = false;

                while (extfile) {
                    std::getline(extfile, line);
                    Content.emplace_back(line);
                    std::stringstream ss(line);
                    ss >> splitstr;
                    if (splitstr == args[2]) {
                        exist = true;
                        break;
                    }
                }
                extfile.close();

                if (exist) {
                    SetConsoleTextAttribute(hConsole, 12);
                    std::cout << "The command already exist\n";
                    SetConsoleTextAttribute(hConsole, 15);
                }
                else {
                    struct  stat buffer;
                    if (stat((spath).c_str(), &buffer) == 0) {
                        std::string cpydir = "move \"" + spath + "\" ./ext/";
                        system(cpydir.c_str());;
                    }

                    for (int j = spath.size() - 1; j > 0; j--) {
                        if (spath[j] == '\\')
                            break;
                        else {
                            filename = spath[j] + filename;
                        }
                    }

                    Content.emplace_back((args[2] + " " + filename));

                    std::ofstream extfile;
                    extfile.open("extlist");
                    for (int i = 0; i < Content.size(); i++) {
                        extfile << Content[i] + "\n";
                    }
                    extfile.close();
                }
            }
            else if (args[1] == "run") {
                if (args.size() != 3) {
                    SetConsoleTextAttribute(hConsole, 12);
                    std::cout << "Invalid argument\n";
                    SetConsoleTextAttribute(hConsole, 15);
                }
                else {
                    std::ifstream extfile;
                    extfile.open("extlist");
                    std::string line, execname;

                    while (extfile) {
                        std::getline(extfile, line);
                        std::stringstream ss(line);
                        ss >> execname >> execname;
                    }
                    extfile.close();

                    char buff[255];
                    _getcwd(buff, 255);
                    std::string current_working_dir(buff);
                    std::string command = current_working_dir + "\\ext\\" + execname;

                    system(("start " + command).c_str());
                }
            }
            else if (args[1] == "del") {
                if (args.size() != 3) {
                    SetConsoleTextAttribute(hConsole, 12);
                    std::cout << "Invalid argument\n";
                    SetConsoleTextAttribute(hConsole, 15);
                }
            }
            else {
                SetConsoleTextAttribute(hConsole, 12);
                std::cout << "Invalid argument\n";
                SetConsoleTextAttribute(hConsole, 15);
            }
        }
        else if (args[0] == "cd") {
            if (args[1] == "..") {
                int start = 0;
                int end = path.find("\\");
                std::string newPath = "";

                while (end != -1) {
                    newPath = path.substr(start, end - start) + "\\";
                    start = end + path.size();
                    end = path.find("\\", start);
                }

                path = newPath;
            }
            else {
                if (args.size() > 2) {
                    for (int i = 2; i < args.size(); i++) {
                        args[1] += " " + args[i];
                    }
                }
                if (args[1][1] == ':') {
                    path = args[1];
                }
                else
                    isPath(path, args[1]);
            }
        }
        else if (args[0] == "dir") {
            if (args.size() == 1) {
                args[0] += " " + path;
                system(args[0].c_str());
            }
            else {
                args[0] += " " + args[1];
                system(args[0].c_str());
            }
        }
        else {
            system(command.c_str());
        }

        if (args[0] != "cls")
            std::cout << std::endl;
        args.clear();
    } while (command != "exit");
}