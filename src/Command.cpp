//
// Created by julinka on 19.5.18.
//

#include "Command.h"

Command::Command() {}

CommandType Command::returnCommandType() const {
    return typeOfCommand;
}

void Command::ExecuteCommand(std::string &temporaryForCutting, bool *delimiters, bool &exit) {
    switch (typeOfCommand) {
        case CommandType::SET : {
            int xCoor, yCoor;
            parseStringToCoordinates(xCoor, yCoor, temporaryForCutting, delimiters);
            if (xCoor >= Model::getInstance()->getWidth() || yCoor > Model::getInstance()->getHeight()) {
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
                Model::getInstance()->clearTable();

                if (Model::getInstance()->getWidth() != Model::WIDTH ||
                    Model::getInstance()->getHeight() != Model::HIGHT)
                    Model::getInstance()->resizeTable(Model::HIGHT, Model::WIDTH);

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
            return;
        }
        case CommandType::GETVALUE : {
            deleteThisUglySpaces(temporaryForCutting);
            int xCoor, yCoor;
            parseStringToCoordinates(xCoor, yCoor, temporaryForCutting, delimiters);

            if (xCoor >= Model::getInstance()->getWidth() || yCoor > Model::getInstance()->getHeight()) {
                std::cout << "Size of the table is too small. Try to use resize()." << std::endl;
                return;
            }

            if (!Model::getInstance()->getElement(yCoor, xCoor))
                std::cout << "null" << std::endl;
            else
                std::cout << Model::getInstance()->getElement(yCoor, xCoor)->ToString(true) << std::endl;
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

            throw InvalidInput("This command doesn't exist. Try 'help' for more information.\n");
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
    } else if (parsedCommand == "getvalue") {
        return CommandType::GETVALUE;
    } else
        throw InvalidInput("This command doesn't exist. Try 'help' for more information.\n");
}

CommandType Command::parseToCommand(std::string &inputString, bool *delimiters) const {
    std::string parsedCommand;
    deleteThisUglySpaces(inputString);
    if (inputString[0] != 'c' && inputString[0] != 'e' && inputString[0] != 's'
        && inputString[0] != 'l' && inputString[0] != 'r' && inputString[0] != 'h'
        && inputString[0] != 'g')
        throw InvalidInput("This command doesn't exist. Try 'help' for more information.\n");
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
    inputString.erase(0, parsedCommand.size());

    if (delimiters[0] && !delimiters[1]) {
        deleteThisUglySpaces(inputString);
        if (inputString[0] != '(' && parsedCommand != "exit" || (parsedCommand == "exit" && !inputString.empty()))
            throw InvalidInput("This command doesn't exist. Try 'help' for more information.\n");
        delimiters[1] = true;
    }
    inputString.erase(0, 1);
    return SwitchTypeOfCommand(parsedCommand);
}

void Command::parseToXYString(std::string &inputString, std::string &xCoorString, std::string &yCoorString,
                              std::vector<char> &delim, bool first, bool breakMoment, int &position,
                              bool *delimiters) const {

    for (unsigned amount = 0; position < (int) inputString.size() - 1; ++position, ++amount) {
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
                throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");
            xCoorString += std::to_string((int) inputString[position] - Reference::FirstA);
        } else {
            if (inputString[position] < 48 || inputString[position] > 57)
                throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");
            yCoorString += inputString[position];
        }

        if (amount >= 7)
            throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");
    }
}

void Command::parseStringToCoordinates(int &xCoor, int &yCoor, std::string &inputString, bool *delimiters,
                                       bool firstParameter) const {

    deleteThisUglySpaces(inputString);
    if (inputString[0] != '$')
        throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");
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
            throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");
    }

    if (xCoorString.size() > 2 || yCoorString.size() > 3)
        throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");
    try{
        xCoor = std::stoi(xCoorString);
    } catch (std::invalid_argument &e){
        throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");
    }

    try{
        yCoor = std::stoi(yCoorString);
    } catch(std::invalid_argument &e){
        throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");
    }
    if (firstParameter)
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
                throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");
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
            throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");
        }
        returnText += inputChar;
        ++position;
    }

    inputString.erase(0, (unsigned long) position + 1);
    deleteThisUglySpaces(inputString);

    if (inputString[0] != ')')
        throw ("Invalid parameter syntax. Try 'help' for more information.\n");
    inputString.erase(0, 1);
    deleteThisUglySpaces(inputString);

    return returnText;
}

