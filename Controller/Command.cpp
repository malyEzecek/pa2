//
// Created by julinka on 19.5.18.
//

#include <cstdlib>
#include <fstream>
#include "Command.h"

Command::Command() {}

CommandType Command::returnCommandType() const {
    return typeOfCommand;
}

// Insert(A14, A5 + B7 + 14 + 15);

void Command::ExecuteCommand(std::string &temporaryForCutting, bool *delimiters, bool &exit) {
    switch (typeOfCommand) {
        case CommandType::SET : {
            int xCoor, yCoor;
            parseStringToCoordinates(xCoor, yCoor, temporaryForCutting, delimiters);
            if(xCoor >= Model::getInstance()->getWidth() || yCoor > Model::getInstance()->getHeight() ){
                std::cout << "Size of the table is too small. Try to use resize()." << std::endl;
                return;
            }

            Cell *newCell = parseStringToCell(temporaryForCutting, delimiters);
            Model::getInstance()->setValue(yCoor - 1, xCoor, newCell); // pocitame od 0
            delete newCell;
            break;
        }
        case CommandType::EXIT : {
            exitOrHelpCorrectCommand(temporaryForCutting);
            std::cout << "Do you want to save table?" << std::endl;
            std::string input, decision;
            getline(std::cin, input);
            std::stringstream ss(input);
            ss >> decision;
            if (SaveTableBeforeExit(decision)) {
                std::cout << "Please, write path and name of the document to save." << std::endl;
                std::string inputString;
                getline(std::cin, inputString);
                typeOfCommand = CommandType::SAVE;
                ExecuteCommand(inputString, delimiters, exit);
            }
            return;
        }
        case CommandType::CLEAR : {
            int xCoor, yCoor;
            parseStringToCoordinates(xCoor, yCoor, temporaryForCutting, delimiters);
            Model::getInstance()->deleteValue(yCoor - 1, xCoor);
            break;
        }
        case CommandType::RESIZE : {
            int xCoor, yCoor;
            getResizeParameters(temporaryForCutting, yCoor, xCoor);
            Model::getInstance()->resizeTable(yCoor, xCoor);
            break;
        }
        case CommandType::LOAD : {
            std::string loadingPath;
            getLoadSaveParameter(temporaryForCutting, loadingPath, exit);
            std::ifstream myFileLoad(loadingPath);
            std::string line;
            if (myFileLoad.is_open()) {
                while (getline(myFileLoad, line).good()) {
                    SetCommand(line, exit);
                }
                myFileLoad.close();
            } else {
                std::cout << "Unable to open file." << std::endl;
            }

            break;
        }
        case CommandType::SAVE : {
            deleteThisUglySpaces(temporaryForCutting);
            std::string savingPath;
            getLoadSaveParameter(temporaryForCutting, savingPath, exit);
            std::ofstream myFileSave(savingPath);
            if (myFileSave.is_open()) {
                writeToFile(myFileSave);
                myFileSave.close();
            } else
                std::cout << "Unable to open file." << std::endl;
        }
    }
}

void Command::SetCommand(const std::string &inputString, bool &exit) {
    std::string temporaryForCutting = inputString;
    bool delimiters[] = {false, false, false, false, false, false, false,
                         false, false, false}; // { ' ', '(', '\n', ')', '+', '-', '*', '\', '$', ',' }
    Command::typeOfCommand = parseToCommand(temporaryForCutting, delimiters);

    if (typeOfCommand == CommandType::EXIT) {
        exit = true;
    } else {
        if (!delimiters[1]) {
            throw "This command doesn't exist. Try 'help' for more information.\n";
        }
    }
    ExecuteCommand(temporaryForCutting, delimiters, exit);

}

