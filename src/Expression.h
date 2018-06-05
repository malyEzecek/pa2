//
// Created by julinka on 12.5.18.
//

#pragma once
#ifndef EDITOR_EXPRESSION_H
#define EDITOR_EXPRESSION_H

#include <vector>
#include "Cell.h"
#include "Number.h"
#include "Reference.h"
#include "Operator.h"

class Expression : public Cell {
private:
    /** array of pointers on Cells
     * every of the is the part of the expression**/
    std::vector<Cell *> parsedStringToCells;

public:
    /**
     * Default constructor.
     */
    Expression() = default;

    /**
     * Explicit constructor
     * @param parsedCells array of pointers on Cell like a parts of the expression to be set
     */

    explicit Expression(std::vector<Cell *> & parsedCells);

    ~Expression() override;

    CellType getType() const override;

    const std::string ToString(bool load) const override;

    Expression *clone() const override;

    void evaluate(std::vector<const Cell *> & inputVector) const override;

    const Expression * getValue() const override;
};


#endif //EDITOR_EXPRESSION_H