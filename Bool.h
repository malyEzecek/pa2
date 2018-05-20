//
// Created by julinka on 10.5.18.
//

#ifndef EDITOR_BOOL_H
#define EDITOR_BOOL_H

#endif //EDITOR_BOOL_H

#include "Cell.h"


class Bool : public Cell {
private:
    bool value;
    const int trueStringSize = 4;
    const int falseStringSize = 5;


public:
    Bool(const bool & newValue);
    CellType getType() const override;
    bool getValue() const;
    bool getValue();
    void setValue(const bool & value);
    const std::string ToString() const override;
    //Bool & operator(const Bool & other);
};