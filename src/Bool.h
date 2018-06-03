//
// Created by julinka on 10.5.18.
//
#pragma once
#ifndef EDITOR_BOOL_H
#define EDITOR_BOOL_H

#endif //EDITOR_BOOL_H

#include "Cell.h"


class Bool : public Cell {
private:
    bool value;

public:
    Bool() = default;

    ~Bool() override = default;

    explicit Bool(const bool newValue);

    CellType getType() const override;

    void setValue(const bool &value);

    const std::string ToString(bool load) const override;

    Bool *clone() const override;

    void evaluate(std::vector<const Cell *> & inputVector) const override;

    const Bool * getValue() const override;
};