//
// Created by julinka on 11.5.18.
//

#pragma once
#ifndef EDITOR_TEXT_H
#define EDITOR_TEXT_H

#endif //EDITOR_TEXT_H

#include "Cell.h"

class Text : public Cell {
private:
    std::string text;

public:
    Text() = default;

    ~Text() override = default;

    explicit Text(const std::string &newText);

public:

    CellType getType() const override;

    const std::string &getValue() const;

    std::string &getValue();

    void setValue(const std::string &newText);

    const std::string ToString() const override;

    Text *clone() const override;
};