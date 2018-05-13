//
// Created by julinka on 11.5.18.
//

#ifndef EDITOR_REFERENCE_H
#define EDITOR_REFERENCE_H

#endif //EDITOR_REFERENCE_H

#include "Cell.h"
#include <string>

class Reference : public Cell {
private:
    std::string position;

public:
    explicit Reference(const std::string & newPosition);

    virtual CommandType getType() const;
    virtual const Cell & getValue() const;
    virtual Cell & getValue();
    void setValue(const std::string & newPosition);
    int getXCoor() const;
    int getYCoor() const;

};