CommandType Command::SwitchTypeOfCommand(const std::string &parsedCommand) const {
    if (parsedCommand == "clear") {
        return CommandType::CLEAR;
    } else if (parsedCommand == "set") {
        return CommandType::SET;
    } else if (parsedCommand == "exit") {
        return CommandType::EXIT;
    } else if (parsedCommand == "save") {
        return CommandType::SAVE;
    } else if (parsedCommand == "load") {
        return CommandType::LOAD;
    } else if (parsedCommand == "resize") {
        return CommandType::RESIZE;
    } else
        throw "This command doesn't exist. Try 'help' for more information.\n";
}

CommandType Command::parseToCommand(std::string &inputString, bool *delimiters) const {
    std::string parsedCommand;
    deleteThisUglySpaces(inputString);
    if (inputString[0] != 'c' && inputString[0] != 'e' && inputString[0] != 's'
        && inputString[0] != 'l' && inputString[0] != 'r' && inputString[0] != 'h')
        throw "This command doesn't exist. Try 'help' for more information.\n";
    std::vector<char> delim = {' ', '(', '\n'};

    int CharInCommand = 0;
    bool finded = false;
    for (char character : inputString) {
        if (CharInCommand == maxCharInCommand) { // prekroceni maximalniho poctu charu v libovolnem existujicim prikazu
            break;
        }

        for (unsigned i = 0; i < delim.size(); ++i) {
            if (character == delim[i]) {
                delimiters[i] = true;
                finded = true;
                break;
            }
        }
        if (finded)
            break;
        parsedCommand += character;
        ++CharInCommand;
    }
    inputString.erase(0, parsedCommand.size() + 1);
    return SwitchTypeOfCommand(parsedCommand);
}

void Command::parseToXYString(std::string &inputString, std::string &xCoorString, std::string &yCoorString,
                              std::vector<char> &delim, bool first, bool breakMoment, int &position,
                              bool *delimiters) const {

    for (unsigned amount = 0; position < (int)inputString.size() - 1; ++position, ++amount) {
        if (inputString[position] == '$') {
            first = false;
            continue;
        }
        for (char delimiter : delim) {
            if (inputString[position] == delimiter) {
                breakMoment = true;
                if (delimiter == ',')
                    delimiters[9] = true;
                else if (delimiter == ')')
                    delimiters[3] = true;
                break;
            }
        }
        if (breakMoment)
            break;

        if (first) {
            if (inputString[position] < 97 || inputString[position] > 122)
                throw "Invalid parameter. Try 'help' for more information.\n";
            xCoorString += std::to_string((int) inputString[position] - FirstA);
        } else {
            if (inputString[position] < 48 || inputString[position] > 57)
                throw "Invalid parameter. Try 'help' for more information.\n";
            yCoorString += inputString[position];
        }

        if (amount >= 7)
            throw "Invalid parameter. Try 'help' for more information.\n";
    }
}

void Command::parseStringToCoordinates(int &xCoor, int &yCoor, std::string &inputString, bool *delimiters) const {

    deleteThisUglySpaces(inputString);
    if (inputString[0] != '$')
        throw "Invalid parameter. Try 'help' for more information.\n";
    inputString.erase(0, 1);

    int position = 0;
    std::vector<char> delim = {',', ')', ' ', ':'};
    std::string xCoorString, yCoorString;
    bool first = true;
    bool breakMoment = false;

    parseToXYString(inputString, xCoorString, yCoorString, delim, first, breakMoment, position, delimiters);

    inputString.erase(0, position);
    deleteThisUglySpaces(inputString);

    if (!delimiters[9] && !delimiters[3]) {
        if (inputString[0] == ',')
            delimiters[9] = true;
        else if (inputString[0] == ')')
            delimiters[3] = true;
        else if (inputString[0] == ':') {}

        else
            throw "Invalid parameter. Try 'help' for more information.\n";
    }

    if (xCoorString.size() > 2 || yCoorString.size() > 4)
        throw "Invalid parameter. Try 'help' for more information.\n";
    xCoor = std::stoi(xCoorString);
    yCoor = std::stoi(yCoorString);
    inputString.erase(0, 1);
}

