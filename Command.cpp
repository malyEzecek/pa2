
//
// Created by julinka on 19.5.18.
//

#include <cstdlib>
#include "Command.h"

Command::Command() {}

CommandType Command::returnCommandType() const {
    return typeOfCommand;
}

// Insert(A14, A5 + B7 + 14 + 15);

void Command::ExecuteCommand(std::string &temporaryForCutting, bool * delimiters) const {
    switch (typeOfCommand) {
        case CommandType::SET : {
            int xCoor, yCoor;
            parseStringToCoordinates(xCoor, yCoor, temporaryForCutting, delimiters);
            Cell *newCell = parseStringToCell(temporaryForCutting, delimiters);
            Model::getInstance()->setValue(yCoor, xCoor, newCell);
            break;
        }
        case CommandType::EXIT : {
            //todo save? -> JSON
            // no -> destruktor
            break;
        }
        case CommandType::CLEAR : {
            int xCoor, yCoor;
            parseStringToCoordinates(xCoor, yCoor, temporaryForCutting, delimiters);
            // no -> destruktor
        }
        case CommandType::RESIZE : {
            break;
        }
        case CommandType::LOAD : {
            break;
        }
        case CommandType::SAVE : {
            break;
        }
    }
}

void Command::SetCommand(const std::string &inputString) {
    std::string temporaryForCutting = inputString;
    bool delimiters[] = {false, false, false, false, false, false, false,
                         false, false, false}; // { ' ', '(', '\n', ')', '+', '-', '*', '\', '$', ',' }
    Command::typeOfCommand = parseToCommand(temporaryForCutting, delimiters);

    if (typeOfCommand == CommandType::EXIT) {
        if (!delimiters[2]) {
            throw "This command doesn't exist. Try 'help' for more information.\n";
        }
    } else {
        if (!delimiters[1]) {
            throw "This command doesn't exist. Try 'help' for more information.\n";
        }
    }
    ExecuteCommand(temporaryForCutting, delimiters);

}

CommandType Command::SwitchTypeOfCommand(const std::string &parsedCommand) const {
    if (parsedCommand == "clear") {
        return CommandType::CLEAR;
    } else if (parsedCommand == "set") {
        return CommandType::SET;
    } else if (parsedCommand == "exit") {
        return CommandType::EXIT;
    } else if (parsedCommand == "save") {
        return CommandType::SAVE;
    } else if (parsedCommand == "load") {
        return CommandType::LOAD;
    } else if (parsedCommand == "resize") {
        return CommandType::RESIZE;
    } else
        throw "This command doesn't exist. Try 'help' for more information.\n";
}

CommandType Command::parseToCommand(std::string &inputString, bool * delimiters) const {
    std::string parsedCommand;
    if (inputString[0] != 'c' && inputString[0] != 'e' && inputString[0] != 's'
        && inputString[0] != 'l' && inputString[0] != 'r' && inputString[0] != 'h')
        throw "This command doesn't exist. Try 'help' for more information.\n";
    std::vector<char> delim = {' ', '(', '\n'};

    int CharInCommand = 0;
    bool finded = false;
    for (char character : inputString) {
        if (CharInCommand == maxCharInCommand) { // prekroceni maximalniho poctu charu v libovolnem existujicim prikazu
            break;
        }

        for (int i = 0; i < delim.size(); ++i) {
            if (character == delim[i]) {
                delimiters[i] = true;
                finded = true;
                break;
            }
        }
        if(finded)
            break;
        parsedCommand += character;
        ++CharInCommand;
    }
    inputString.erase(0, parsedCommand.size() + 1);
    return SwitchTypeOfCommand(parsedCommand);
}


void Command::parseStringToCoordinates(int &xCoor, int &yCoor, std::string &inputString, bool * delimiters) const {
    int position = 0;
    std::vector<char> delim = { ',', ')', ' '};
    for (char character : inputString) {
        if (character == '$'){
            ++position;
            break;
        }
        else if (character != ' ')
            throw "Invalid parameter. Try 'help' for more information.\n";
        ++position;
    }
    std::string xCoorString, yCoorString;
    bool first = true, finded = false;
    bool breakMoment = false;
    for (int amount = 0; position < inputString.size() -1; ++position, ++amount) {
        if (inputString[position] == '$') {
            first = false;
            continue;
        }
        for(char delimiter : delim){
            if(inputString[position] == delimiter){
                breakMoment = true;
                if(delimiter == ',')
                    delimiters[9] = true;
                else if(delimiter == ')')
                    delimiters[2] = true;
                break;

            }
        }
        if (breakMoment)
            break;

        if(first){
            if(inputString[position] < 97 || inputString[position] > 122)
                throw "Invalid parameter. Try 'help' for more information.\n";
            xCoorString += std::to_string((int)inputString[position] - FirstA);
        } else {
            if(inputString[position] < 48 || inputString[position] > 57)
                throw "Invalid parameter. Try 'help' for more information.\n";
            yCoorString += inputString[position];
        }

        if( amount >= 7)
            throw "Invalid parameter. Try 'help' for more information.\n";
    }
//todo delete space
    if(xCoorString.size() > 2 || yCoorString.size() > 4 || ( !delimiters[9] && !delimiters[3]))
        throw "Invalid parameter. Try 'help' for more information.\n";
    xCoor = std::stoi(xCoorString);
    yCoor = std::stoi(yCoorString);
    inputString.erase(0, (unsigned long) position + 1);

}

Cell * Command::parseStringToCell(std::string inputString, bool * delimiters) const {
    std::vector<std::string> possibleCells;
    deleteThisUgglySpaces(delimiters, inputString);
    if(inputString[0] == '"'){
        std::string value = parseStringToText(inputString);
    } else {
        if(inputString.substr(0, 4) == "true" || inputString.substr(0, 5) == "false")
    }
}

void Command::deleteThisUgglySpaces(bool *delimiters, std::string & inputString) const {
    int position = 0;
    for(; position < inputString.size(); ++position ){
        if(inputString[position ] == ' ')
            continue;
        else{
            switch(inputString[position]){ // { ' ', '(', '\n', ')', '+', '-', '*', '\', '$', ',' }
                case ' ': {
                    delimiters[0] = true;
                    break;
                }
                case '(': {
                    delimiters[1] = true;
                    break;
                }
                case '\n': {
                    delimiters[2] = true;
                    break;
                }
                case ')': {
                    delimiters[3] = true;
                    break;
                }
                case '+': {
                    delimiters[4] = true;
                    break;
                }
                case '-' : {
                    delimiters[5] = true;
                    break;
                }
                case '*': {
                    delimiters[6] = true;
                    break;
                }
                case '/': {
                    delimiters[7] = true;
                    break;
                }
                case '$': {
                    delimiters[8] = true;
                    break;
                }
                case ',': {
                    delimiters[9] = true;
                    break;
                }
                default: break;
            }
            break;
        }
    }
    inputString.erase(0, (unsigned long)position);
}
