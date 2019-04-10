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
#include "CallCount.h"

#define DEBUG_TYPE "hello"

bool CallCount::runOnFunction(Function &F) {

  for(BasicBlock &BB : F){
      for(Instruction &I : BB){
        if(CallInst* CI = dyn_cast<CallInst>(&I)){
          dbgs() << CI->getCalledFunction()->getName() << "\n";
        }
      }
    }
 
  return false;
}

void CallCount::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.addRequired<LoopInfoWrapperPass>();
  AU.setPreservesAll();
}

char CallCount::ID = 0;
static RegisterPass<CallCount> Y("CallCount", "CallCount Pass ");