Cell *Command::parseStringToCell(std::string inputString, bool *delimiters) const {
    std::vector<Cell *> possibleCells;
    deleteThisUglySpaces(inputString);
    if (inputString[0] == '"') {
        inputString.erase(0, 1);
        std::string value = parseStringToText(inputString);
        return new Text(value);
    } else {

        if (inputString.substr(0, 4) == "true") {
            parseStringToBool(inputString.erase(0, 4));
            return new Bool(true);
        } else if (inputString.substr(0, 5) == "false") {
            parseStringToBool(inputString.erase(0, 5));
            return new Bool(false);
        } else {
            bool reference = false;
            parseExpression(possibleCells, inputString, delimiters, reference);
            if (possibleCells.size() > 1) {
                return new Expression(possibleCells, reference);
            } else if (possibleCells.size() == 1) {
                return possibleCells[0];
            } else
                throw "Invalid parameter. Try 'help' for more information.\n";
        }
    }
}

void Command::deleteThisUglySpaces(std::string &inputString) const {
    unsigned position = 0;
    for (; position < inputString.size(); ++position) {
        if (inputString[position] == ' ')
            continue;
        else {
            break;
        }
    }

    inputString.erase(0, (unsigned long) position);
}

std::string Command::parseStringToText(std::string &inputString) const {
    std::string returnText;
    int position = 0;
    for (char inputChar : inputString) {
        if (inputChar == '"') {
            break;
        }
        if (inputChar == ')') {
            throw "Invalid parameter. Try 'help' for more information.\n";
        }
        returnText += inputChar;
        ++position;
    }

    inputString.erase(0, (unsigned long) position + 1);
    deleteThisUglySpaces(inputString);

    if (inputString[0] != ')')
        throw "Invalid parameter. Try 'help' for more information.\n";
    inputString.erase(0, 1);
    deleteThisUglySpaces(inputString);

    return returnText;
}

void Command::parseStringToBool(std::string &inputString) const {
    deleteThisUglySpaces(inputString);
    if (inputString[0] != ')')
        throw "Invalid parameter. Try 'help' for more information.\n";
    inputString.erase(0, 1);
    deleteThisUglySpaces(inputString);
}

