//
// Created by julinka on 19.5.18.
//
#pragma once
#ifndef EDITOR_COMMAND_H
#define EDITOR_COMMAND_H

#include <vector>
#include <cstdlib>
#include <stack>
#include <iostream>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <cstdlib>
#include <fstream>
#include "Model.h"

enum class CommandType {
    CLEAR,
    SET,
    EXIT,
    SAVE,
    LOAD,
    RESIZE,
    GETVALUE
};

/**
 * Invalid input exception.
 * Description of exception: wrong type of command, invalid parameters, invalid types of value in expression.
 */
class InvalidInput {
private:
    std::string warningOfInvalidInput;
public:

    explicit InvalidInput(const std::string &warning);
    /**
     * @return warning;
     */
    const std::string &getStr() const ;
};

/**
 * Invalid reference/expression exception.
 * Description of exception: null reference, cyclic dependency, invalid type of reference in expression.
 */
class InvalidExpressionOrReference {
private:
    std::string warningOfInvalidExpressionReference;

public:
    explicit InvalidExpressionOrReference(const std::string &warning);
    /**
     * @return warning;
     */
    const std::string &getStr() const;
};


class Command {
private:
    /** type of Command **/
    CommandType typeOfCommand;

    static const int maxCharInCommand = 9;
    /**
     * Parse input string to known command or throw exception, if inputted command doesn't exist.
     * @param inputString inputted by user string
     * @param delimiters different types of delimiters
     * @return determine type of inputted command
     */
    CommandType parseToCommand(std::string &inputString, bool *delimiters) const;

    /**
     * Check correctness of inputted coordinates.
     * @param xCoor number of column
     * @param yCoor number of row
     * @param inputString
     * @param xCoorString number of column to_String()
     * @param yCoorString number of row to_String()
     * @param delimiters different types of delimiters
     * @param firstParameter detects if basic algebraic operations like ( '+', '-', '*', '/') were used
     */

    void checkParsedStrCoordinates(int &xCoor, int &yCoor, std::string &inputString, std::string &xCoorString,
                                   std::string &yCoorString, bool *delimiters, bool firstParameter) const;
    /**
     * Parse input string to coordinates.
     * @param xCoor number of column
     * @param yCoor number of row
     * @param inputString
     * @param delimiters different types of delimiters
     * @param firstParameter detects if basic algebraic operations like ( '+', '-', '*', '/')  were used
     */
    void parseStringToCoordinates(int &xCoor, int &yCoor, std::string &inputString, bool *delimiters,
                                  bool firstParameter = true) const;
    /**
     * Decides what type of cell is used and that parsed string.
     * @param inputString
     * @param delimiters different types of delimiters
     * @return new Cell to table
     */
    Cell *parseStringToCell(std::string inputString, bool *delimiters) const;

    /**
     * Decides what type of command was inputted.
     * @param parsedCommand string with name of the command
     * @return type of the command
     */
    CommandType SwitchTypeOfCommand(const std::string &parsedCommand) const;

    /**
     * Cut temporaryForCutting string to get coordinates for GetValue() command.
     * @param temporaryForCutting input string
     * @param delimiters different types of delimiters
     */
    void getValueCommand(std::string &temporaryForCutting, bool *delimiters);

    /**
     * Execute EXIT command with possibility to save table.
     * @param temporaryForCutting input string
     * @param delimiters different types of delimiters
     * @param exit detects if user want to exit program and send the information to the view
     */
    void exitCommand(std::string &temporaryForCutting, bool *delimiters, bool &exit);

    /**
     * Cut temporaryForCutting string to get path and save actual table.
     * @param temporaryForCutting input string
     * @param exit detects if user want to exit program and send the information to the view
     */
    void saveCommand(std::string &temporaryForCutting, bool &exit);

    /**
     * Cut temporaryForCutting string to get path for loading and load table from the path.
     * @param temporaryForCutting input string
     * @param exit detects if user want to exit program and send the information to the view
     */

    void loadCommand(std::string &temporaryForCutting, bool &exit);

    /**
     * Decides which command program should execute.
     * @param temporaryForCutting input string
     * @param delimiters different types of delimiters
     * @param exit detects if user want to exit program and send the information to the view
     */
    void ExecuteCommand(std::string &temporaryForCutting, bool *delimiters, bool &exit);

    /**
     * Delete all spaces from the string beginning.
     * @param inputString
     */
    void deleteThisUglySpaces(std::string &inputString) const;

    /**
     * Parse string to Number type.
     * @param inputString
     * @param number save number result.
     */
    void parseStringToNumber(std::string &inputString, std::string &number) const;

    /**
     * Parse string to Text type.
     * @param inputString
     * @return parsed string.
     */
    std::string parseStringToText(std::string &inputString) const;

    /**
     * parse string to Bool type.
     * @param inputString
     */
    void parseStringToBool(std::string &inputString) const;

