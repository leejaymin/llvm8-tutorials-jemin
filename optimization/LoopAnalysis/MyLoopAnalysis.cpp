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
#include "MyLoopAnalysis.h"

#define DEBUG_TYPE "hello"

bool MyLoopAnalysis::runOnFunction(Function &F) {

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

void MyLoopAnalysis::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.addRequired<LoopInfoWrapperPass>();
  AU.setPreservesAll();
}

char MyLoopAnalysis::ID = 0;
static RegisterPass<MyLoopAnalysis> Y("MyLoopAnalysis", "MyLoopAnalysis Pass ");