void Command::parseExpression(std::vector<Cell *> &possibleCells, std::string &inputString, bool *delimiters,
                              bool &reference) const {
    bool operatorFirstType = false, operatorSecondType = false; // firstType - tradicni operatory +, -, *, /, secondType - sin, cos atd...
    int brackets = 1, amountOfBracketsForMathFunc = 0; // zapamatuje si cislo zavorek pred tim
    OperatorType *mathOperator = nullptr, *aggregationFunction = nullptr;
    std::string mathFunction;
    auto mainSize = (int) inputString.size();
    for (int t = 0; t < mainSize; ++t) {
        deleteThisUglySpaces(inputString);
        if (inputString[0] == '$') {
            int xCoor, yCoor;
            parseStringToCoordinates(xCoor, yCoor, inputString, delimiters);
            possibleCells.push_back(new Reference(xCoor, yCoor));
            reference = true;
            if (possibleCells.back()->getType() != CellType::NUMBER ||
                possibleCells.back()->getType() != CellType::EXPRESSION ||
                possibleCells.back()->getType() != CellType::REFERENCE)
                throw "Invalid expression. Try 'help' for more information.\n";
            if (operatorFirstType)   // jestli operator +, -, *, / -pak za nim jde cislo nebo referencee, tak by zadne problemy vyskytnout nemely
                operatorFirstType = false;

        } else if (inputString[0] >= 48 && inputString[0] <= 57) {
            std::string number;
            parseStringToNumber(inputString, number);
            double cellNumber = std::stod(number);
            possibleCells.push_back(new Number(cellNumber));
            if (operatorFirstType)
                operatorFirstType = false;

        } else if (inputString[0] >= 42 && inputString[0] <= 47) {
            if (operatorFirstType)
                throw "Invalid expression. Try 'help' for more information.\n";
            switch (inputString[0]) {
                case '+': {
                    if (possibleCells.empty())
                        throw "Invalid expression. Try 'help' for more information.\n";
                    possibleCells.push_back(new Operator(OperatorType::PLUS));
                    break;
                }
                case '-': {
                    possibleCells.push_back(new Operator(OperatorType::MINUS));
                    break;
                }
                case '/': {
                    if (possibleCells.empty())
                        throw "Invalid expression. Try 'help' for more information.\n";
                    possibleCells.push_back(new Operator(OperatorType::DIVIDE));
                    break;
                }
                case '*': {
                    if (possibleCells.empty())
                        throw "Invalid expression. Try 'help' for more information.\n";
                    possibleCells.push_back(new Operator(OperatorType::MULTIPLY));
                    break;
                }
                default:
                    throw "Invalid parameter. Try 'help' for more information.\n";
            }
            operatorFirstType = true;
            inputString.erase(0, 1);

        } else if (inputString[0] == '(' || inputString[0] == ')') {

            if (inputString[0] == '(') {
                possibleCells.push_back(new Operator(OperatorType::BRACKETOPEN));
                ++brackets;
            } else {
                if (operatorSecondType && amountOfBracketsForMathFunc == brackets) {
                    OperatorType reversedOperator;
                    getInverseOperator(mathOperator, reversedOperator);
                    possibleCells.push_back(new Operator(reversedOperator)); // todo proc to vypada podobne???
                    operatorSecondType = false;
                } else {
                    possibleCells.push_back(new Operator(OperatorType::BRACKETCLOSE));
                    --brackets;
                }

            }
            inputString.erase(0, 1);
        } else {
            if (mathOperator)
                delete mathOperator;
            mathOperator = parseStringToMathFunction(inputString);
            if (mathOperator) {
                possibleCells.push_back(new Operator(*mathOperator));
                deleteThisUglySpaces(inputString);
                if (inputString[0] != '(')
                    throw "Invalid expression. Try 'help' for more information.\n";
                inputString.erase(0, 1);

                operatorSecondType = true;
                amountOfBracketsForMathFunc = brackets;
                if (operatorFirstType)   // jestli operator +, -, *, / -pak za nim jde cislo nebo reference, tak by zadne problemy vyskytnout nemely
                    operatorFirstType = false;
            } else {
                aggregationFunction = parseStringToAggregationFunction(inputString);
                if (aggregationFunction) {
                    parseAggregationFuncValue(inputString, possibleCells, aggregationFunction, delimiters);
                    if (operatorFirstType)   // jestli operator +, -, *, / -pak za nim jde cislo nebo referencee, tak by zadne problemy vyskytnout nemely
                        operatorFirstType = false;
                } else {
                    break;
                }
            }
        }
        deleteThisUglySpaces(inputString);

    }

    if (mathOperator)
        delete mathOperator;
    deleteThisUglySpaces(inputString);
    if (brackets || operatorFirstType || operatorSecondType)
        throw "Invalid parameter. Try 'help' for more information.\n";
    deleteThisUglySpaces(inputString);
    if (inputString.size() > 0)
        throw "Invalid parameter. Try 'help' for more information.\n";

    delete possibleCells.back();
    possibleCells.pop_back();

}

void Command::parseStringToNumber(std::string &inputString, std::string &number) const {
    int dots = 0, position = 0;
    for (char input : inputString) {
        if ((input >= 48 && input <= 57))
            number += input;
        else if (input == '.') {
            number += '.';
            ++dots;
        } else {
            break;
        }
        ++position;
    }
    inputString.erase(0, (unsigned long) position);
    if (dots > 1)
        throw "Invalid parameter. Try 'help' for more information.\n";
}

