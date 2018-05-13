//
// Created by julinka on 9.5.18.
//

#ifndef EDITOR_CELL_H
#define EDITOR_CELL_H

#endif //EDITOR_CELL_H
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
public:
    Cell();
    virtual ~Cell();
    int getCellSize() const;
    virtual CommandType getType() const {}
    virtual const Cell & getValue() const {}
    virtual Cell & getValue() {}
};
