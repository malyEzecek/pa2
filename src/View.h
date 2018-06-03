//
// Created by julinka on 2.5.18.
//

#ifndef EDITOR_VIEW_H
#define EDITOR_VIEW_H

#include <cmath>
#include <iostream>
#include <sstream>
#include "Command.h"

class View {
private:

    void StringToLower(std::string &stringToBeChanged) const;

public:
    void createTable() const;

};


#endif //EDITOR_VIEW_H