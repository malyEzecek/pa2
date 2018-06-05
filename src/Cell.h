//
// Created by julinka on 9.5.18.
//

#pragma once
#ifndef EDITOR_CELL_H
#define EDITOR_CELL_H

#endif //EDITOR_CELL_H

#include <string>
#include <vector>

enum class CellType {
    BOOLEAN,
    TEXT,
    REFERENCE,
    EXPRESSION,
    NUMBER,
    OPERATION
};

/**
 * Abstract class.
 */
class Cell {
private:
    /**
     * Width of the cell.
     */
    int sizeOfCell;

protected:
    /** Default width of all cells in the table.**/
    static const int defaultWidthOfCell = 11;
    /** Actual width of the cell.**/
    int mode;

    /**
     * Change input value align to mode parameter.
     * @param editString input string to be changes
     * @return new edited string
     */
    std::string editToWideOfCell(const std::string &editString) const;

public:
    /**
     * default constructor
     */
    Cell();
    /**
     *Virtual destructor for superclass Cell.
     */
    virtual ~Cell() = default;

    /**
     * @return actual Cell size.
     */
    int getCellSize() const;

    /**
     * Virtual abstract method.
     * @return CellType type of the inherited class.
     */
    virtual CellType getType() const = 0;
    /**
     * Virtual method that returns subclass value and transform it to string.
     * @param load depends on this parameter program find out,
     * if it should align string to mode parameter.
     * @return subclasses value to_string
     */

    virtual const std::string ToString(bool load) const = 0;

    /**
     * Copy constructor for subclasses.
     * @return pointer on the new subclass object.
     */

    virtual Cell *clone() const = 0;

    /**
     * @param inputVector copies pointers to Cell objects from the actual Cell.
     */

    virtual void evaluate(std::vector<const Cell *> & inputVector) const = 0;

    /**
     * @return  access to its own address.
     */
    virtual const Cell * getValue() const = 0;
};