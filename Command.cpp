//
// Created by julinka on 19.5.18.
//
#include <arpa/nameser_compat.h>
#include "Command.h"

CommandType Command::returnCommandType() const {
    return typeOfCommand;
}

// Insert(A14, A5 + B7 + 14 + 15);

void Command::SetCommand( const std::string & inputString) {
    std::string temporaryForCutting = inputString;
    Command::typeOfCommand = parseToCommand(temporaryForCutting);

    switch(typeOfCommand){
        case CommandType::SET : {
            int xCoor, yCoor;
            parseStringToCoordinates(xCoor, yCoor, temporaryForCutting);
            Cell newCell = parseStringToCell(temporaryForCutting);
            Model::getInstance()->setValue(yCoor, xCoor, newCell);
            break;
        }
        case CommandType::EXIT : {
            //todo save? -> JSON
            // no -> destruktor
            break;
        }
        case CommandType::CLEAR : {
            //todo save? -> JSON
            // no -> destruktor
        }
    }
}

CommandType Command::parseToCommand(std::string &inputString) const {
    //todo
}

Command::Command() {}

void Command::parseStringToCoordinates(int & xCoor, int & yCoor, std::string & inputString) {
    //todo
}

Cell Command::parseStringToCell(std::string inputString) {
    //todo
}

