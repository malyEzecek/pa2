//
// Created by julinka on 2.5.18.
//

#ifndef EDITOR_VIEW_H
#define EDITOR_VIEW_H

#include <math.h>
//#include <ncurses.h>
#include <sstream>
#include "Command.h"

class View{
private:
    const int WIDTHMAX = 676;
    const int HEIGHTMAX = 9999;
    void clearTable();
    void StringToLower(std::string &stringToBeChanged);
public:
    void createTable();
    void Refresh();

};


#endif //EDITOR_VIEW_H