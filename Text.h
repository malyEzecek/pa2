//
// Created by julinka on 11.5.18.
//

#ifndef EDITOR_TEXT_H
#define EDITOR_TEXT_H

#endif //EDITOR_TEXT_H

#include "Cell.h"
#include <string>

class Text : public Cell {
public:
    std::string text;

private:

    explicit Text(const std::string newText);

    virtual CommandType getType() const;
    virtual const Cell & getValue() const;
    virtual Cell & getValue();
    void setValue(const std::string newText);
};
