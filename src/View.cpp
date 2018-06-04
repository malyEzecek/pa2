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
        warnings.clear();
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

void View::Help() const {
    std::string c = "a";
    c[0] = '"';
    std::string BashCom = "echo " + c +  "\t\t\t\t\t\t\t\t\t\tConsole \n\n Spreadsheet:"
            "\n\n\n\n\n\tNAME:"
            "\n\n\t\t Simple console spreadsheet"
            "\n\n\n\n\tDESCRIPTION:"
            "\n\n\t\t  Simple spreadsheet (something like sc). The program on the command line creates simple "
            "\n\t\t  table. It features basic calculation and can summarizes data from the exact part of the table."
            "\n\t\t  CS has the basic features of all spreadsheets, using a grid of cells arranged in numbered "
            "\n\t\t  rows and letter-named columns to organize data manipulations like arithmetic operations."
            "\n\t\t  Also it supports different trigonometric functions like sin(), cos() and tan()."
            "\n\t\t  Some aggregate function ( max(), avg(), sum()) are also included in our program."
            "\n\n\n\n\n\tCOMMANDS:"
            "\n\t\t  All commands aren't case sensitive."
            "\n\n\t\t SET( COORDINATES, VALUE )       change value of the cell on COORDINATES position in the table"
            "\n\n\t\t CLEAR( COORDINATES )            delete value of the cell on COORDINATES position in the table"
            "\n\n\t\t GETVALUE( COORDINATES )         show value of the cell as a console output"
            "\n\n\t\t RESIZE( UNSIGNED, UNSIGNED )    change table size. Be CAREFUL!"
            "\n\t\t                                 DELETE CELL VALUES FROM THE TABLE IF IT'S OUT OF THE TABLE BOARDERS."
            "\n\n\t\t SAVE( PATH )                    save table values and size like a set of commands to the PATH."
            "\n\n\t\t LOAD( PATH )                    load saved table values from the PATH. All previous table changes"
            "\t\t                                 will be deleted."
            "\n\n\t\t EXIT                            exit program. Asks if user want to save table. If answer is \"yes\""
            "\t\t                                    write PATH."


                                                 "\n\n\n\n\n\tSYNTAX:"
            "\n\n\t\t COORDINATES                     Position of the cell in the table. Not splitted. Write $LetterOfColumn$NumberOfRow."
            "\n\t\t                                   LetterOfColumn - a range from A to ZZ. NumberOf Column - a range from 1 to 999."
            "\n\n\t\t VALUES                          Cell can accept different types of values like TEXT, NUMBER, BOOLEAN, REFERENCE, "
            "\n\t\t                                   and EXPRESSION."
            "\n\n\t\t TEXT    Show manual for this program"
            "\n\t\t           It can be set as first parameter"
            "\n\n\t\t REFERENCE                       Has the same syntax like coordinates."

            "\n\n\t\t NUMBER                          It's typical double digit."

            "\n\n\t\t BOOLEAN                         Only two possible values : true and false"

            "\n\t\t           "
            "\n\n\t\t -(w)      Last parameter is web page, which you want to download."
            "\n\n\n\t\t\t         Example:     downloader -ajp -3 www.example.com/test.html "
            "\n\n\n\n\n\n" + c + "| less";
    char *Command = new char[BashCom.length() + 1];
    strcpy(Command, BashCom.c_str());
    system(Command);

    delete [] Command;
}

bool View::CheckParameters(const int &argc, char **argv) const {
    if(argc == 2){
        if(argv[1][0] == '-' && argv[1][1] == '-' && argv[1][2] == 'h' && argv[1][3] == 'e'&& argv[1][4] == 'l' && argv[1][5] == 'p'){      //help
            Help();
            return true;
        }
        return false;
    }
}
