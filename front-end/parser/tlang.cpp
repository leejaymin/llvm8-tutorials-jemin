#include "llvm/ADT/STLExtras.h"
#include <iostream> 

#include "tlang.h"

using namespace std;

// ----------------- Lexer ----------------- //

static char consume() {
  return module_ifs.get(); 
}

/// gettok - Return the next token from standard input.
static int gettok() {
  static int LastChar = ' ';

  // Skip any whitespace.
  while (isspace(LastChar))
    LastChar = consume();

  if (isalpha(LastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
    IdStr = LastChar;
    while (isalnum((LastChar = consume())))
      IdStr += LastChar;

    if (IdStr == "fun")
      return tok_fun;
    
    return tok_id;
  }

  if (isdigit(LastChar)) { // Number: [0-9]+
    string NumStr;
    do {
      NumStr += LastChar;
      LastChar = consume();
    } while (isdigit(LastChar));

    NumVal = stoi(NumStr);
    return tok_num;
  }

  // Check for end of file.  Don't eat the EOF.
  if (LastChar == EOF)
    return tok_eof;

  // Otherwise, just return the character as its ascii value.
  int ThisChar = LastChar;
  LastChar = consume();
  return ThisChar;
}

static int getNextToken() {
  return CurTok = gettok();
}

// ----------------- Parser ----------------- //

static unique_ptr<ExpAST> ParseExpression();

static unique_ptr<ExpAST> ParseExpression(unique_ptr<ExpAST> LHS) {
  char Op; 
  getNextToken();
  
  switch (CurTok) {
    case '+':
      Op = '+';
      break;
    case '-':
      Op = '-';
      break;
    case '}':
      return LHS;
    default:
      cerr << "Unknown token when expecting '+', '-', or '}'" << endl;
      return nullptr;
  }
  
  if (auto RHS = ParseExpression())
    return llvm::make_unique<BinaryExpAST>(Op, move(LHS), move(RHS));

  return nullptr;
}

static unique_ptr<ExpAST> ParseExpression() {
  std::unique_ptr<ExpAST> LHS;
  
  getNextToken();
  switch (CurTok) {
    case tok_id:
      LHS = llvm::make_unique<VariableExpAST>(IdStr);
      break;
    case tok_num:
      LHS = llvm::make_unique<NumberExpAST>(NumVal);
      break;
    default:
      cerr << "Unknown token when expecting an expression" << endl;
      return nullptr;
  }

  return ParseExpression(move(LHS));
}

static unique_ptr<FunctionDeclAST> ParseFunctionDefinition() {
  getNextToken(); // eat fun.
  if (CurTok != tok_id) {
    cerr << "Expected function name in function definition" << endl;
    return nullptr;
  } 
  string FunName = IdStr;
  
  getNextToken();
  if (CurTok != '(') {
    cerr << "Expected '(' in function definition" << endl;  
    return nullptr;
  }

  vector<string> ArgNames;

  getNextToken();
  if (CurTok != tok_id) {
    cerr << "Expected argument name in function definition" << endl;
    return nullptr;
  } 
  ArgNames.push_back(IdStr);

  getNextToken();
  while (CurTok != ')') {
    if (CurTok != ',') {
      cerr << "Expected ',' in function definition" << endl;
      return nullptr;
    }

    getNextToken();
    if (CurTok != tok_id) {
      cerr << "Expected argument name in function definition" << endl;
      return nullptr;
    } 
    ArgNames.push_back(IdStr);

    getNextToken();  
  } 
  
  getNextToken();  
  if (CurTok != '{') {
    cerr << "Expected '{' in function definition" << endl;  
    return nullptr;
  }

  if (auto E = ParseExpression())
    return llvm::make_unique<FunctionDeclAST>(FunName, ArgNames, move(E));
  
  return nullptr;
}

static void HandleFunctionDefinition() {
  if (ParseFunctionDefinition()) {
    cout << "Parsed a function definition." << endl;
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

static void MainLoop() {
  while (1) {
    switch (CurTok) {
      case tok_eof:
        return;
      case tok_fun:
        HandleFunctionDefinition();
        break;
      default:
        // Skip token for error recovery.
        getNextToken();
    }
  }
}

int main (int argc, char *argv[]) {
  if (argc != 2) {
    cerr << "Usage: funlang [Input File]" << endl;
    return -1;
  }

  module_ifs.open(argv[1]);
  if(!module_ifs.is_open()) {
    cerr << "Error: Cannot open " << argv[1] << endl;
    return -1;
  }

  getNextToken();
  MainLoop();

  module_ifs.close();

  return 0;
}
