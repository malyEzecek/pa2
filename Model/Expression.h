//
// Created by julinka on 12.5.18.
//

#pragma once
#ifndef EDITOR_EXPRESSION_H
#define EDITOR_EXPRESSION_H

#include <vector>
#include "Cell.h"

class Expression : public Cell {
private:

    std::vector<Cell *> parsedStringToCells;
    bool reference;
public:
    Expression();

    explicit Expression(std::vector<Cell *> & parsedCells, bool reference);

    ~Expression() override;

    CellType getType() const override;

    const std::string ToString() const override;

    Expression *clone() const override;

    void evaluate(std::vector<const Cell *> & inputVector) const override;

    const Expression * getValue() const override;
};


#endif //EDITOR_EXPRESSION_H