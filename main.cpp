#include <iostream>
#include "codegen.h"
#include "node.h"

using namespace std;

extern int yyparse();
extern NBlock* programBlock;

int main(int argc, char **argv)
{
    yyparse();
    std::cout << programBlock << std::endl;

    CodeGenContext context;

    if(!programBlock)
    {
        std::cout << "ERROR: could not parse code. exiting..." << std::endl;
        return 1; 
    }

    context.generateCode(*programBlock);
    context.runCode();

    return 0;
}
