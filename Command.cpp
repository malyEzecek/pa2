//
// Created by julinka on 19.5.18.
//
#include <arpa/nameser_compat.h>
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
            Cell *newCell = parseStringToCell(temporaryForCutting);
            Model::getInstance()->setValue(yCoor, xCoor, newCell);
            break;
        }
        case CommandType::EXIT : {
            int xCoor, yCoor;
            parseStringToCoordinates(xCoor, yCoor, temporaryForCutting, delimiters);
            //todo save? -> JSON
            // no -> destruktor
            break;
        }
        case CommandType::CLEAR : {
            //todo save? -> JSON
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

void Command::CheckCoordinatesDelimiters(std::vector<char> &  delim, bool * delimiters, bool & finded, std::string & inputString, int & position) const {
    int positionInDelimVector = 0;
    for(; positionInDelimVector < delim.size(); ++positionInDelimVector){
        if(inputString[position] == delim[positionInDelimVector]){
            finded = true;
            break;
        }
    }
    if(finded){
        if(positionInDelimVector == 2){
            delimiters[3] = true;
        } else if( positionInDelimVector == 1){
            delimiters[9] = true;
        }
    }
}


void Command::parseStringToCoordinates(int &xCoor, int &yCoor, std::string &inputString, bool * delimiters) const {
    int position = 0;
    std::vector<char> delim = {' ', ',', ')'};
    for (char character : inputString) {
        if (character == '$')
            break;
        else if (character != ' ')
            throw "Invalid parameter. Try 'help' for more information.\n";
        ++position;
    }
    std::string xCoorString, yCoorString;
    bool first = true, finded = false;
    for (int amount = 0; position < inputString.size(); ++position, ++amount) {
        if (inputString[position] == '$') {
            first = false;
            continue;
        }
        if(first){
            if(inputString[position] < 97 || inputString[position] > 122)
                throw "Invalid parameter. Try 'help' for more information.\n";
            xCoorString += inputString[position];
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

Cell * Command::parseStringToCell(std::string inputString) const {
    //todo delete space
}



