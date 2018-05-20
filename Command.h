//
// Created by julinka on 19.5.18.
//

#ifndef EDITOR_COMMAND_H
#define EDITOR_COMMAND_H

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
    CommandType parseToCommand(std::string & inputString) const;
    void parseStringToCoordinates(int & xCoor, int & yCoor, std::string & inputString);
    CommandType typeOfCommand;
    Cell parseStringToCell(std::string inputString);

public:
    Command();
    void SetCommand(const std::string & inputString);
    CommandType returnCommandType() const;

};


#endif //EDITOR_COMMAND_H
