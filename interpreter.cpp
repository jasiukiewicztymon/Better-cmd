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
                }
            }
        }
        /*
        List:
        Example of list definition:
        @list -add "possible text" | $variable ...
        @list -del "content"
        @list -del $variable
        */
        else if (splitCommand[0][0] == '@') {
            std::map<std::string, std::vector<std::string>>::iterator it = List.find(splitCommand[0]);
            if (splitCommand.size() == 1) {
                errorMsg("Invalid argument\n");
            }
            else if (splitCommand[1] == "-add" && splitCommand.size() >= 3) {
                bool isok = true, isstring = false;
                std::vector<std::string> Vstr;
                std::string tempstr;

                for (int i = 2; i < splitCommand.size(); i++) {
                    if (isstring) {

                    }
                    else if (splitCommand[i][0] == '$') {

                    }
                    else if (splitCommand[i][0] == '@') {

                    }
                    else if (splitCommand[i][0] == '"') {
                        if (splitCommand[i][splitCommand[i].size() - 1] == '"') {
                            Vstr.emplace_back(splitCommand[i].substr(1, splitCommand[i].size() - 1));
                        }
                        else {
                            tempstr = splitCommand[i].substr(1, splitCommand[i].size());
                            isstring = true;
                        }
                    }
                    else {
                        isok = false;
                        break;
                    }
                }

                if (isok && !isstring) {
                    if (it == List.end()) {
                        List.insert(std::pair<std::string, std::vector<std::string>>(splitCommand[0], Vstr));
                    }
                    else {
                        for (int j = 0; j < Vstr.size(); j++) {
                            it->second.emplace_back(Vstr[j]);
                        }
                    }
                }
            }
            else if (splitCommand[1] == "-del" && splitCommand.size() == 3) {
                auto vfind = std::find(it->second.begin(), it->second.end(), splitCommand[2]);
                it->second.erase(vfind);
            }
            else if (splitCommand[1] == "-list" && splitCommand.size() == 2) {
                auto ittemp = List.find(splitCommand[0]);
                if (ittemp != List.end()) {
                    for (int i = 0; i < ittemp->second.size(); i++) {
                        std::cout << List.find(splitCommand[0])->second[i] << ";";
                    }
                    std::cout << "\n";
                }
                else {
                    errorMsg("Invalid list name\n");
                }
            }
            else if (splitCommand[1] == "-size" && splitCommand.size() == 2) {
                auto ittemp = List.find(splitCommand[0]);
                if (ittemp != List.end()) {
                    std::cout << ittemp->second.size() << "\n";
                }
                else {
                    errorMsg("Invalid list name\n");
                }
            }
            else {
                errorMsg("Invalid argument\n");
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
