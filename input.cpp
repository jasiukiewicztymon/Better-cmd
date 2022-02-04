#include <Windows.h>
#include <string>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <vector>
#include <map>

/*
	Arguments: To use all the possibilities of the bcin
	function and get correction and syntax help pass a vector
	of command with the map key as the command and the vector
	of string as parameter of possibilities, next pass the
	variable vector, list vector, function vector (having a
	pointer to the function from a class)
*/

std::string output = "";
char move;
int cox = 0, coy = 0;

void CheckKey();

std::string bcin(std::map<std::string, std::vector<std::string>> commandSyntax, std::vector<std::string> variable, std::vector<std::vector<std::string>> list, std::vector<std::vector<std::string>> function) {
	std::vector<std::string> keywords;

	for (std::map<std::string, std::vector<std::string>>::iterator it = commandSyntax.begin(); it != commandSyntax.end(); ++it) {
		keywords.emplace_back(it->first);
	}

    while (1) {

    }
}

void CheckKey() {
    int key;
    if (_kbhit()) {
        key = _getch();
        if (key == 224) {
            do {
                key = _getch();
            } while (key == 224);
            switch (key) {
            case 75:
                move = 'l';
                break;
            case 77:
                move = 'r';
                break;
            }
        }
        else {
            char ch = key;
            if (ch == 8) {
                // backspace
            }
            if (ch == 127) {
                // delete
            }
            else {
                output += ch;
            }
        }
    }
}
