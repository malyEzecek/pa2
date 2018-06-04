#include "View.h"


int main(int argc, char *argv[]) {
    View newView;

    if (argc == 2){
        newView.createTable();
    } else  {
        newView.CheckParameters(argv);
    }
    return 0;
}