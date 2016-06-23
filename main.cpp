#include <iostream>
#include "codegen.h"
#include "node.h"

using namespace std;

extern int yyparse();
extern NBlock* programBlock;

int main(int argc, char **argv)
{
    std::cout << argc << ", " << argv[0] << std::endl;
    yyparse();
    std::cout << programBlock << std::endl;

    CodeGenContext context;

    if(!programBlock)
    {
        std::cout << "ERROR: could not parse code. exiting..." << std::endl;
        return 1;
    }

    context.generateCode(*programBlock);
    //context.runCode();

    std::cout << "Saving bytecode to code.ll" << std::endl;
    FILE *file = fopen("code.ll", "w");
    llvm::raw_fd_ostream stream(fileno(file), true);
    llvm::WriteBitcodeToFile(context.module, stream);
    return 0;
}
