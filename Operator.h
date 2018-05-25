//
// Created by julinka on 11.5.18.
//

#ifndef EDITOR_OPERATOR_H
#define EDITOR_OPERATOR_H

#include "Cell.h"

enum class OperatorType { // skupiny <1,2>, <3,4>, <5,6>, <7,14>, <15, 17>
    PLUS = 1,
    MINUS = 2,
    MULTIPLY = 3,
    DIVIDE = 4,
    BRACKETOPEN = 5,
    BRACKETCLOSE = 6,
    SINOPEN = 7,
    SQRTOPEN,
    ABSOPEN,
    COSOPEN,
    TANOPEN,
    ROUNDOPEN,
    LOGOPEN,
    LOG2OPEN = 14,
    SINCLOSE = 15,
    SQRTCLOSE,
    ABSCLOSE,
    COSCLOSE,
    TANCLOSE,
    ROUNDCLOSE,
    LOGCLOSE,
    LOG2CLOSE = 22,
    AVG = 23,
    SUM,
    MAX = 25
};

class Operator : public Cell {
private:
    OperatorType basicOperator;

public:
    Operator() = default;

    ~Operator() = default;

    explicit Operator(OperatorType newOperator);

    CellType getType() const;

    const Operator *getValue() const override;

    void setValue(const int &newOperator);

    Operator *clone() const override;

    const std::string ToString() const override;

    void evaluate(std::vector<const Cell *> & inputVector) const override;

    OperatorType returnOperatorType() const;

    bool IsOpeningOperator() const;

};


#endif //EDITOR_OPERATOR_H