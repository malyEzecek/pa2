//
// Created by julinka on 11.5.18.
//

#ifndef EDITOR_NUMBER_H
#define EDITOR_NUMBER_H

#include "Cell.h"

class Number : public Cell {
private:
    double number;

public:
    explicit Number(const double & newNumber);

    CommandType getType() const override;
    const double & getValue() const;
    double & getValue();
    void setValue(const double & newNumber);
    const std::string ToString() const override;
};


#endif //EDITOR_NUMBER_H
