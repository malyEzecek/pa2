//
// Created by julinka on 9.5.18.
//

#pragma once
#ifndef EDITOR_CELL_H
#define EDITOR_CELL_H

#endif //EDITOR_CELL_H

#include <string>
#include <vector>

enum class CellType {
    BOOLEAN,
    TEXT,
    REFERENCE,
    EXPRESSION,
    NUMBER,
    OPERATION
};

class Cell {
private:
    int sizeOfCell;

protected:
    static const int defaultWidthOfCell = 11; // defaultni nastaveni pro promennou mode;
    int mode;

    std::string editToWideOfCell(const std::string &editString) const;

public:
    Cell();

    virtual ~Cell() {}

    int getCellSize() const;

    virtual CellType getType() const = 0;

    virtual const std::string ToString() const = 0;

    virtual Cell *clone() const = 0;

    virtual void evaluate(std::vector<const Cell *> & inputVector) const = 0;

    virtual const Cell * getValue() const = 0;
};