    /**
     * Control correctness of the expression
     * @param possibleCells vector of Cell * to save all parts of expression.
     * @param inputString
     * @param operatorFirstType detects if basic algebraic operation like ( '+', '-', '*', '/') was used before
     * @param operatorSecondType detects if algebraic or trigonometric operation like ( 'sin(', 'cos(', 'avg(') was used before
     * @param brackets amount of not-closed brackets that were used in expression
     * @param mathOperator type of mathematical(algebraic or trigonometric) operator that what used and not closed yet
     */
    void parseExpressionFinalControl(std::vector<Cell *> &possibleCells, std::string &inputString, bool &operatorFirstType,
                                     bool &operatorSecondType, int &brackets, OperatorType *&mathOperator) const;

    /**
     * "Helper method" for method Command::parseExpression(). Parse one part of expression to mathematical function (Operator).
     * @param possibleCells vector of Cell * to save all parts of expression.
     * @param inputString
     * @param operatorFirstType detects if basic algebraic operation like ( '+', '-', '*', '/') was used before
     * @param operatorSecondType detects if algebraic or trigonometric operation like ( 'sin(', 'cos(', 'avg(') was used before
     * @param mathOperator type of mathematical(algebraic or trigonometric) operator that what used and not closed yet
     * @param amountOfBracketsForMathFunc amount of "opened" brackets when math func started
     * @param brackets amount of not-closed brackets that were used in expression
     */
    void parseExpressionMathematicalPart(std::vector<Cell *> &possibleCells, std::string &inputString,
                                         bool &operatorFirstType, bool &operatorSecondType,
                                         OperatorType *&mathOperator, int &amountOfBracketsForMathFunc,
                                         int &brackets) const;
    /**
     * "Helper method" for method Command::parseExpression(). Parse one part of expression to open or closed bracket (Operator).
     * @param possibleCells vector of Cell * to save all parts of expression.
     * @param inputString
     * @param operatorSecondType detects if algebraic or trigonometric operation like ( 'sin(', 'cos(', 'avg(') was used before
     * @param brackets amount of not-closed brackets that were used in expression
     * @param amountOfBracketsForMathFunc amount of "opened" brackets when math func started
     * @param mathOperator type of mathematical(algebraic or trigonometric) operator that what used and not closed yet
     */
    void parseExpressionBracketsPart(std::vector<Cell *> &possibleCells, std::string &inputString, bool &operatorSecondType,
                                     int &brackets, int &amountOfBracketsForMathFunc,
                                     OperatorType *&mathOperator) const;
    /**
     * "Helper method" for method Command::parseExpression(). Parse one part of expression to Operator.
     * @param possibleCells vector of Cell * to save all parts of expression.
     * @param inputString
     * @param operatorFirstType detects if basic algebraic operation like ( '+', '-', '*', '/') was used before
     */
    void parseExpressionBasicOperatorPart(std::vector<Cell *> &possibleCells, std::string &inputString,
                                          bool &operatorFirstType) const;
    /**
     * "Helper method" for method Command::parseExpression(). Parse one part of expression to Number.
     * @param possibleCells vector of Cell * to save all parts of expression.
     * @param inputString
     * @param operatorFirstType detects if basic algebraic operation like ( '+', '-', '*', '/') was used before
     */
    void parseExpressionNumberPart(std::vector<Cell *> &possibleCells, std::string &inputString,
                                   bool &operatorFirstType) const;
    /**
     * Parse expression on different cells.
     * @param possibleCells vector of Cell * to save all parts of expression.
     * @param inputString
     * @param delimiters different types of delimiters
     * @param reference bool, that ckecks if reference was used in the expression
     */
    void parseExpression(std::vector<Cell *> &possibleCells, std::string &inputString, bool *delimiters,
                         bool &reference) const;
    /**
     * Parse string to X & Y coordinates.
     * @param inputString
     * @param xCoorString X coordinate to_String()
     * @param yCoorString Y coordinate to_String()
     * @param delim actual valid delimeters
     * @param breakMoment boolean - tells when we should stop parsing
     * @param position of delimiter
     * @param delimiters different types of delimiters
     */
    void parseToXYString(std::string &inputString, std::string &xCoorString, std::string &yCoorString,
                         std::vector<char> &delim, bool first, bool breakMoment, int &position, bool *delimiters) const;

    /**
     * Parse input string to math functions.
     * @param inputString
     * @return type of mathematical operator
     * @example pointer on OperatorType::SINOPEN
     */

    OperatorType *parseStringToMathFunction(std::string &inputString) const;

    /**
    * Parse input string to aggregation functions.
    * @param inputString
    * @return type of aggregation operator
    * @example pointer on OperatorType::AVGOPEN
    */

    OperatorType *parseStringToAggregationFunction(std::string &inputString) const;

    /**
     * Parsed input string to 2 parameters(coordinates) for aggregation function.
     * @param inputString
     * @param possibleCells vector of Cell * to save all parts of expression.
     * @param aggregationFunction create new aggregation Operator
     * @param delimiters different types of delimiters
     */

