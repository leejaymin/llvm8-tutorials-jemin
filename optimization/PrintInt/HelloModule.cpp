//===- Hello.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements two versions of the LLVM "Hello World" pass described
// in docs/WritingAnLLVMPass.html
//
//===----------------------------------------------------------------------===//

#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Instructions.h"
#include "HelloModule.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/BasicBlock.h"

#define DEBUG_TYPE "hello"

bool HelloModule::runOnModule(Module &M) {
  
  LLVMContext &Context =M.getContext();

  Function *F = M.getFunction("printInt");
  if(!F){
    return false;
  }

  BasicBlock &BB = *F->begin();
  
  Instruction *PrintCall = nullptr;

  for (Instruction &I : BB){
    if(CallInst *CI = dyn_cast<CallInst>(&I)){
      if(CI->getCalledFunction()->getName() == "printf"){
        PrintCall = CI;
      }
    }
  }

  if(!PrintCall){
    return false;
  }

  BasicBlock *black = BB.splitBasicBlock(PrintCall);
  BB.getTerminator()->eraseFromParent();
  
  BasicBlock *RetBB = BasicBlock::Create(Context, "retbb", F);
  IRBuilde<> RetBBBuilder(RetBB);
  RetBBBuilder.CreateRetVoid();

  IRBuilder<> EntryBBBuilder(&BB);

  //F->dump();

  Argument *Arg = F->arg_begin();
  Constant *Two = ConstantInt::get(Type::getInt32Ty(Context), 2);
  Value *Remainder = EntryBBBuilder.CreateSRem(Arg, Two);

  Constant *One = ConstantInt::get(Type::getInt32Ty(Context), 1);
  Value *IsOdd = EntryBBBuilder.CreateICmpEQ(Remainder, One);

  EntryBBBuilder.CreateCondBr(IsOdd, RetBB, black);

  return true;
}

void HelloModule::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesAll();
}

char HelloModule::ID = 0;
static RegisterPass<HelloModule> X("helloModule", "Hello World Pass ");
