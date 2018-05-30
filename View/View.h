//
// Created by julinka on 2.5.18.
//

#ifndef EDITOR_VIEW_H
#define EDITOR_VIEW_H

#include <math.h>
//#include <ncurses.h>
#include <sstream>
#include "../Controller/Command.h"

class View {
private:
    const int WIDTHMAX = 676; // (A-Z)*(A-Z)
    const int HEIGHTMAX = 9999; // max amount of lines

    void clearTable() const;

    void StringToLower(std::string &stringToBeChanged) const;

public:
    void createTable() const;

    void Refresh() const;

};


#endif //EDITOR_VIEW_H