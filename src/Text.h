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
    /** text value **/
    std::string text;

public:
    /**
     * Default constructor.
     */
    Text() = default;

    ~Text() override = default;

    /**
     * Explicit constructor
     * @param newText new parameter to be set
     */
    explicit Text(const std::string &newText);

public:

    CellType getType() const override;

    const Text * getValue() const override;

    /**
     * @return reference on member variable text
     */
    std::string &getValue();

    /**
     * Change actual value of string member variable in the cell.
     * @param newText new value to be set
     */
    void setValue(const std::string &newText);

    const std::string ToString(bool load) const override;

    Text *clone() const override;

    void evaluate(std::vector<const Cell *> & inputVector) const override;
};