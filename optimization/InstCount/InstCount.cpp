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
#include "llvm/Support/Debug.h"
#include "InstCount.h"

#define DEBUG_TYPE "hello"

bool InstCount::runOnFunction(Function &F) {
  int count =0;
    for(BasicBlock &BB : F){
      for(Instruction &I : BB){
        count++;
      }
    }
  dbgs() <<"Function name: " << F.getName() <<"\n";
  dbgs() << count << "\n";
  return false;
}

void InstCount::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesAll();
}

char InstCount::ID = 0;
static RegisterPass<InstCount> X("InstCount", "InstCount Pass ");
