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
    /**
     * Transform input string to lower case string.
     * @param stringToBeChanged input string that program transform to lower case.
     */
    void StringToLower(std::string &stringToBeChanged) const;

public:
    /**
     * Create new Model.
     */
    void createTable() const;

    /**
     *  Help if --help param is set, then, print help in terminal
     */
    void Help() const;

    /**
     * Check_Param check if there is any parameter
     * @param argv array of input parameters
     * @return true if --help parameter is used, false if not
     */
    bool CheckParameters(char * argv[]) const;

};


#endif //EDITOR_VIEW_H