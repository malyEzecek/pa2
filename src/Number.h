//
// Created by julinka on 11.5.18.
//

#pragma once
#ifndef EDITOR_NUMBER_H
#define EDITOR_NUMBER_H

#include <math.h>
#include "Cell.h"

class Number : public Cell {
private:
    double number;
    bool postfix;

    std::string cutStringWithDouble(const std::string &editString) const;

public:
    explicit Number(const double &newNumber, bool postfix = false);

    Number() = default;

    ~Number() override = default;

    CellType getType() const override;

    const Number *getValue() const override;

    double &getValue();

    void setValue(const double &newNumber);

    const std::string ToString(bool load) const override;

    Number *clone() const override;

    void evaluate(std::vector<const Cell *> &inputVector) const override;

    double getNumber() const;

    bool addedInPostfixFunction() const;

};


#endif //EDITOR_NUMBER_H