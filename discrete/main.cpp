#include "truthtable.hpp"

int main(int argc, char** argv){

    static truthtable* tables = new truthtable[argc-1];

    for(int i = 1; i < argc; i++){
        tables[i-1].setExpression(argv[i]);
    }

    for(int i = 0; i < argc - 1; i++){
        tables[i].buildTable();
        tables[i].display();
    }

    delete[] tables;

    return 0;
}