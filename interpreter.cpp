#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <map>
#include <iterator>
#include <sstream>
#include <Windows.h>
#include <cassert>
#include <cstring>

#include "bcin.h"
#include "interpreter.h"

void errorMsg(std::string alert) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);
    std::cout << alert;
    SetConsoleTextAttribute(hConsole, 15);
}

void interpret(
    std::string& command,
    std::map<std::string, std::string>& Val,
    std::map<std::string, std::vector<std::string>>& List,
    std::string& path,
    int& userColor,
    int& pathColor
) {


    std::vector<std::string> splitCommand;
    std::stringstream ss(command);
    std::string tempstr;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (ss >> tempstr) {
        splitCommand.emplace_back(tempstr);
    }

    try {
        /*
        Variables:
        Example of variable definition:
        $variable_name = "text"
        $variable_name = $other_variable
        $variable_name = @list "1"
        $variable_name = @list $index
        */
        if (splitCommand[0][0] == '$') {
            if (splitCommand.size() < 3) {
                errorMsg("Invalid argument\n");
            }
            else if (splitCommand[1] == "=") {
                // not existing
                if (Val.find(splitCommand[0]) == Val.end()) {
                    // $variable_name = "text"
                    if (splitCommand[2][0] == '"' && splitCommand[splitCommand.size() - 1][splitCommand[splitCommand.size() - 1].size() - 1] == '"') {
                        std::string strvalue = "";
                        for (int i = 2; i < splitCommand.size(); i++) {
                            strvalue += splitCommand[i] + " ";
                        }
                        Val.insert({ splitCommand[0], strvalue.substr(1, strvalue.size() - 3) });
                        std::cout << splitCommand[0] << ": " << strvalue.substr(1, strvalue.size() - 3) << "\n";
                    }
                    // $variable_name = $other_variable
                    else if (splitCommand[2][0]== '$' && splitCommand.size() == 3) {
                        auto val2 = Val.find(splitCommand[2]);
                        if (val2 == Val.end()) {
                            errorMsg("Invalid argument\n");
                        }
                        else {
                            Val.insert({ splitCommand[0], val2->second });
                            std::cout << splitCommand[0] << ": " << val2->second << "\n";
                        }
                    }
                    else {
                        errorMsg("Invalid argument\n");
                    }
                }
                // existing
                else {
                    // $variable_name = "text"
                    if (splitCommand[2][0] == '"' && splitCommand[splitCommand.size() - 1][splitCommand[splitCommand.size() - 1].size() - 1] == '"') {
                        std::string strvalue = "";
                        for (int i = 2; i < splitCommand.size(); i++) {
                            strvalue += splitCommand[i] + " ";
                        }
                        auto it = Val.find(splitCommand[0]);
                        it->second = strvalue.substr(1, strvalue.size() - 3);
                        std::cout << splitCommand[0] << ": " << strvalue.substr(1, strvalue.size() - 3) << "\n";
                    }
                    // $variable_name = $other_variable
                    else if (splitCommand[2][0] == '$' && splitCommand.size() == 3) {
                        auto val2 = Val.find(splitCommand[2]);
                        if (val2 == Val.end()) {
                            errorMsg("Invalid argument\n");
                        }
                        else {
                            auto it = Val.find(splitCommand[0]);
                            it->second = val2->second;
                            std::cout << splitCommand[0] << ": " << val2->second << "\n";
                        }
                    }
                    else {
                        errorMsg("Invalid argument\n");
                    }
                }
            }
        }
        /*
        List:
        Example of list definition:
        @list -add "possible text" | $variable ...
        @list -del "content"
        @list -del $variable
        Example of change value
        @list "1" = "content"
        @list "1" = $variable
        @list $variable = "content"
        @list $variable = $variable
        Example of list
        @list -list 
        @list -size
        */
        else if (splitCommand[0][0] == '@') {
            if (splitCommand.size() < 2) {
                errorMsg("Invalid argument\n");
            }
            else {
                auto it = List.find(splitCommand[0]);
                if (it == List.end()) {
                    if (splitCommand[1] == "-add" && splitCommand.size() > 2) {
                        std::vector<std::string> instr;
                        std::string temp;

                        // split | to get values

                        for (int i = 2; i < splitCommand.size(); i++) {
                            if (splitCommand[i] != "|") {
                                temp += splitCommand[i] + " ";
                            }
                            else {
                                instr.emplace_back(temp.substr(1, temp.size() - 3));
                                temp = "";
                            }
                        }
                        instr.emplace_back(temp.substr(1, temp.size() - 3));
                        temp = "";

                        std::cout << splitCommand[0] << ": ";
                        for (int i = 0; i < instr.size() - 1; i++) {
                            std::cout << instr[i] << " | ";
                        }
                        std::cout << instr[instr.size() - 1] << "\n";

                        List.insert({ splitCommand[0], instr });
                        instr.clear();
                    }
                    else if (splitCommand[1] == "-list" || splitCommand[1] == "-del") {
                        errorMsg("Invalid argument\n");
                    }
                    else if (splitCommand[1][0] == '"' || splitCommand[1][0] == '$') {
                        errorMsg("Invalid argument\n");
                    }
                    else {
                        errorMsg("Invalid argument\n");
                    }
                }
                else {
                    if (splitCommand[1] == "-add") {
                    }
                    else if (splitCommand[1] == "-list") {
                        std::cout << splitCommand[0] << ": ";
                        for (int i = 0; i < it->second.size() - 1; i++) {
                            std::cout << it->second[i] << " | ";
                        }
                        std::cout << it->second[it->second.size() - 1] << "\n";
                    }
                    else if (splitCommand[1][0] == '"' || splitCommand[1][0] == '$') {
                        errorMsg("Invalid argument\n");
                    }
                    else {
                        errorMsg("Invalid argument\n");
                    }
                }
            }
        }
        else {
            if (splitCommand[0] == "print" || splitCommand[0] == "echo") {

            }
            else if (splitCommand[0] == "clear" || splitCommand[0] == "cls") {
                system("cls");
            }
            else if (splitCommand[0] == "title") {
                if (splitCommand[1] == "-set") {

                }
                else if (splitCommand[1] == "-reset" && splitCommand.size() == 2) {
                    SetConsoleTitleW(L"Better CMD");
                }
                else
                    errorMsg("Invalid syntax\n");
            }
            else if (splitCommand[0] == "color") {

            }
            else if (splitCommand[0] == "exit") {}
            else {
                errorMsg("Invalid argument\n");
            }
        }
    }
    catch (...) {
        errorMsg("Invalid argument\n");
    }
}
