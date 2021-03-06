#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <stack>

#include <iostream>

using namespace llvm;

class NBlock;

class CodeGenBlock
{
public:
    BasicBlock *block;
    Value *returnValue;
    std::map<std::string, Value *> locals;
};

class CodeGenContext
{
    std::stack<CodeGenBlock *> blocks;
    Function *mainFunction;

    std::stack<Function *> parentFunctions;

public:
    Module *module;
    CodeGenContext() { module = new Module( "main", getGlobalContext() ); }

    void generateCode( NBlock &root );
    GenericValue runCode();
    std::map<std::string, Value *> &locals() { return blocks.top()->locals; }
    BasicBlock *currentBlock()
    {
        return blocks.top()->block;
    }
    void pushBlock( BasicBlock *block )
    {
        CodeGenBlock *b = new CodeGenBlock();
        if(!blocks.empty())b->locals = blocks.top()->locals;
        b->block = block;
        blocks.push( b );
    }
    void popBlock()
    {
        CodeGenBlock *top = blocks.top();
        blocks.pop();
        delete top;
    }
    void setCurrentReturnValue( Value *value ) { blocks.top()->returnValue = value; }
    Value *getCurrentReturnValue() { return blocks.top()->returnValue; }

    void pushParentFunction( Function *function ) { parentFunctions.push( function ); }
    void popParentFunction() { parentFunctions.pop(); }
    Function *getParentFunction() { return parentFunctions.top(); }
};
