#include <iostream>
#include "View.h"
#include "Model.h"

int main() {

    Model modelFirst;
    std::cout << "Write something on your monitor.\n";
    View newView;
    newView.createTable( modelFirst );
    return 0;
}