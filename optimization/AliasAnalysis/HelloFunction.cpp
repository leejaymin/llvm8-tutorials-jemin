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
#include "llvm/Analysis/AliasAnalysis.h"
#include "HelloFunction.h"
#include "llvm/Support/Debug.h"
#define DEBUG_TYPE "hello"

bool HelloFunction::runOnFunction(Function &F) {
  AAResults &AA = getAnalysis<AAResultsWrapperPass>().getAAResults();

  std::vector<Instruction*> InstVector;


  for (BasicBlock &BB : F){
    for (Instruction &I : BB){
      InstVector.push_back(&I);
    }
  }

  auto Begin = InstVector.begin(), End = InstVector.end();
  for(auto it = Begin; it != End; it++){
    for(auto next_it = it + 1; next_it != End; next_it++){
      
      AliasResult Result = AA.alias(*it, *next_it);

        if(Result == NoAlias){
          dbgs() <<"NoAlias: \n";
          (*it)->dump();
          (*next_it)->dump();
        } else if (Result == MayAlias){
          dbgs() <<"May Alias: \n";
          (*it)->dump();
          (*next_it)->dump();
        } else if (Result == PartialAlias){
          dbgs() <<"Partial Alias: \n";
          (*it)->dump();
          (*next_it)->dump();
        } else if (Result == MustAlias){
          dbgs() <<"Must Alias: \n";
          (*it)->dump();
          (*next_it)->dump();
        }
      }
  }

  return false;
}

void HelloFunction::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.addRequired<AAResultsWrapperPass>();
  AU.setPreservesAll();
}

char HelloFunction::ID = 0;
static RegisterPass<HelloFunction> Y("helloFunction", "Hello World Pass ");
