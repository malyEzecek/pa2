//
// Created by julinka on 2.5.18.
//

#ifndef EDITOR_VIEW_H
#define EDITOR_VIEW_H

#include <cmath>
#include <iostream>
#include <sstream>
#include <cstring>
#include "Command.h"

class View {
private:

    void StringToLower(std::string &stringToBeChanged) const;

public:
    void createTable() const;

    void Help() const;

    bool CheckParameters(char * argv[]) const;

};


#endif //EDITOR_VIEW_H