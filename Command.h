//
// Created by julinka on 19.5.18.
//
#pragma once
#ifndef EDITOR_COMMAND_H
#define EDITOR_COMMAND_H

#include <vector>
#include <cstdlib>
#include "Model.h"

enum class CommandType {
    CLEAR,
    SET,
    EXIT,
    SAVE,
    LOAD,
    RESIZE
};


class Command {
private:
    CommandType typeOfCommand;
    static const int maxCharInCommand = 6;
    static const int FirstA = 97; // in ASCII code

    CommandType parseToCommand(std::string &inputString, bool *delimiters) const;

    void parseStringToCoordinates(int &xCoor, int &yCoor, std::string &inputString, bool *delimiters) const;

    Cell *parseStringToCell(std::string inputString, bool * delimiters) const;

    CommandType SwitchTypeOfCommand(const std::string &parsedCommand) const;

    void ExecuteCommand(std::string &temporaryForCutting, bool *delimiters) const;

    void deleteThisUgglySpaces( bool *delimiters, std::string & inputString) const;

public:
    Command();

    void SetCommand(const std::string &inputString);

    CommandType returnCommandType() const;

};


#endif //EDITOR_COMMAND_H