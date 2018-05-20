//
// Created by julinka on 2.5.18.
//
#include <iostream>
#include <string>
#include "View.h"

void View::Refresh() {}

/**
 * Get model as a parameter and transform the information from the model
 * to an typical "Excel table".
 * @param model
 */

void View::createTable() {
    std::string columnName = "         A     ";

    Model * model = Model::getInstance();

//    if (model->getWidth() > WIDTHMAX)
//        throw "The table can not be wider!\n";
//    if (model->getHeight() > HEIGHTMAX)
//        throw "The table can not be higher!\n";

    initscr(); //open window
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    nocbreak(); // let the terminal do the line editing

    printw("Please, enter a command : ");

    int inputCharacter;
    std::string inputString;
    bool changed = true;
    move(3, 0); // posun vystupu o 3 radky dolu
    do {
        if (changed) {
            for (int i = 0, actualPositionLastLetter = 9; i < model->getWidth(); ++i) {

                attron(COLOR_PAIR(1));
                attron(A_BOLD);
                printw(const_cast<char *>(columnName.c_str()));
                attroff(A_BOLD);
                attroff(COLOR_PAIR(1));

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
                    columnName = "     A     ";
                    actualPositionLastLetter = 6;
                    columnName[actualPositionLastLetter] = 'A';
                }
            }
            printw("\n");

            int amountOfNumber;
            for (int i = 1; i <= model->getHeight(); ++i) {
                amountOfNumber = (int) log10(i) + 1;
                std::string numberColumn;
                if (amountOfNumber == 1) {
                    numberColumn = "   ";
                    numberColumn += std::to_string(i);
                } else if (amountOfNumber == 2) {
                    numberColumn = "  ";
                    numberColumn += std::to_string(i);
                } else if (amountOfNumber == 3) {
                    numberColumn = " ";
                    numberColumn += std::to_string(i);
                } else {
                    numberColumn += std::to_string(i);
                }

                attron(COLOR_PAIR(1));
                attron(A_BOLD);
                printw(const_cast<char *>(numberColumn.c_str()));
                attroff(A_BOLD);
                attroff(COLOR_PAIR(1));

                for (int j = 0; j < model->getWidth(); ++j) {
                    if (!model->getElement(i, j).getCellSize())
                        printw("           ");
                    else {
                        printw(const_cast<char *>(model->getElement(i, j).ToString().c_str()));
                    }
                }
                printw("\n");
            }
            refresh(); //make it appear on the screen!!!!!
        }
        changed = false;
        move(0, 26);
        inputCharacter = getch();
        inputString += (char) inputCharacter;
        if (inputCharacter == '\n') {
            StringToLower(inputString);

        }

    } while (inputString != "exit\n");

    endwin();

}

void View::clearTable() {}

void View::StringToLower(std::string &stringToBeChanged) {
    for (char i : stringToBeChanged) {
        if (i < 65 || i > 90)
            continue;
        i = (char) tolower(i);
    }
}