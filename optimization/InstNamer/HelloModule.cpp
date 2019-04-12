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
#include "llvm/IR/Type.h"
#include "HelloModule.h"
#include "llvm/IR/Metadata.h"

#define DEBUG_TYPE "hello"

bool HelloModule::runOnModule(Module &M) {
  LLVMContext &Context = M.getContext();
  int id = 0;

for(Function &F : M){
    for(BasicBlock &BB : F){
      for(Instruction &I : BB){
        Constant *IDConstant = ConstantInt::get(Type::getInt32Ty(Context), id);
        Metadata *IDMD = (Metadata*) ConstantAsMetadata::get(IDConstant);
        std::vector<Metadata*> MDs = {IDMD};
        MDNode *Node = MDNode::get(Context, MDs);
        I.setMetadata("name", Node);
        id++;
      }
    }
  }


  return false;
}

void HelloModule::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesAll();
}

char HelloModule::ID = 0;
static RegisterPass<HelloModule> X("helloModule", "Hello World Pass ");
