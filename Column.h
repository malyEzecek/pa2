//
// Created by julinka on 2.5.18.
//

#include <vector>

#ifndef EDITOR_COLUMN_H
#define EDITOR_COLUMN_H

#endif //EDITOR_COLUMN_H
class Column{
private:
    int size;
    /**
     * todo include CELL
     */
    std::vector<int> cells;

    void setSize(const int & size);
    int getSize() const;

};