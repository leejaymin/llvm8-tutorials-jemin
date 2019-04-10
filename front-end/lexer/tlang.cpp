#include <iostream> 

#include "tlang.h"

using namespace std;

static char consume() {
  return module_ifs.get(); 
}

/// gettok - Return the next token from input file stream.
static int gettok() {
  static int LastChar = ' ';

  // Skip any whitespace.
  while (isspace(LastChar))
    LastChar = consume();

  if (isalpha(LastChar)) { // id: [a-zA-Z][a-zA-Z0-9]*
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

static void printCurTok() {    
  switch (CurTok) {
    case tok_eof:
      cout << "EOF";
      break;
    case tok_fun: 
      cout << "FUN";
      break;
    case tok_id:
      cout << "ID(\"" << IdStr << "\")";
      break;
    case tok_num:
      cout << "NUM(" << NumVal << ")";
      break;
    default:
      cout << (char)CurTok;
  }
  cout << " ";
}

int main (int argc, char *argv[]) {
  if (argc != 2) {
    cerr << "Usage: funlang [Input File]" << std::endl;
    return -1;
  }

  module_ifs.open(argv[1]);
  if(!module_ifs.is_open()) {
    cerr << "Error: Cannot open " << argv[1] << std::endl;
    return -1;
  }

  // For test lexer
  do {
    getNextToken();
    printCurTok();
  } while(CurTok != tok_eof);

  cout << endl;

  module_ifs.close();

  return 0;
}
