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
public:
    explicit Bool(const bool & newValue);

    CommandType getType() const;
    virtual const Cell & getValue() const;
    virtual Cell & getValue();
    void setValue(const bool & value);
};