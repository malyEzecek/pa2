//
// Created by julinka on 2.5.18.
//
#include "View.h"

/**
 * Get model as a parameter and transform the information from the model
 * to an typical "Excel table".
 * @param model
 */

void View::createTable() const {

    Model *model = Model::getInstance();
    Command controller;

    std::string columnName = "         A      ";

    std::string inputString;
    bool changed = true;
    bool exit = false;
    std::string warnings;

    do {
        warnings.clear();
        if (exit) {
            break;
        }

        if (changed) {
            for (unsigned i = 0, actualPositionLastLetter = 9; i < model->getWidth(); ++i) {
                std::cout << columnName;
                if (!i) {
                    columnName = "     B      ";
                    actualPositionLastLetter = 5;
                    continue;
                }

                if (i < 25) {
                    ++columnName[actualPositionLastLetter];
                } else if (i > 25) {
                    if (!((i - 25) % 26)) {
                        ++columnName[actualPositionLastLetter - 1];
                        columnName[actualPositionLastLetter] = 'A';
                    } else {
                        ++columnName[actualPositionLastLetter];
                    }
                } else {
                    columnName = "     A      ";
                    actualPositionLastLetter = 6;
                    columnName[actualPositionLastLetter] = 'A';
                }
            }
            std::cout << std::endl;

            int amountOfNumber;
            for (unsigned i = 1; i <= model->getHeight(); ++i) {
                amountOfNumber = (int) log10(i) + 1;
                std::string numberColumn;
                if (amountOfNumber == 1) {
                    numberColumn = "  ";
                    numberColumn += std::to_string(i) += " ";
                } else if (amountOfNumber == 2) {
                    numberColumn = " ";
                    numberColumn += std::to_string(i) += "  ";
                } else if (amountOfNumber == 3) {
                    numberColumn += std::to_string(i) += " ";
                } else {
                    numberColumn += std::to_string(i);
                }
                std::cout << numberColumn;

                for (unsigned j = 0; j < model->getWidth(); ++j) {
                    if (!model->getElement(i, j))
                        std::cout << "            ";
                    else {
                        std::vector<const Cell *> checkCyclesInReferences;
                        if (model->getElement(i, j)->getType() == CellType::EXPRESSION) {

                            try {
                                const Number *number = controller.evaluateExpression(model->getElement(i, j),
                                                                                     checkCyclesInReferences);
                                std::cout << number->ToString(false) << " ";
                                delete number;
                            } catch (InvalidExpressionOrReference &e) {
                                std::cout << "       null ";
                                warnings = e.getStr();
                            }

                        } else if (model->getElement(i, j)->getType() == CellType::REFERENCE) {
                            try {
                                controller.evaluateReference(i, j, checkCyclesInReferences);
                            } catch (InvalidExpressionOrReference & e) {
                                std::cout << "       null ";
                                warnings = e.getStr();
                            }

                        } else
                            std::cout << model->getElement(i, j)->ToString(false) << " ";
                    }
                }
                std::cout << std::endl;
            }

        }
        std::cout << warnings << std::endl;
        changed = false;
        std::cout << "Please, enter a command : ";

        getline(std::cin, inputString);

        StringToLower(inputString);

        try {
            controller.SetCommand(inputString, exit);
        } catch (InvalidInput &e) {
            std::cout << e.getStr();
        }

        changed = true;
        columnName = "         A      ";

    } while (changed);

    Model::releaseInstance();
}

void View::StringToLower(std::string &stringToBeChanged) const {
    int i = 0;
    while (stringToBeChanged[i]) {
        if (stringToBeChanged[i] < 65 || i > stringToBeChanged[i]) {
            ++i;
            continue;
        }
        stringToBeChanged[i] = (char) tolower(stringToBeChanged[i]);
        ++i;
    }
}