//
// Created by julinka on 11.5.18.
//

#ifndef EDITOR_OPERATOR_H
#define EDITOR_OPERATOR_H

#include <math.h>
#include "Cell.h"

enum class OperatorType { // skupiny <1,2>, <3,4>, <5,6>, <7,14>, <15, 17>
    PLUS = 1, // first type
    MINUS = 2, // first type
    MULTIPLY = 3, // second type
    DIVIDE = 4, // second type
    BRACKETOPEN = 5, // third type begin
    BRACKETCLOSE = 6,
    SINOPEN = 7,
    SQRTOPEN,
    ABSOPEN,
    COSOPEN,
    TANOPEN,
    ROUNDOPEN,
    LOGOPEN,
    LOG2OPEN = 14, // third type end
    SINCLOSE = 15, // forth type begin
    SQRTCLOSE,
    ABSCLOSE,
    COSCLOSE,
    TANCLOSE,
    ROUNDCLOSE,
    LOGCLOSE,
    LOG2CLOSE = 22, // forth type end
    AVGOPEN = 23, // third type
    SUMOPEN,
    MAXOPEN = 25, // third type
    AVGCLOSE = 26, // forth type
    SUMCLOSE,
    MAXCLOSE = 28 // forth type
};
/**
 * Methematical exception.
 * Description : divide by zero.
 */

class InvalidMathematicalExpression {
private:
    std::string warning;
public:
    explicit InvalidMathematicalExpression(const std::string &mathematicalWarning);

    const std::string &getStr() const;
};


class Operator : public Cell {
private:
    /** Determine the type of Operator**/
    OperatorType basicOperator;
    /**
     * Helper function for expression evaluation.
     * On the weight of the Operator depends processing of pushing and poping operators to/from std::stack<Operator *>.
     * @param value type of Operator
     * @return int - range from 1 to 4
     */
    int getWeightOfOperator(const OperatorType &value) const;

public:

    /** well known pi-const**/
    const double PI = 3.14159265;

    /** well known pidegree **/
    const double PIDEGREE = 180;
    /**
     * Default constructor.
     */
    Operator() = default;

    ~Operator() override = default;

    /**
    * Explicit constructor
    * @param newOperator new parameter to be set
    */
    explicit Operator(OperatorType newOperator);

    CellType getType() const override;

    const Operator *getValue() const override;

    /**
     * Change actual value of OperatorType member variable in the cell.
     * @param newOperator new value
     */
    void setValue(const int &newOperator);

    Operator *clone() const override;

    const std::string ToString(bool load) const override;

    void evaluate(std::vector<const Cell *> &inputVector) const override;

    /**
     * @return OperatorType of actual Operator objeect.
     */
    OperatorType returnOperatorType() const;

    /**
     * Detect if input operator is "close operator".
     * @param operators input Operator type parameter
     * @return true of false
     * @example ')' is closed operator
     */

    static bool IsClosedOperator(const OperatorType &operators);
    /**
     * Detect if input operator is open operator.
     * @param operators input Operator type parameter
     * @return true of false
     * @example '(' or 'sin(' is "open operator"
     */

    static bool IsOpenedOperator(const OperatorType &operators);

    /**
     * Compare weight of actual object with input.
     * @param topOfStack param to be compared with
     * @return true if topOfStack has higher precedence, otherwise false
     */

    bool HasHigherPrecedence(const OperatorType &topOfStack) const;

    /**
     * Find open operator for actual operator.
     * @return OperatorType open operator
     */
    OperatorType returnOpenedBracket() const;

    int getWeighOfOperator() const;

    /**
     * Use binary operator and evaluate two input numbers.
     * @param first first param to be evaluated
     * @param second second param to be evaluated
     * @return double result of evaluation.
     */

    double evaluateNumbers(const double &first, const double &second) const;

    /**
    * Use unary operator and evaluate two input numbers.
    * @param first first param to be evaluated
    * @return double result of evaluation.
    */

    double evaluateNumbers(const double &first) const;
};


#endif //EDITOR_OPERATOR_H