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

    ~Bool() = default;

    explicit Bool(const bool newValue);

    CellType getType() const override;

    bool getValue() const;

    bool getValue();

    void setValue(const bool &value);

    const std::string ToString() const override;

    Bool *clone() const override;
};