OperatorType *Command::parseStringToMathFunction(std::string &inputString) const {
    OperatorType *mathOperator = nullptr;

    if (inputString.size() < 3)
        return nullptr;

    std::string firstCommand = inputString.substr(0, 4);

    if (firstCommand == "sqrt") {
        mathOperator = new OperatorType;
        *mathOperator = OperatorType::SQRTOPEN;
    } else if (firstCommand == "log2") {
        mathOperator = new OperatorType;
        *mathOperator = OperatorType::LOG2OPEN;
    }
    if (mathOperator) {
        inputString.erase(0, 4);
        return mathOperator;
    }

    firstCommand = inputString.substr(0, 3);

    if (firstCommand == "sin") {
        mathOperator = new OperatorType;
        *mathOperator = OperatorType::SINOPEN;
    } else if (firstCommand == "cos") {
        mathOperator = new OperatorType;
        *mathOperator = OperatorType::COSOPEN;
    } else if (firstCommand == "tan") {
        mathOperator = new OperatorType;
        *mathOperator = OperatorType::TANOPEN;
    } else if (firstCommand == "abs") {
        mathOperator = new OperatorType;
        *mathOperator = OperatorType::ABSOPEN;
    } else if (firstCommand == "log") {
        mathOperator = new OperatorType;
        *mathOperator = OperatorType::LOGOPEN;
    }
    if (mathOperator) {
        inputString.erase(0, 3);
        return mathOperator;
    }


    firstCommand = inputString.substr(0, 5);
    if (firstCommand == "round") {
        mathOperator = new OperatorType;
        *mathOperator = OperatorType::ROUNDOPEN;
    }
    if (mathOperator) {
        inputString.erase(0, 5);
        return mathOperator;
    }
    return nullptr;
}

OperatorType *Command::parseStringToAggregationFunction(std::string &inputString) const {
    OperatorType *aggregationFctionOperator = nullptr;

    if (inputString.size() < 3)
        return nullptr;

    std::string firstCommand = inputString.substr(0, 3);

    if (firstCommand == "avg") {
        aggregationFctionOperator = new OperatorType;
        *aggregationFctionOperator = OperatorType::AVGOPEN;
    } else if (firstCommand == "sum") {
        aggregationFctionOperator = new OperatorType;
        *aggregationFctionOperator = OperatorType::SUMOPEN;
    } else if (firstCommand == "max") {
        aggregationFctionOperator = new OperatorType;
        *aggregationFctionOperator = OperatorType::MAXOPEN;
    }
    if (aggregationFctionOperator) {
        inputString.erase(0, 3);
        return aggregationFctionOperator;
    }

    return nullptr;
}

void Command::parseAggregationFuncValue(std::string &inputString, std::vector<Cell *> &possibleCells,
                                        const OperatorType *aggregationFunction, bool *delimiters) const {

    deleteThisUglySpaces(inputString);
    if (inputString[0] != '(')
        throw "Invalid expression. Try 'help' for more information.\n";
    inputString.erase(0, 1);
    int xCoorFirstParameter, yCoorFirstParameter, xCoorSecondParameter, yCoorSecondParameter;
    parseStringToCoordinates(xCoorFirstParameter, yCoorFirstParameter, inputString, delimiters);
    delimiters[3] = false;
    parseStringToCoordinates(xCoorSecondParameter, yCoorSecondParameter, inputString, delimiters);

    if (!delimiters[3])
        throw "Invalid expression. Try 'help' for more information.\n";

    deleteThisUglySpaces(inputString);
    possibleCells.push_back(new Operator(*aggregationFunction));
}

void Command::evaluateExpression(const int &yCoor, const int &xCoor) const {
    std::vector<const Cell *> insideOfExpression;
    std::vector<const Cell *> expressionWithoutReferences;

    Model::getInstance()->getElement(yCoor, xCoor)->evaluate(insideOfExpression);
    for (const Cell *cell : insideOfExpression) {
        if (cell->getType() == CellType::REFERENCE) {
            std::vector<const Cell *> detectorOfCyclus;
            expressionWithoutReferences.push_back(new Operator(OperatorType::BRACKETOPEN)); // todo pamet!!!!!!!!!!!!!
            detectorOfCyclus.push_back(Model::getInstance()->getElement(yCoor, xCoor));
            referenceEvaluation(cell, detectorOfCyclus, expressionWithoutReferences);
            expressionWithoutReferences.push_back(new Operator(OperatorType::BRACKETCLOSE));
        } else {
            expressionWithoutReferences.push_back(cell);
        }
    }
    insideOfExpression.clear();
    InfixToPostfix(expressionWithoutReferences, insideOfExpression);
    const Number *result = evaluatePostfixExpression(insideOfExpression);
    std::cout << result->ToString(false) << " ";

}

