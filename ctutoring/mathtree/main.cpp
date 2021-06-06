//
//  main.cpp
//  CS260Lab5
//
//  Created by Jim Bailey on 5/3/18.
//  Copyright © 2018 Jim Bailey. All rights reserved.
//

#include <iostream>

#include "ParseTree.hpp"

#define TEST_BASE
#define TEST_ADV
#define TEST_THINK


int main(int argc, const char * argv[]) {
#ifdef TEST_BASE
    
    std::cout << "Testing Base Parse Tree" << std::endl << std::endl;
    
    std::string expression1 = "AB+CD-*";
    std::string expression2 = "AB-C+DE/*";
    
    ParseTree ptree1(expression1);
    std::cout << "Input is AB+CD-* " << std::endl;
    std::cout << "In Order should be ((A+B)*(C-D)) or (((A)+(B))*((C)-(D))) and is " << ptree1.inOrder() << std::endl;
    std::cout << "Post Order should be AB+CD-* and is " << ptree1.postOrder() << std::endl;
    std::cout << "Pre Order should be *+AB-CD and is " << ptree1.preOrder() << std::endl << std::endl;
    
    ParseTree ptree2(expression2);
    std::cout << "Input is AB-C+DE/* " << std::endl;
    std::cout << "In Order output should be (((A-B)+C)*(D/E)) or ((((A)-(B))+(C))*((D)/(E))) and is" << ptree2.inOrder() << std::endl;
    std::cout << "Post Order should be AB-C+DE/* and is " << ptree2.postOrder() << std::endl;
    std::cout << "Pre Order should be *+-ABC/DE and is " << ptree2.preOrder() << std::endl;
    
    std::cout << "Done with Parse Tree test" << std::endl << std::endl;
    
#endif // TEST_BASE

    
    return 0;
}

