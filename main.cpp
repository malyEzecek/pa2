#include <iostream>
#include "View.h"
#include "Model.h"

int main() {

    std::cout << "Write something on your monitor.\n";
    View newView;
    newView.createTable();
    return 0;
}