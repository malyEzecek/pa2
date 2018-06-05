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
    /** actual value of cell */
    double number;
    /** control if Number wasn't appear in Model::evaluatePostfixExpression() method. **/
    bool postfix;
    /**
     * Cutting input string to show them in the table without great amount of zeroes.
     * @param editString to be cut
     * @return new edited string
     */
    std::string cutStringWithDouble(const std::string &editString) const;

public:
    /**
     * Explicit constructor
     * @param newNumber new value to be set
     * @param postfix shows if Number was created in Model::evaluatePostfixExpression() method
     */
    explicit Number(const double &newNumber, bool postfix = false);

    /**
     * Default constructor
     */
    Number() = default;

    /**
     * Default overridden destructor.
     */

    ~Number() override = default;

    /**
     * Overridden Cell method.
     * @return CellType of the cell. (NUMBER)
     */
    CellType getType() const override;

    /**
     * Overridden Cell method.
     * @return access to its own address.
     */

    const Number *getValue() const override;

    /**
     * @return reference of member variable number.
     */
    double &getValue();

    /**
     * Change actual value of double member variable in the cell.
     * @param newNumber new value
     */
    void setValue(const double &newNumber);

    /**
     * Overridden Cell method.
     * @param load Depends on this parameter program find out,
     * if it should align string to mode parameter.
     * @return new align string
     */

    const std::string ToString(bool load) const override;

    /**
     * Overridden Cell method (Copy constructor).
     * @return pointer on the new Number object.
     */
    Number *clone() const override;

    /**
     * Overridden Cell method.
     * @param inputVector copies pointers to Cell objects from the actual Cell.
     */

    void evaluate(std::vector<const Cell *> &inputVector) const override;

    /**
     *
     * @return copy of member variable number.
     */
    double getNumber() const;

    /**
     * @return information, if it was created in Model::evaluatePostfixExpression() method.
     */
    bool addedInPostfixFunction() const;

};


#endif //EDITOR_NUMBER_H