void Command::parseStringToBool(std::string &inputString) const {
    deleteThisUglySpaces(inputString);
    if (inputString[0] != ')')
        throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");
    inputString.erase(0, 1);
    deleteThisUglySpaces(inputString);
}

void Command::parseExpressionError(std::vector<Cell *> &possibleCells) const {
    for (auto i : possibleCells) {
        delete i;
    }
    throw InvalidInput("Invalid expression syntax. Try 'help' for more information.\n");
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
            parseStringToCoordinates(xCoor, yCoor, inputString, delimiters, false);
            if (xCoor >= Model::getInstance()->getWidth() || yCoor > Model::getInstance()->getHeight()) {
                std::cout << "Size of the table is too small. Try to use resize()." << std::endl;
                return;
            }
            possibleCells.push_back(new Reference(xCoor, yCoor));
            reference = true;
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
                parseExpressionError(possibleCells);

            switch (inputString[0]) {
                case '+': {
                    if (possibleCells.empty())
                        parseExpressionError(possibleCells);
                    possibleCells.push_back(new Operator(OperatorType::PLUS));
                    break;
                }
                case '-': {
                    possibleCells.push_back(new Operator(OperatorType::MINUS));
                    break;
                }
                case '/': {
                    if (possibleCells.empty())
                        parseExpressionError(possibleCells);
                    possibleCells.push_back(new Operator(OperatorType::DIVIDE));
                    break;
                }
                case '*': {
                    if (possibleCells.empty())
                        parseExpressionError(possibleCells);
                    possibleCells.push_back(new Operator(OperatorType::MULTIPLY));
                    break;
                }
                default:
                    parseExpressionError(possibleCells);
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
                    parseExpressionError(possibleCells);
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
        throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");
    deleteThisUglySpaces(inputString);
    if (inputString.size() > 0)
        throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");

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
        throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");
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
        throw InvalidInput("Invalid expression. Try 'help' for more information.\n");
    inputString.erase(0, 1);
    int xCoorFirstParameter, yCoorFirstParameter, xCoorSecondParameter, yCoorSecondParameter;
    parseStringToCoordinates(xCoorFirstParameter, yCoorFirstParameter, inputString, delimiters);
    delimiters[3] = false;
    parseStringToCoordinates(xCoorSecondParameter, yCoorSecondParameter, inputString, delimiters);

    if (!delimiters[3])
        throw InvalidInput("Invalid expression. Try 'help' for more information.\n");

    deleteThisUglySpaces(inputString);
    possibleCells.push_back(new Operator(*aggregationFunction));
}

const Number *Command::evaluateExpression(const Cell *expression, std::vector<const Cell *> &checkReferences) const {
    std::vector<const Cell *> insideOfExpression;
    std::vector<const Cell *> expressionWithoutReferences;
    const Number *result = nullptr;

    expression->evaluate(insideOfExpression);
    for (const Cell *cell : insideOfExpression) {
        if (cell->getType() == CellType::REFERENCE) {

            for (auto &reference : checkReferences) {
                if (cell == reference) {
                    return result;
                }
            }
            std::vector<const Cell *> detectorOfCyclus = checkReferences;
            detectorOfCyclus.push_back(expression);

            referenceEvaluation(cell, detectorOfCyclus, expressionWithoutReferences);
        } else {
            expressionWithoutReferences.push_back(cell);
        }
    }
    insideOfExpression.clear();
    InfixToPostfix(expressionWithoutReferences, insideOfExpression);
    result = evaluatePostfixExpression(insideOfExpression);
    return result;

}

void Command::referenceEvaluation(const Cell *actualCell, std::vector<const Cell *> &detectorOfCyclus,
                                  std::vector<const Cell *> &expressionWithoutReferences) const { //zaroven najdeme cyklickou zavislost
    if (!actualCell)
        throw InvalidExpressionOrReference("Null reference.\n"); // todo VYJIMKA
    if (actualCell->getType() != CellType::NUMBER && actualCell->getType() != CellType::REFERENCE &&
        actualCell->getType() != CellType::OPERATION && actualCell->getType() != CellType::EXPRESSION)
        throw InvalidExpressionOrReference(
                "Invalid reference inside expression.\n"); // todo STEJNA VYJIMKA JAKO O 2 RADKY VEJS

    for (auto dependence : detectorOfCyclus) {
        if (dependence == actualCell)
            throw InvalidExpressionOrReference("Cyclic dependency.\n");
    }

    if (actualCell->getType() == CellType::NUMBER || actualCell->getType() == CellType::OPERATION) {
        expressionWithoutReferences.push_back(actualCell);
    } else if (actualCell->getType() == CellType::REFERENCE) {
        detectorOfCyclus.push_back(actualCell);// jestli je to reference, pridej na zasobnik
        int newXCoor = ((Reference *) actualCell)->getXCoor();
        int newYCoor = ((Reference *) actualCell)->getYCoor();
        referenceEvaluation(Model::getInstance()->getElement(newYCoor, newXCoor), detectorOfCyclus,
                            expressionWithoutReferences);
        detectorOfCyclus.pop_back(); // a pak odeber po vraceni ze zanoreni
    } else if (actualCell->getType() == CellType::EXPRESSION) {
        const Number *number = evaluateExpression(actualCell, detectorOfCyclus);
        expressionWithoutReferences.push_back((const Cell *) number);
    }
}

void Command::InfixToPostfix(std::vector<const Cell *> &expressionWithoutReferences,
                             std::vector<const Cell *> &insideOfExpression) const {
    std::stack<const Operator *> ss;
    for (const Cell *cell : expressionWithoutReferences) {
        if (cell->getType() == CellType::NUMBER) {
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
                if (openedBracket != OperatorType::BRACKETOPEN)
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
            throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");
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
        throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");
    temporaryForCutting.erase(0, 1);

    deleteThisUglySpaces(temporaryForCutting);
    getCoord(temporaryForCutting, secondYCoor);

    if (temporaryForCutting[0] == ' ') {
        deleteThisUglySpaces(temporaryForCutting);
    }

    if (temporaryForCutting[0] != ')')
        throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");

    temporaryForCutting.erase(0, 1);
    deleteThisUglySpaces(temporaryForCutting);

    if (temporaryForCutting.size() > 0)
        throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");

    xCoor = std::stoi(firstXCoor);
    yCoor = std::stoi(secondYCoor);
}

void Command::getLoadSaveParameter(std::string &temporaryForCutting, std::string &loadingPath, bool &exit) const {
    deleteThisUglySpaces(temporaryForCutting);

    if (temporaryForCutting[0] != '"')
        throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");
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
            throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");

        temporaryForCutting.erase(0, 1);
        deleteThisUglySpaces(temporaryForCutting);

        if (!temporaryForCutting.empty())
            throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");
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
                    myFileSave << "set( $" << (char) (j + Reference::FirstA) << "$" << i << ", \""
                               << Model::getInstance()->getElement(i, j)->ToString(true) << "\")\n";
                else
                    myFileSave << "set( $" << (char) (j + Reference::FirstA) << "$" << i << ", "
                               << Model::getInstance()->getElement(i, j)->ToString(true) << ")\n";
            }
        }
    }
}

