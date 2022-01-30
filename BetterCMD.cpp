#include <iostream>
#include <Windows.h>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <Lmcons.h>

#include <direct.h>
#include <limits.h>
#include <process.h>

#include "mainext.h"

#ifndef _UNISTD_H
#define _UNISTD_H    1

#include <stdlib.h>
#include <io.h>
#include <process.h> 
#include <direct.h> 

#define srandom srand
#define random rand

#define R_OK    4       
#define W_OK    2       
#define F_OK    0   

#define access _access
#define dup2 _dup2
#define execve _execve
#define ftruncate _chsize
#define unlink _unlink
#define fileno _fileno
#define getcwd _getcwd
#define chdir _chdir
#define isatty _isatty
#define lseek _lseek

#ifdef _WIN64
#define ssize_t __int64
#else
#define ssize_t long
#endif

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#endif

#include <Lmcons.h>

int main() {
    system("cls");

    SetConsoleTitleA("BetterCMD");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::string command = "", extention = "Main", path = "c:\\";

    SetConsoleTextAttribute(hConsole, 15);

    std::cout << "\n     ____       __  __               ________  _______ \n";
    std::cout << "    / __ )___  / /_/ /____  _____   / ____/  |/  / __ \\\n";
    std::cout << "   / __  / _ \\/ __/ __/ _ \\/ ___/  / /   / /|_/ / / / /\n";
    std::cout << "  / /_/ /  __/ /_/ /_/  __/ /     / /___/ /  / / /_/ / \n";
    std::cout << " /_____/\\___/\\__/\__/\\____/_/      \\____/_/  /_/_____/  \n";
    std::cout << "\n Github: jasiukiewicztymon | --help\n\n\n";

    TCHAR username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    GetUserName(username, &username_len);

    std::wstring wusername(&username[0]);
    std::string usertype(wusername.begin(), wusername.end());

    do {
        showHeader(extention, path, usertype);
        getline(std::cin, command);

        std::cout << std::endl;

        std::stringstream ss(command);
        std::string splitstr;
        std::vector<std::string> args;

        while (ss >> splitstr) {
            std::transform(splitstr.begin(), splitstr.end(), splitstr.begin(),
                [](unsigned char c) { return std::tolower(c); });
            args.emplace_back(splitstr);
        }

        if (args[0] == "ext") {
            std::ifstream xfile;
            std::string lines;
            xfile.open("./ext/extlist");
            if (!xfile) {
                _mkdir("ext");
                std::fstream wfile;
                wfile.open("./ext/extlist", std::ios_base::app);
                wfile.write("\n", 1);
            }
            xfile.close();
            if (args[1] == "set") {
                std::string name = args[2], spath = "", filename = "";
                for (int i = 3; i < args.size(); i++) {
                    spath += args[i] + " ";
                }
                if (args[3][1] != ':') {
                    spath = path + "\\" + spath;
                }
                xfile.open(spath);
                if (xfile) {
                    std::ifstream extfile;
                    extfile.open("./ext/extlist");
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
                        errorText("The command already exist");
                    }
                    else {
                        std::string rpath = spath, newpath = "";
                        int start = 0;
                        int end = rpath.find("\\");
                        while (end != -1) {
                            newpath += rpath.substr(start, end - start) + "\\";
                            start = end + 1;
                            end = rpath.find("\\", start);
                        }
                        newpath += 's' + rpath.substr(start, end - start);

                        std::ofstream wfile(newpath);
                        std::ifstream inputfile(spath);

                        wfile << inputfile.rdbuf();

                        wfile.close();
                        inputfile.close();

                        struct  stat buffer;
                        if (stat((newpath).c_str(), &buffer) == 0) {
                            std::string cpydir = "move \"" + newpath + "\" ./ext/";
                            system(cpydir.c_str());;
                        }

                        for (int j = newpath.size() - 1; j > 0; j--) {
                            if (newpath[j] == '\\')
                                break;
                            else {
                                filename = newpath[j] + filename;
                            }
                        }

                        Content.emplace_back((args[2] + " " + filename));

                        std::ofstream extfile;
                        extfile.open("./ext/extlist");
                        for (int i = 0; i < Content.size(); i++) {
                            extfile << Content[i] + "\n";
                        }
                        extfile.close();
                        std::cout << "\tThe command has been setted\n";
                    }
                }
                else {
                    errorText("Invalid path");
                }
            }
            else if (args[1] == "run") {
                if (args.size() != 3) {
                    errorText("Invalid argument");
                }
                else {
                    std::ifstream extfile;
                    extfile.open("./ext/extlist");
                    std::string line, execname, name;
                    bool exist = false;

                    while (extfile) {
                        std::getline(extfile, line);
                        std::stringstream ss(line);
                        ss >> name >> execname;
                        if (name == args[2]) {
                            exist = true;
                            break;
                        }
                    }
                    extfile.close();

                    if (exist) {
                        char buff[255];
                        _getcwd(buff, 255);
                        std::string current_working_dir(buff);
                        std::string command = current_working_dir + "\\ext\\" + execname;

                        system(("start " + command).c_str());
                    }
                    else {
                        errorText("The extension doesn't exist");
                    }
                }
            }
            else if (args[1] == "del") {
                if (args.size() != 3) {
                    errorText("Invalid argument");
                }
                else {
                    std::ifstream extfile;
                    extfile.open("./ext/extlist");
                    std::string line, delfile;
                    std::vector<std::string> Content;
                    bool exist = false;

                    while (extfile) {
                        std::getline(extfile, line);
                        std::stringstream ss(line);
                        ss >> splitstr >> delfile;
                        if (splitstr == args[2]) {
                            exist = true;
                            continue;
                        }
                        Content.emplace_back(line);
                    }
                    extfile.close();

                    std::ofstream outfile;
                    outfile.open("./ext/extlist", std::ios::out | std::ios::trunc);
                    for (int i = 0; i < Content.size(); i++) {
                        outfile << Content[i] + "\n";
                    }
                    outfile.close();

                    if (exist) {
                        remove(("./ext/" + delfile).c_str());
                        std::cout << "The command has been removed\n";
                    }
                    else {
                        std::cout << "This command already doesn't exist\n";
                    }
                }
            }
            else if (args[1] == "list") {
                std::ifstream inFile;
                inFile.open("./ext/extlist");

                std::stringstream strStream;
                strStream << inFile.rdbuf();
                std::string str = strStream.str();

                int start = 0;
                int end = str.find("\n");
                bool notfound = true;
                while (end != -1) {
                    if (str.substr(start, end - start) != "") {
                        std::cout << str.substr(start, end - start) << "\n";
                        notfound = false;
                    }
                    start = end + 1;
                    end = str.find("\n", start);
                }
                if (str.substr(start, end - start) != "") {
                    std::cout << str.substr(start, end - start) << "\n";
                    notfound = false;
                }
                if (notfound)
                    std::cout << "The list is empty\n";
            }
            else {
                errorText("Invalid argument");
            }
        }
        else if (args[0] == "compare") {
            if (args.size() != 3) {
                errorText("Invalid argument");
            }
            else {
                if (args[1][1] != ':') {
                    args[1] = path + "\\" + args[1];
                }
                if (args[2][1] != ':') {
                    args[2] = path + "\\" + args[2];
                }

                std::ifstream path1(args[1]);
                std::ifstream path2(args[2]);
                std::string line;

                std::vector<std::string> Path1, Path2;

                while (std::getline(path1, line)) {
                    Path1.emplace_back(line);
                }
                while (std::getline(path2, line)) {
                    Path2.emplace_back(line);
                }

                int minSize;
                if (Path1.size() < Path2.size())
                    minSize = Path1.size();
                else
                    minSize = Path2.size();

                for (int j = 0; j < minSize; j++) {
                    if (Path1[j] == Path2[j]) {
                        SetConsoleTextAttribute(hConsole, 10);
                        std::cout << Path1[j] << "\n";
                        SetConsoleTextAttribute(hConsole, 15);
                    }
                    else {
                        SetConsoleTextAttribute(hConsole, 12);
                        std::cout << Path1[j] << " | " << Path2[j] << "\n";
                        SetConsoleTextAttribute(hConsole, 15);
                    }
                }

                if (Path1.size() < Path2.size()) {
                    for (int j = minSize; j < Path2.size(); j++) {
                        SetConsoleTextAttribute(hConsole, 12);
                        std::cout << Path2[j] << "\n";
                        SetConsoleTextAttribute(hConsole, 15);
                    }
                }
                else {
                    for (int j = minSize; j < Path1.size(); j++) {
                        SetConsoleTextAttribute(hConsole, 12);
                        std::cout << Path1[j] << "\n";
                        SetConsoleTextAttribute(hConsole, 15);
                    }
                }

                Path1.clear();
                Path2.clear();
            }
        }
        else if (args[0] == "--help") {
            showHelp();
        }
        else if (args[0] == "color") {
            errorText("Color argument is disable");
        }
        else if (args[0] == "cat") {
            std::string spath;
            if (args[1][1] == ':') {
                spath = args[1];
            }
            else {
                spath = path + "\\" + args[1];
            }

            std::ifstream ifile;
            std::string line;
            ifile.open(spath);
            if (ifile) {
                while (std::getline(ifile, line)) {
                    std::cout << line << "\n";
                }
            }
            else {
                std::cout << "File doesn't exist\n";
            }
        }
        else if (args[0] == "cd") {
            if (args[1] == "..") {
                std::vector<std::string> V;
                char del = '\\';
                std::string s = path;
                int start = 0;
                int end = s.find(del);
                while (end != -1) {
                    V.emplace_back(s.substr(start, end - start));
                    start = end + 1;
                    end = s.find(del, start);
                }

                std::string vstr = path;
                path = "";
                for (int i = 0; i < V.size(); i++) {
                    path = path + V[i] + '\\';
                }
                if (path == vstr) {
                    path = "";
                    for (int i = 0; i < V.size() - 1; i++) {
                        path = path + V[i] + '\\';
                    }
                }
                if (path == "") {
                    path = "c:\\";
                }
                V.clear();
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
        else if (args[0] == "dir" || args[0] == "ls") {
            if (args[0] == "ls")
                args[0] = "dir";
            if (args.size() == 1) {
                args[0] += " " + path;
                system(args[0].c_str());
            }
            else {
                args[0] += " " + args[1];
                system(args[0].c_str());
            }
        }
        else if (args[0] == "mkdir") {
            if (args.size() == 1) {
                args[0] += " " + path;
                system(args[0].c_str());
            }
            else {
                if (args[1][1] != ':') {
                    args[1] = path + args[1];
                }
                args[0] += " " + args[1];
                system(args[0].c_str());
            }
        }
        else if (args[0] == "rmdir") {
            if (args.size() == 1) {
                args[0] += " " + path;
                system(args[0].c_str());
            }
            else {
                if (args[1][1] != ':') {
                    args[1] = path + args[1];
                }
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