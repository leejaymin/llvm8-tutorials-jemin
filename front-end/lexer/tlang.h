#ifndef TUTORIAL_FRONT_END_TLANG_H
#define TUTORIAL_FRONT_END_TLANG_H

#include <fstream>
static std::ifstream module_ifs;

// The lexer returns tokens [0-255] if it is an unknown character, 
// otherwise one of these for known things.
enum Token {
  tok_eof = -1,

  tok_fun = -2,

  tok_id = -3,
  tok_num = -4
};

static std::string IdStr; // Filled in if tok_id
static double NumVal;     // Filled in if tok_num

static int CurTok;

#endif