void Command::exitOrHelpCorrectCommand(std::string &temporaryForCutting) const {
    deleteThisUglySpaces(temporaryForCutting);
    if (!temporaryForCutting.empty())
        throw InvalidInput("Invalid parameter syntax. Try 'help' for more information.\n");
}

bool Command::SaveTableBeforeExit(const std::string &decision) const {
    std::string line = decision;
    while (true) {
        if (line == "yes")
            return true;
        else if (line == "no")
            return false;
        std::cout << "Wrong answer. You can write only \"yes\"\\\"no\". Please, try again" << std::endl;
        getline(std::cin, line);
    }
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

void Command::postfixExpressionError(std::stack<const Number *> ss) const {

    if (!ss.empty()) {

        while (!ss.empty()) {
            if (ss.top()->addedInPostfixFunction())
                delete ss.top();
            ss.pop();
        }
    }
}


const Number *Command::evaluatePostfixExpression(std::vector<const Cell *> &postfixExpression) const {
    std::stack<const Number *> ss;
    for (auto &cellPointer : postfixExpression) {
        if (cellPointer->getType() == CellType::NUMBER) {
            ss.push((const Number *) cellPointer);
        } else if (cellPointer->getType() == CellType::OPERATION) {
            int weight = ((const Operator *) cellPointer)->getWeighOfOperator();
            if (weight <= 2) {
                if (ss.size() < 2) {
                    postfixExpressionError(ss);
                    throw InvalidExpressionOrReference("Invalid expression. Try 'help' for more information.\n");
                }

                auto second = ss.top()->getNumber();

                if (ss.top()->addedInPostfixFunction())
                    delete ss.top();
                ss.pop();

                auto first = ss.top()->getNumber();

                if (ss.top()->addedInPostfixFunction())
                    delete ss.top();

                ss.pop();

                double result;
                try {
                    result = ((const Operator *) cellPointer)->evaluateNumbers(first, second);
                } catch (InvalidMathematicalExpression & e){
                    postfixExpressionError(ss);
                    throw InvalidExpressionOrReference(e.getStr());
                }
                ss.push(new Number(result, true));
            } else if (weight == 3) {
                if (ss.size() < 2) {
                    postfixExpressionError(ss);
                    throw InvalidExpressionOrReference("Invalid expression. Try 'help' for more information.\n");
                }

            } else {
                if (ss.empty()) {
                    postfixExpressionError(ss);
                    throw InvalidExpressionOrReference("Invalid expression. Try 'help' for more information.\n");
                }

                auto first = ss.top()->getNumber();

                if (ss.top()->addedInPostfixFunction())
                    delete ss.top();
                ss.pop();
                double result = (((const Operator *) cellPointer)->evaluateNumbers(first));
                ss.push(new Number(result, true));
            }
        }
    }

    const Number *finalResults = ss.top();
    ss.pop();

    if (!ss.empty()) {
        postfixExpressionError(ss);
        throw InvalidExpressionOrReference("Invalid expression. Try 'help' for more information.\n");
    }
    return finalResults;

}

void Command::evaluateReference(const unsigned &height, const unsigned &width,
                                std::vector<const Cell *> &checkCycles) const {
    if (width >= Model::getInstance()->getWidth() || height > Model::getInstance()->getHeight()) {
        std::cout << "Size of the table is too small. Try to use resize()." << std::endl;
        return;
    }
    for (auto reference : checkCycles) { // kontrola na mozne cyklicke zavislosti
        if (Model::getInstance()->getElement(height, width) == reference)
            throw InvalidExpressionOrReference("Cyclic dependency.\n");

    }

    unsigned newYCoor = ((Reference *) Model::getInstance()->getElement(height, width))->getYCoor();
    unsigned newXCoor = ((Reference *) Model::getInstance()->getElement(height, width))->getXCoor();

    if (!Model::getInstance()->getElement(newYCoor, newXCoor)) {
        std::cout << "       null ";
        return;
    } else {
        if (Model::getInstance()->getElement(newYCoor, newXCoor)->getType() == CellType::EXPRESSION) {
            checkCycles.push_back(Model::getInstance()->getElement(height, width));

            const Number *number = evaluateExpression(Model::getInstance()->getElement(newYCoor, newXCoor),
                                                      checkCycles);
            std::cout << number->ToString(false) << " ";
            delete number;

        } else if (Model::getInstance()->getElement(newYCoor, newXCoor)->getType() == CellType::REFERENCE) {
            checkCycles.push_back(Model::getInstance()->getElement(height, width));
            evaluateReference(newYCoor, newXCoor, checkCycles);
        } else {
            std::cout << Model::getInstance()->getElement(newYCoor, newXCoor)->ToString(false) << " ";
        }
    }


}
