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
#include "llvm/IR/Instructions.h"
#include "llvm/Support/Debug.h"
#include "llvm/Analysis/LoopInfo.h"
#include "HelloFunction.h"

#define DEBUG_TYPE "hello"

bool HelloFunction::runOnFunction(Function &F) {
/*
  for(BasicBlock &BB : F){
      for(Instruction &I : BB){
        if(CallInst* CI = dyn_cast<CallInst>(&I)){
          dbgs() << CI->getCalledFunction()->getName() << "\n";
        }
      }
    }
*/
 // dbddgs() <<"Function name:" << F.getName() << "\n";
 //  dbgs() <<"# of CallInst:" << count << "\n";
  LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();

  for (Loop *L : LI){
    dbgs() << L->getName() << "\n";  
  }

  for (Loop *L : LI){
    PHINode *Node = L->getCanonicalInductionVariable();
    if(Node){
      Node->dump();
    }
  }
  return false;
}

void HelloFunction::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.addRequired<LoopInfoWrapperPass>();
  AU.setPreservesAll();
}

char HelloFunction::ID = 0;
static RegisterPass<HelloFunction> Y("helloFunction", "Hello World Pass ");
