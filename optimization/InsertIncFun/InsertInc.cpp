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
#include "InsertInc.h"
#include "llvm/IR/Value.h"

#define DEBUG_TYPE "hello"

bool InsertInc::runOnModule(Module &M) {
  
  LLVMContext &Context =M.getContext();

  Constant *newF = M.getOrInsertFunction("inc", \
    Type::getInt32Ty(Context), \
    Type::getInt32Ty(Context));
   
  BasicBlock *BB = BasicBlock::Create(Context, "entry", 
    dyn_cast<Function>(newF));

  Argument *Arg = dyn_cast<Function>(newF)->arg_begin();
  Constant *One = ConstantInt::get(Type::getInt32Ty(Context), 1);

  IRBuilder<> Builder(BB); 
  Value *result = Builder.CreateAdd(Arg,One);
  Builder.CreateRet(result);

  return true;
}

void InsertInc::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesAll();
}

char InsertInc::ID = 0;
static RegisterPass<InsertInc> X("InsertInc", "InsertInc Pass ");
