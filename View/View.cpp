//
// Created by julinka on 2.5.18.
//
#include <iostream>
#include "View.h"

void View::Refresh() const {}

/**
 * Get model as a parameter and transform the information from the model
 * to an typical "Excel table".
 * @param model
 */

void View::createTable() const {

    Model *model = Model::getInstance();
    Command controller;

    std::string columnName = "         A      ";

//    if (model->getWidth() > WIDTHMAX)
//        throw "The table can not be wider!\n";
//    if (model->getHeight() > HEIGHTMAX)
//        throw "The table can not be higher!\n";

//    initscr(); //open window
//    start_color();
//    init_pair(1, COLOR_BLACK, COLOR_WHITE);
//    nocbreak(); // let the terminal do the line editing

    std::string inputString;
    bool changed = true;
    bool exit = false;
    // move(3, 0); // posun vystupu o 3 radky dolu
    do {
        if (exit)
            return;

        if (changed) {
            for (unsigned i = 0, actualPositionLastLetter = 9; i < model->getWidth(); ++i) {

//                attron(COLOR_PAIR(1));
//                attron(A_BOLD);
                std::cout << columnName; // todo const_cast<char *>(columnName.c_str()));
//                attroff(A_BOLD);
//                attroff(COLOR_PAIR(1));
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
            std::cout << std::endl;// todo printw("\n");

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

//                attron(COLOR_PAIR(1));
//                attron(A_BOLD);
                std::cout << numberColumn; //todo printw(const_cast<char *>(numberColumn.c_str()));
//                attroff(A_BOLD);
//                attroff(COLOR_PAIR(1));

                for (unsigned j = 0; j < model->getWidth(); ++j) {
                    if (!model->getElement(i, j))
                        std::cout << "            "; //todo
                    else {
                        if (model->getElement(i, j)->getType() == CellType::EXPRESSION) {
                            controller.evaluateExpression(i, j);
                        } else if (model->getElement(i, j)->getType() == CellType::REFERENCE){
                            controller.evaluateReference(i, j);
                        }

                        else
                            std::cout << model->getElement(i, j)->ToString(false) << " ";

                        //todo (const_cast<char *>)
                    }
                }
                std::cout << std::endl; // todo
            }
            //refresh(); //make it appear on the screen!!!!!
        }
        changed = false;
        std::cout << "Please, enter a command : "; //todo in the beginning
        // move(0, 26);
//        inputCharacter = getch();
//        inputString += (char) inputCharacter;

        getline(std::cin, inputString);
        //if (inputCharacter == '\n') {
        StringToLower(inputString);
        controller.SetCommand(inputString, exit);
        changed = true;
        columnName = "         A      ";
        //}

    } while (changed);

    //endwin();

}

void View::clearTable() const {}

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