    void parseAggregationFuncValue(std::string &inputString, std::vector<Cell *> &possibleCells,
                                   const OperatorType *aggregationFunction, bool *delimiters) const;
    /**
     * Evaluation of reference that can detect cyclic dependence or reference on invalid type of cells.
     * Recursion function.
     * @param actualCell out reference
     * @param detectorOfCyclus vector of pointers on Cell that were used in our exprassion for evaluation
     * @param expressionWithoutReferences vector of pointers on Cells without any references (only Number type).
     */
    void referenceEvaluation(const Cell *actualCell, std::vector<const Cell *> &detectorOfCyclus,
                             std::vector<const Cell *> &expressionWithoutReferences) const;

    /**
     * Transform expression from infix notation to postfix with stack usage.
     * Important part of expression evaluation.
     * @param expressionWithoutReferences vector of pointers on Cells without any references (only Number type).
     * @param insideOfExpression evaluation of reference, if it refers on expression
     */
    void InfixToPostfix(std::vector<const Cell *> &expressionWithoutReferences,
                        std::vector<const Cell *> &insideOfExpression) const;
    /**
     * Get parameters for table resizing from input string.
     * @param temporaryForCutting
     * @param yCoor new height of the table (reference)
     * @param xCoor new width of the table (reference)
     */

    void getResizeParameters(std::string &temporaryForCutting, int &yCoor, int &xCoor) const;

    /**
     * "Helper method" for resize Table.
     * @param temporaryForCutting input string
     * @param cord new output coordinate
     */
    void getCoord(std::string &temporaryForCutting, std::string &cord) const;
    /**
     * Parse input string to loading/saving path.
     * @param temporaryForCutting input string
     * @param loadingPath output string
     * @param exit detects if user want to exit program and send the information to the view
     */
    void getLoadSaveParameter(std::string &temporaryForCutting, std::string &loadingPath, bool &exit) const;
    /**
     * Just write output to file.
     * @param myFileSave path to load/save
     */
    void writeToFile(std::ofstream &myFileSave) const;
    /**
     * Check valid od exit command.
     * @param temporaryForCutting
     */
    void exitOrHelpCorrectCommand(std::string &temporaryForCutting) const;
    /**
     * Ask user, if he/she wants to save table before exit.
     * @param decision input-output parameter
     * @return user's answer.
     */
    bool SaveTableBeforeExit(const std::string &decision) const;
    /**
     * Get inverse (close -> open, open -> close) operator to mathOperator.
     * @param mathOperator
     * @param reversedOperator
     */
    void getInverseOperator(OperatorType *&mathOperator, OperatorType &reversedOperator) const;
    /**
     * "Helper method" for Controll::evaluatePostfixExpression method.
     * Evaluation of postfix expression with basic algebraic operators.
     * @param cellPointer actual cell to process
     * @param ss stack with Number objects.
     */
    void evaluatePostfixExpressionBasicOpearators(const Cell * cellPointer, std::stack<const Number *> &ss) const;
    /**
     * Evaluate vector of postfixExpression with stack usage.
     * @param postfixExpression vector of Cell pointers.
     * @return pointer on Number like a result of evaluation.
     */
    const Number *evaluatePostfixExpression(std::vector<const Cell *> &postfixExpression) const;
    /**
     * Control correctness and throw exceptions.
     * @param ss stack with pointers on Numbers.
     */
    void postfixExpressionError(std::stack<const Number *> ss) const;

    /**
     * Control correctness and throw exceptions.
     * @param possibleCells vector of Cell * to save all parts of expression.
     */
    void parseExpressionError(std::vector<Cell *> &possibleCells) const;

public:

    static const std::string SMALLTABLESIZE;

    static const std::string OPENFILEERROR;

    static const std::string COMMANDDOESNTEXISTS;

    static const std::string INVALIDPARAMETER;

    static const std::string INVALIDEXPRESSION;

    static const std::string NULLREFERENCE;

    static const std::string INVALIDREFERNCEINSIDEEXPRESSION;

    static const std::string CYCLICDEPENDENCY;
    /**
     * Default constructor.
     */
    Command();
    /**
     * Set new Command.
     * @param inputString
     * @param exit exit detects if user want to exit program and send the information to the view
     */
    void SetCommand(const std::string &inputString, bool &exit);
    /**
     * @return type of the Command.
     */
    CommandType returnCommandType() const;
    /**
     * Expression evaluation.
     * @param expression input pointer on Cell
     * @param checkReferences vector of const pointers on Cells to control cyclic dependency
     * @return new evaluated Number
     */

    const Number *evaluateExpression(const Cell *expression, std::vector<const Cell *> &checkReferences) const;
    /**
     * Evaluate reference.
     * @param height Y coordinate
     * @param width  X coordinate
     * @param checkCycles checkReferences vector of const pointers on Cells to control cyclic dependency
     */
    void evaluateReference(const unsigned &height, const unsigned &width, std::vector<const Cell *> &checkCycles) const;

};


#endif //EDITOR_COMMAND_H