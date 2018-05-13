//
// Created by julinka on 2.5.18.
//

#include <vector>
#include "Cell.h"

#ifndef EDITOR_COLUMN_H
#define EDITOR_COLUMN_H

#endif //EDITOR_COLUMN_H

class Column{
private:
    int size;

    std::vector<Cell *> cells;

public:
//    Column(const int & size)
    void setSize(const int & size);
    int getSize() const;

};