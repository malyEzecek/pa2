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
    /** value of cell that contains boolean **/
    bool value;

public:
    /**
     * Default constructor.
     */
    Bool() = default;

    /**
     * Default overridden destructor.
     */

    ~Bool() override = default;
    /**
     * Explicit constructor. Set parameters operation.
     * @param newValue new value for private param value.
     */

    explicit Bool(const bool newValue);
    /**
     * Overridden Cell method.
     * @return CellType of the cell. (BOOLEAN)
     */
    CellType getType() const override;

    /**
     * Change actual value of boolean parameter in the cell.
     * @param value new boolean value
     */

    void setValue(const bool &value);

    /**
     * Overridden Cell method.
     * @param load Depends on this parameter program find out,
     * if it should align string to mode parameter.
     * @return new align string
     */

    const std::string ToString(bool load) const override;

    /**
     * Overridden Cell method (Copy constructor).
     * @return pointer on the new Bool object.
     */
    Bool *clone() const override;

    /**
     * Overridden Cell method.
     * @param inputVector copies pointers to Cell objects from the actual Cell.
     */

    void evaluate(std::vector<const Cell *> & inputVector) const override;

    /**
     * Overridden Cell method.
     * @return access to its own address.
     */
    const Bool * getValue() const override;
};