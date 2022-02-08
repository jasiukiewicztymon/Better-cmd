#include <iostream>
#include <map>
#include <vector>
#include <stdexcept>
#include <string>

#include "interpreter.h"
#include "bcin.h"

std::string command, path = "c:\\";
std::vector<std::string> Keywords = {"cat", "cd", "clear", "cls", "cmd", "date", "del", "dir", "disk",
                                     "elif", "else", "exit", "func", "help", "if", "loop", "ls", "mkdir", 
                                     "move", "print", "powershell", "ps", "rmdir", "title"};

std::map<std::string, std::string> Val;
std::map<std::string, std::string> Function;
std::map<std::string, std::vector<std::string>> List;

int main(int argc, char* argv[]) {
    do {
        bcin(command, " >", Val, Function, List, Keywords);
        interpret(command, Val, List, Function, path);
    } while (command != "exit");
}
