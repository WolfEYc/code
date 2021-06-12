#include "truthtable.hpp"

int main(int argc, char** argv){

    truthtable table;

    for(int i = 1; i < argc; i++){
        table.addExpression(argv[i]);
    }

    table.buildTable();
    table.display();
    table.write();

    return 0;
}