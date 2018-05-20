//
// Created by julinka on 19.5.18.
//
#pragma once
#ifndef EDITOR_COMMAND_H
#define EDITOR_COMMAND_H

#include <vector>
#include <cstdlib>
#include "Model.h"

enum class CommandType{
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

    CommandType parseToCommand(std::string & inputString, bool * delimiters ) const;
    void parseStringToCoordinates(int & xCoor, int & yCoor, std::string & inputString, bool * delimiters) const;
    Cell * parseStringToCell(std::string inputString) const;
    CommandType SwitchTypeOfCommand(const std::string & parsedCommand) const;
    void ExecuteCommand(std::string & temporaryForCutting, bool * delimiters) const;
    void CheckCoordinatesDelimiters(std::vector<char> &  delim, bool * delimiters, bool & finded, std::string & inputString, int & position) const;


public:
    Command();
    void SetCommand(const std::string & inputString);
    CommandType returnCommandType() const;

};


#endif //EDITOR_COMMAND_H
