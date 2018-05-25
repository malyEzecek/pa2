//
// Created by julinka on 11.5.18.
//

#pragma once
#ifndef EDITOR_REFERENCE_H
#define EDITOR_REFERENCE_H

#endif //EDITOR_REFERENCE_H

#include <vector>
#include "Cell.h"

class Reference : public Cell {
private:
    int XCoor;
    int YCoor;
    std::vector<Cell *> valueOfReference;

public:
    Reference() = default;

    ~Reference() override = default;

    explicit Reference(const int &XPosition, const int &YPosition);

    CellType getType() const override;

    virtual const std::string ToString() const override;

    const int getXCoor() const;

    const int getYCoor() const;

    void setValue(const int &XPosition, const int &YPosition);

    Reference *clone() const override;

    void evaluate(std::vector<const Cell *> & inputVector) const override;

    const Reference * getValue() const override;
};