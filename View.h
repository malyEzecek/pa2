//
// Created by julinka on 2.5.18.
//

#ifndef EDITOR_VIEW_H
#define EDITOR_VIEW_H

#include "Model.h"

class View{
private:
    void createTable(const Model & model);
    void clearTable();
public:
    void Refresh();

};


#endif //EDITOR_VIEW_H