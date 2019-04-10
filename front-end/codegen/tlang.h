#ifndef TUTORIAL_FRONT_END_TLANG_H
#define TUTORIAL_FRONT_END_TLANG_H

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"

#include <fstream>
#include <vector>

using namespace std;
using namespace llvm;

static ifstream module_ifs;

// ----------------- Lexer ----------------- //
// The lexer returns tokens [0-255] if it is an unknown character, otherwise one
// of these for known things.
enum Token {
  tok_eof = -1,

  tok_fun = -2,

  tok_id = -3,
  tok_num = -4
};

static string IdStr;     // Filled in if tok_identifier
static double NumVal;         // Filled in if tok_number

static int CurTok;

// ----------------- Parser ----------------- //
/// ExpAST - Base class for all expression nodes.
class ExpAST {
public:
  virtual ~ExpAST() {}
  virtual Value *Codegen() = 0;
};

/// BinaryExpAST - Expression class for a binary operator.
class BinaryExpAST : public ExpAST {
  char Op;
  unique_ptr<ExpAST> LHS, RHS;

public:
  BinaryExpAST(char op, unique_ptr<ExpAST> LHS,
               unique_ptr<ExpAST> RHS)
    : Op(op), LHS(move(LHS)), RHS(move(RHS)) {}
  virtual Value *Codegen();
};

/// VariableExpAST - Expression class for referencing a variable, like "a".
class VariableExpAST : public ExpAST {
  string Name;

public:
  VariableExpAST(const string &Name) : Name(Name) {}
  virtual Value *Codegen();
};

/// NumberExpAST - Expression class for numeric literals like "1.0".
class NumberExpAST : public ExpAST {
  double Val;

public:
  NumberExpAST(double Val) : Val(Val) {}
  virtual Value *Codegen();
};

/// FunctionDeclAST - This class represents a function definition itself.
class FunctionDeclAST {
  string FunName;
  vector<string> ArgNames;

  unique_ptr<ExpAST> Body;

public:
  FunctionDeclAST(string FunName, vector<string> &ArgNames,
                  unique_ptr<ExpAST> Body)
    : FunName(FunName), ArgNames(ArgNames), Body(move(Body)) {}
  virtual Function *Codegen();
};

// ----------------- CodeGen ----------------- //

static LLVMContext Context;
static IRBuilder<> Builder(Context);
static std::unique_ptr<Module> M;
static std::map<std::string, Value *> VariableMap;

#endif
