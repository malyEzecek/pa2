//
// Created by julinka on 11.5.18.
//

#ifndef EDITOR_TEXT_H
#define EDITOR_TEXT_H

#endif //EDITOR_TEXT_H

#include "Cell.h"

class Text : public Cell {
public:
    std::string text;

private:

    explicit Text(const std::string & newText);

    CellType getType() const override;
    const std::string & getValue() const;
    std::string & getValue();
    void setValue(const std::string & newText);
    const std::string ToString() const override;
};
