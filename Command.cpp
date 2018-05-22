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

void Command::ExecuteCommand(std::string &temporaryForCutting, bool *delimiters) const {
    switch (typeOfCommand) {
        case CommandType::SET : {
            int xCoor, yCoor;
            parseStringToCoordinates(xCoor, yCoor, temporaryForCutting, delimiters);
            Cell *newCell = parseStringToCell(temporaryForCutting, delimiters);
            Model::getInstance()->setValue(yCoor, xCoor, newCell);
            delete newCell;
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

CommandType Command::parseToCommand(std::string &inputString, bool *delimiters) const {
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
        if (finded)
            break;
        parsedCommand += character;
        ++CharInCommand;
    }
    inputString.erase(0, parsedCommand.size() + 1);
    return SwitchTypeOfCommand(parsedCommand);
}

void Command::ParseToXYString(std::string &inputString, std::string &xCoorString, std::string &yCoorString,
                              std::vector<char> &delim, bool first, bool breakMoment, int &position,
                              bool *delimiters) const {

    for (int amount = 0; position < inputString.size() - 1; ++position, ++amount) {
        if (inputString[position] == '$') {
            first = false;
            continue;
        }
        for (char delimiter : delim) {
            if (inputString[position] == delimiter) {
                breakMoment = true;
                if (delimiter == ',')
                    delimiters[9] = true;
                else if (delimiter == ')')
                    delimiters[3] = true;
                break;
            }
        }
        if (breakMoment)
            break;

        if (first) {
            if (inputString[position] < 97 || inputString[position] > 122)
                throw "Invalid parameter. Try 'help' for more information.\n";
            xCoorString += std::to_string((int) inputString[position] - FirstA);
        } else {
            if (inputString[position] < 48 || inputString[position] > 57)
                throw "Invalid parameter. Try 'help' for more information.\n";
            yCoorString += inputString[position];
        }

        if (amount >= 7)
            throw "Invalid parameter. Try 'help' for more information.\n";
    }
}

void Command::parseStringToCoordinates(int &xCoor, int &yCoor, std::string &inputString, bool *delimiters) const {

    deleteThisUglySpaces(inputString);
    if (inputString[0] != '$')
        throw "Invalid parameter. Try 'help' for more information.\n";
    inputString.erase(0, 1);

    int position = 0;
    std::vector<char> delim = {',', ')', ' '};
    std::string xCoorString, yCoorString;
    bool first = true;
    bool breakMoment = false;

    ParseToXYString(inputString, xCoorString, yCoorString, delim, first, breakMoment, position, delimiters);


    deleteThisUglySpaces(inputString);
    if (!delimiters[9] && !delimiters[3]) {
        if (inputString[0] == ',')
            delimiters[9] = true;
        else if (inputString[0] == ')')
            delimiters[3] = true;
        else
            throw "Invalid parameter. Try 'help' for more information.\n";
    }

    if (xCoorString.size() > 2 || yCoorString.size() > 4)
        throw "Invalid parameter. Try 'help' for more information.\n";
    xCoor = std::stoi(xCoorString);
    yCoor = std::stoi(yCoorString);
    inputString.erase(0, (unsigned long) position + 1);
}

Cell *Command::parseStringToCell(std::string inputString, bool *delimiters) const {
    std::vector<Cell *> possibleCells;
    deleteThisUglySpaces(inputString);
    if (inputString[0] == '"') {
        inputString.erase(0, 1);
        std::string value = parseStringToText(inputString);
        return new Text(value);
    } else {

        if (inputString.substr(0, 4) == "true") {
            parseStringToBool(inputString.erase(0, 4));
            return new Bool(true);
        } else if (inputString.substr(0, 5) == "false") {
            parseStringToBool(inputString.erase(0, 5));
            return new Bool(false);
        } else {
            parseExpression(possibleCells, inputString, delimiters);
        }
    }
}

void Command::deleteThisUglySpaces(std::string &inputString) const {
    int position = 0;
    for (; position < inputString.size(); ++position) {
        if (inputString[position] == ' ')
            continue;
        else {
            break;
        }
    }

    inputString.erase(0, (unsigned long) position);
}


void Command::deleteThisUglySpaces(bool *delimiters, std::string &inputString) const {
    int position = 0;
    for (; position < inputString.size(); ++position) {
        if (inputString[position] == ' ')
            continue;
        else {
            switch (inputString[position]) { // { ' ', '(', '\n', ')', '+', '-', '*', '\', '$', ',' }
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
                default:
                    break;
            }
            break;
        }
    }
    inputString.erase(0, (unsigned long) position);
}

void Command::setAllDelimitersToFalse(bool *delimiters) const {
    for (int i = 0; i < 10; ++i) {
        delimiters[i] = false;
    }
}

std::string Command::parseStringToText(std::string &inputString) const {
    std::string returnText;
    for (char inputChar : inputString) {
        if (inputChar == '"') {
            break;
        }
        if (inputChar == ')' || inputChar == '\n') {
            throw "Invalid parameter. Try 'help' for more information.\n";
        }
        returnText += inputChar;
    }
    deleteThisUglySpaces(inputString);

    if (inputString[0] != ')')
        throw "Invalid parameter. Try 'help' for more information.\n";
    inputString.erase(0, 1);
    deleteThisUglySpaces(inputString);

    if (inputString[0] != '\n')
        throw "Invalid parameter. Try 'help' for more information.\n";
}

void Command::parseStringToBool(std::string &inputString) const {
    deleteThisUglySpaces(inputString);
    if (inputString[0] != ')')
        throw "Invalid parameter. Try 'help' for more information.\n";
    inputString.erase(0, 1);
    deleteThisUglySpaces(inputString);

    if (inputString[0] != '\n')
        throw "Invalid parameter. Try 'help' for more information.\n";
}

void Command::parseExpression(std::vector<Cell *> &possibleCells, std::string &inputString, bool *delimiters) const {
    deleteThisUglySpaces(inputString);
    for (char inputCharacter : inputString) {
        if (inputCharacter == '$'){
            int xCoor, yCoor;
            parseStringToCoordinates(xCoor, yCoor, inputString, delimiters);
            possibleCells.push_back(new Reference(xCoor, yCoor));
        } else if( inputCharacter > 48 && inputCharacter < 57){
            std::string number;
            parseStringToNumber(inputString, number);
            double cellNumber = std::stod(number);
        }


    }

}

void Command::parseStringToNumber(std::string &inputString, std::string &number) const {

}

