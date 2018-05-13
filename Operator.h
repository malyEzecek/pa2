//
// Created by julinka on 11.5.18.
//

#ifndef EDITOR_OPERATOR_H
#define EDITOR_OPERATOR_H

#include "Cell.h"

enum class OperatorType {
    PLUS = 0,
    MINUS = 1,
    DIVIDE = 3,
    MULTIPLY = 4
};

class Operator : public Cell {
private:
    OperatorType basicOperator;

public:
    Operator(const int & newOperator);
    CommandType getType() const;
    const Cell & getValue() const;
    Cell & getValue();
    void setValue(const int & newOperator);

};


#endif //EDITOR_OPERATOR_H
