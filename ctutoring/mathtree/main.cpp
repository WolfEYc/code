//
//  main.cpp
//  CS260Lab5
//
//  Created by Jim Bailey on 5/3/18.
//  Copyright Â© 2018 Jim Bailey. All rights reserved.
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
    std::cout << "In Order output should be (((A-B)+C)*(D/E)) or ((((A)-(B))+(C))*((D)/(E))) and is " << ptree2.inOrder() << std::endl;
    std::cout << "Post Order should be AB-C+DE/* and is " << ptree2.postOrder() << std::endl;
    std::cout << "Pre Order should be *+-ABC/DE and is " << ptree2.preOrder() << std::endl;
    
    std::cout << "Done with Parse Tree test" << std::endl << std::endl;
    
#endif // TEST_BASE
    
#ifdef TEST_ADV
    std::cout << "Testing Advanced Parse Tree" << std::endl << std::endl;
    
    std::string expression3 = "(A+B)*C+D";
    std::string expression4 = "A/(B+C)*(D+E)";
    ParseTree ptree3("");

    ptree3.parseInOrder(expression3);
    std::cout << "Input is (A+B)*C+D" << std::endl;
    std::cout << "In Order should be (((A+B)*C)+D) or ((((A)+(B))*(C))+(D)) and is " << ptree3.inOrder() << std::endl;
    std::cout << "Post Order should be AB+C*D+ and is " << ptree3.postOrder() << std::endl;
    std::cout << "Pre Order should be +*+ABCD and is " << ptree3.preOrder() << std::endl << std::endl;
    
    ptree3.parseInOrder(expression4);
    std::cout << "Input is A/(B+C)*(D+E)" << std::endl;
    std::cout << "In Order should be ((A/(B+C))*(D+E)) or (((A)/((B)+(C)))*((D)+(E))) and is " << ptree3.inOrder() << std::endl;
    std::cout << "Post Order should be ABC+DE+*/ and is " << ptree3.postOrder() << std::endl;
    std::cout << "Pre Order should be /A*+BC+DE and is " << ptree3.preOrder() << std::endl << std::endl;
    
    std::cout << "Done with Advanced Parse Tree test" << std::endl << std::endl;
    
#endif // TEST_ADV
    
#ifdef TEST_THINK
    std::cout << "Testing Thinking Problem" << std::endl << std::endl;
    
    std::string expression5 = "(A+B)*C+D*(F/G)";
    std::string expression6 = "A*B+(C-D)";
    ParseTree ptree4("");

    ptree4.parseInOrder(expression5);
    std::cout << "Input is (A+B)*C+D*(F/G)" << std::endl;
    std::cout << "In Order should be (A+B)*C+D*F/G and is " << ptree4.inOrder() << std::endl << std::endl;
    std::cout << "Post Order should be AB+C*DFG/*+ and is " << ptree4.postOrder() << std::endl;
    std::cout << "Pre Order should be +*+ABC*D/FG and is " << ptree4.preOrder() << std::endl << std::endl;
    
    ptree4.parseInOrder(expression6);
    std::cout << "Input is A*B+(C-D)" << std::endl;
    std::cout << "In Order should be A*B+C-D and is " << ptree4.inOrder() << std::endl << std::endl;
    std::cout << "Post Order should be AB*CD-+ and is " << ptree4.postOrder() << std::endl;
    std::cout << "Pre Order should be +*AB-CD and is " << ptree4.preOrder() << std::endl << std::endl;
    
    std::cout << "Done with Testing Thinking Problem" << std::endl << std::endl;
    
#endif // TEST_THINK
    
    return 0;
}