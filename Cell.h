//
// Created by julinka on 9.5.18.
//

#ifndef EDITOR_CELL_H
#define EDITOR_CELL_H

#endif //EDITOR_CELL_H

#include <string>

enum class CommandType {
    BOOLEAN = 0,
    TEXT = 1,
    REFERENCE= 2,
    EXPRESSION = 3,
    NUMBER = 4,
    OPERATION = 5,
    BASICOPERATOR = 6
};

struct Cell{
private:
    int sizeOfCell;

protected:
    const int defaultWidthOfCell = 11; // defaultni nastaveni pro promennou mode;
    int mode;
    std::string editToWideOfCell(const std::string & editString) const;

public:
    Cell();
    virtual ~Cell() {}
    int getCellSize() const;
    virtual CommandType getType() const = 0;
    virtual const std::string ToString() const = 0;
};