void Command::referenceEvaluation(const Cell *actualCell, std::vector<const Cell *> &detectorOfCyclus,
                                  std::vector<const Cell *> &expressionWithoutReferences) const { //zaroven najdeme cyklickou zavislost
    for (auto dependence : detectorOfCyclus) {
        if (dependence == actualCell)
            throw "Cyclic dependency.\n";
    }

    int xCoord = ((const Reference *) actualCell->getValue())->getXCoor();
    int yCoord = ((const Reference *) actualCell->getValue())->getYCoor();

    if (Model::getInstance()->getElement(yCoord, xCoord)->getType() == CellType::NUMBER ||
        Model::getInstance()->getElement(yCoord, xCoord)->getType() == CellType::OPERATION) {
        expressionWithoutReferences.push_back(Model::getInstance()->getElement(yCoord, xCoord));
    } else if (Model::getInstance()->getElement(yCoord, xCoord)->getType() == CellType::REFERENCE) {
        detectorOfCyclus.push_back(
                Model::getInstance()->getElement(yCoord, xCoord));// jestli je to reference, pridej na zasobnik
        expressionWithoutReferences.push_back(new Operator(OperatorType::BRACKETOPEN));
        referenceEvaluation(Model::getInstance()->getElement(yCoord, xCoord), detectorOfCyclus,
                            expressionWithoutReferences);
        expressionWithoutReferences.push_back(new Operator(OperatorType::BRACKETCLOSE));
        detectorOfCyclus.pop_back(); // a pak odeber po vraceni ze zanoreni
    } else if (Model::getInstance()->getElement(yCoord, xCoord)->getType() == CellType::EXPRESSION) {
        std::vector<const Cell *> partsOfCell;
        Model::getInstance()->getElement(yCoord, xCoord)->evaluate(partsOfCell);
        expressionWithoutReferences.push_back(new Operator(OperatorType::BRACKETOPEN));
        for (auto partOfCell : partsOfCell) {
            referenceEvaluation(partOfCell, detectorOfCyclus, expressionWithoutReferences);
        }
        expressionWithoutReferences.push_back(new Operator(OperatorType::BRACKETCLOSE));
    }
}

void Command::InfixToPostfix(std::vector<const Cell *> &expressionWithoutReferences,
                             std::vector<const Cell *> &insideOfExpression) const {
    std::stack<const Operator *> ss;
    for (const Cell *cell : expressionWithoutReferences) {
        if (cell->getType() == CellType::NUMBER) { //todo pridat REFERENCE
            insideOfExpression.push_back(cell);
        }
        if (cell->getType() == CellType::OPERATION) {
            OperatorType basicOperator = ((const Operator *) cell)->returnOperatorType();

            if (!((const Operator *) cell)->IsClosedOperator(basicOperator) &&
                // jestli neni otviraci/zavirajici operator
                !((const Operator *) cell->getValue())->IsOpenedOperator(basicOperator)) {
                while (!ss.empty() &&
                       !((const Operator *) cell)->IsOpenedOperator(ss.top()->returnOperatorType()) &&
                       ((const Operator *) cell)->HasHigherPrecedence(ss.top()->returnOperatorType())) {
                    insideOfExpression.push_back(ss.top());
                    ss.pop();
                }
                ss.push(((const Operator *) cell));
            } else if (((const Operator *) cell)->IsOpenedOperator(basicOperator)) {
                ss.push((const Operator *) cell);
            } else if (((const Operator *) cell)->IsClosedOperator(basicOperator)) {
                OperatorType openedBracket = ((const Operator *) cell->getValue())->returnOpenedBracket();

                while (!ss.empty() && ss.top()->returnOperatorType() != openedBracket) {
                    insideOfExpression.push_back(ss.top());
                    ss.pop();
                }
                insideOfExpression.push_back(ss.top());
                ss.pop();
            }
        }
    }

    while (!ss.empty()) {
        insideOfExpression.push_back(ss.top());
        ss.pop();
    }
}

