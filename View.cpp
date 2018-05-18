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

void View::createTable( const Model & model ) {
    std::string columnName = "         A     ";

    if( model.getWidth() > WIDTHMAX )
        throw "The table can not be wider!\n";
    if( model.getHeight() > HEIGHTMAX )
        throw "The table can not be higher!\n";

    //initscr(); //open window
    //move(2,0); // posun vystupu o 2 radky dolu
    for( int i = 0, actualPositionLastLetter = 9; i < model.getWidth(); ++i ) {
        std::cout << columnName;
        if( i < 25 ){
            ++columnName[actualPositionLastLetter];
        } else if ( i > 25 ){
            if( !(  (i - 25) % 26 ) ){
                ++columnName[actualPositionLastLetter - 1];
                columnName[actualPositionLastLetter] = 'A';
            } else{
                ++columnName[actualPositionLastLetter];
            }
        }
        else {
            columnName = "     A     " ;
            actualPositionLastLetter = 6;
            columnName[actualPositionLastLetter] = 'A';
        }
    }
    std::cout<< "\n";

    int amountOfNumber;
    for( int i = 1; i <= model.getHeight(); ++i ){
        amountOfNumber = (int)log10( i ) + 1;
        std::string numberColumn;
        if( amountOfNumber == 1 ){
            numberColumn = "   ";
            numberColumn += std::to_string(i);
        } else if( amountOfNumber == 2 ){
            numberColumn = "  ";
            numberColumn += std::to_string(i);
        } else if( amountOfNumber == 3 ){
            numberColumn = " ";
            numberColumn += std::to_string(i);
        } else {
            numberColumn += std::to_string(i);
        }
        std::cout<< numberColumn;

        const Cell * pointerOnCell;
        for( int j = 0; j < model.getWidth(); ++j ){
            if( !( pointerOnCell = model.getElement(i, j) ))
                std::cout<< "           ";
            else {
                std::cout << pointerOnCell->ToString();
            }
        }
        std::cout << "\n";

        //refresh(); //make it appear on the screen!!!!!
        //endwin(); //close window
    }
}

void View::clearTable() {}