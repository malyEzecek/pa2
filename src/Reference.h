//
// Created by julinka on 11.5.18.
//

#pragma once
#ifndef EDITOR_REFERENCE_H
#define EDITOR_REFERENCE_H

#endif //EDITOR_REFERENCE_H

#include <vector>
#include <cstdio>
#include <cstdlib>
#include "Cell.h"

class Reference : public Cell {
private:
    /** X coordinate of referenced object **/
    int XCoor;
    /** X coordinate of referenced object **/
    int YCoor;

public:
    /** 'a' in ASCII code **/
    static const int FirstA = 97;

    /**
     * Default constructor
     */
    Reference() = default;

    ~Reference() override = default;

    /**
     * Explicit constructor
     * @param XPosition new X coordinate to be set
     * @param YPosition new Y coordinate to be set
     */

    explicit Reference(const int &XPosition, const int &YPosition);

    CellType getType() const override;

    virtual const std::string ToString(bool load) const override;

    /**
     * @return X coordinate of referenced object.
     */
    int getXCoor() const;

    /**
     * @return Y coordinate of referenced object.
     */
    int getYCoor() const;

    /**
     * Change actual value of reference member variable in the cell.
     * @param XPosition new X value to be set
     * @param YPosition new Y value to be set
     */
    void setValue(const int &XPosition, const int &YPosition);

    Reference *clone() const override;

    void evaluate(std::vector<const Cell *> & inputVector) const override;

    const Reference * getValue() const override;
};