void Command::getCoord(std::string &temporaryForCutting, std::string &cord) const {
    unsigned position = 0;
    for (; position < temporaryForCutting.size(); ++position) {
        if (temporaryForCutting[position] == ' ' || temporaryForCutting[position] == ',' ||
            temporaryForCutting[position] == ')') {
            break;
        }

        if (temporaryForCutting[position] >= 48 && temporaryForCutting[position] <= 57) {
            cord += temporaryForCutting[position];
        } else
            throw "Invalid parameters! Try 'help' for help!\n";
    }
    temporaryForCutting.erase(0, (unsigned long) position);
}

void Command::getResizeParameters(std::string &temporaryForCutting, int &yCoor, int &xCoor) const {

    deleteThisUglySpaces(temporaryForCutting);
    std::string firstXCoor, secondYCoor;
    std::vector<char> delim = {',', ' '};

    getCoord(temporaryForCutting, firstXCoor);

    if (temporaryForCutting[0] == ' ') {
        deleteThisUglySpaces(temporaryForCutting);
    }

    if (temporaryForCutting[0] != ',')
        throw "Invalid parameters! Try 'help' for help!\n";
    temporaryForCutting.erase(0, 1);

    deleteThisUglySpaces(temporaryForCutting);
    getCoord(temporaryForCutting, secondYCoor);

    if (temporaryForCutting[0] == ' ') {
        deleteThisUglySpaces(temporaryForCutting);
    }

    if (temporaryForCutting[0] != ')')
        throw "Invalid parameters! Try 'help' for help!\n";

    temporaryForCutting.erase(0, 1);
    deleteThisUglySpaces(temporaryForCutting);

    if (temporaryForCutting.size() > 0)
        throw "Invalid parameters! Try 'help' for help!\n";

    xCoor = std::stoi(firstXCoor);
    yCoor = std::stoi(secondYCoor);
}

void Command::getLoadSaveParameter(std::string &temporaryForCutting, std::string &loadingPath, bool &exit) const {
    deleteThisUglySpaces(temporaryForCutting);

    if (temporaryForCutting[0] != '"')
        throw "Invalid parameters! Try 'help' for help!\n";
    temporaryForCutting.erase(0, 1);
    unsigned position = 0;
    for (; position < temporaryForCutting.size(); ++position) {
        if (temporaryForCutting[position] == '"') {
            ++position;
            break;
        }
        loadingPath += temporaryForCutting[position];
    }

    temporaryForCutting.erase(0, (unsigned long) position);
    deleteThisUglySpaces(temporaryForCutting);
    if (!exit) {
        if (temporaryForCutting.empty() || temporaryForCutting[0] != ')')
            throw "Invalid parameters! Try 'help' for help!\n";

        temporaryForCutting.erase(0, 1);
        deleteThisUglySpaces(temporaryForCutting);

        if (!temporaryForCutting.empty())
            throw "Invalid parameters! Try 'help' for help!\n";
    }
}

