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
#include "NamePrinter.h"

#define DEBUG_TYPE "hello"

bool NamePrinter::runOnFunction(Function &F) {
  dbgs() <<"Hello: "<< F.getName()<<"\n";
  return false;
}

void NamePrinter::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesAll();
}

char NamePrinter::ID = 0;
static RegisterPass<NamePrinter> Y("NamePrinter", "Hello World Pass ");