void Command::writeToFile(std::ofstream &myFileSave) const {
    if (Model::getInstance()->wasResized())
        myFileSave << "resize( " << Model::getInstance()->getWidth() << ", " << Model::getInstance()->getHeight()
                   << ")\n";
    for (unsigned i = 1; i <= Model::getInstance()->getHeight(); ++i) {
        for (unsigned j = 0; j < Model::getInstance()->getWidth(); ++j) {
            if (Model::getInstance()->getElement(i, j) != nullptr) {
                if (Model::getInstance()->getElement(i, j)->getType() == CellType::TEXT)
                    myFileSave << "set( $" << (char) (j + FirstA) << "$" << i << ", \""
                               << Model::getInstance()->getElement(i, j)->ToString(true) << "\")\n";
                else
                    myFileSave << "set( $" << (char) (j + FirstA) << "$" << i << ", "
                               << Model::getInstance()->getElement(i, j)->ToString(true) << ")\n";
            }
        }
    }
}

void Command::exitOrHelpCorrectCommand(std::string &temporaryForCutting) const {
    deleteThisUglySpaces(temporaryForCutting);
    if (!temporaryForCutting.empty())
        throw "Invalid parameters! Try 'help' for help!\n";
}

bool Command::SaveTableBeforeExit(const std::string &decision) const {
    if (decision == "yes")
        return true;
    else if (decision == "no")
        return false;
    else
        throw "Wrong answer. You can write only \"yes\"\\\"no\".\n";
}

void Command::getInverseOperator(OperatorType *&mathOperator, OperatorType &reversedOperator) const {

    if (*mathOperator == OperatorType::SINOPEN)
        reversedOperator = OperatorType::SINCLOSE;

    else if (*mathOperator == OperatorType::SQRTOPEN)
        reversedOperator = OperatorType::SQRTCLOSE;

    else if (*mathOperator == OperatorType::ABSOPEN)
        reversedOperator = OperatorType::ABSCLOSE;

    else if (*mathOperator == OperatorType::COSOPEN)
        reversedOperator = OperatorType::COSCLOSE;

    else if (*mathOperator == OperatorType::TANOPEN)
        reversedOperator = OperatorType::TANCLOSE;

    else if (*mathOperator == OperatorType::ROUNDOPEN)
        reversedOperator = OperatorType::ROUNDCLOSE;

    else if (*mathOperator == OperatorType::LOGOPEN)
        reversedOperator = OperatorType::LOGCLOSE;

    else if (*mathOperator == OperatorType::LOG2OPEN)
        reversedOperator = OperatorType::LOG2CLOSE;

    else if (*mathOperator == OperatorType::AVGOPEN)
        reversedOperator = OperatorType::AVGCLOSE;

    else if (*mathOperator == OperatorType::SUMOPEN)
        reversedOperator = OperatorType::SUMCLOSE;

    else if (*mathOperator == OperatorType::MAXOPEN)
        reversedOperator = OperatorType::MAXCLOSE;

}

const Number *Command::evaluatePostfixExpression(
        std::vector<const Cell *> &postfixExpression) const { // todo opravit problem s pameti!!!!
    std::stack<const Number *> ss;
    for (auto &cellPointer : postfixExpression) {
        if (cellPointer->getType() == CellType::NUMBER) {
            ss.push((const Number *) cellPointer);
        } else if (cellPointer->getType() == CellType::OPERATION) {
            int weight = ((const Operator *) cellPointer)->getWeighOfOperator();
            if (weight <= 2) {
                if (ss.size() < 2)
                    throw "Invalid expression. Try 'help' for more information.\n";
                auto second = ss.top()->getNumber();
                ss.pop();
                auto first = ss.top()->getNumber();
                ss.pop();
                double result = ((const Operator *) cellPointer)->evaluateNumbers(first, second);
                ss.push(new Number(result));
            } else if (weight == 3) {

            } else {
                if (ss.empty())
                    throw "Invalid expression. Try 'help' for more information.\n";
                auto first = ss.top()->getNumber();
                ss.pop();
                double result = (((const Operator *) cellPointer)->evaluateNumbers(first));
                ss.push(new Number(result));
            }
        }
    }
    const Number *finalResults = ss.top();
    ss.pop();

    if (!ss.empty())
        throw "Invalid expression. Try 'help' for more information.\n";
    return finalResults;

}

