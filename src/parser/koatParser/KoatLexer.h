
// Generated from Koat.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"




class  KoatLexer : public antlr4::Lexer {
public:
  enum {
    COM = 1, GOAL = 2, CPX = 3, TERM = 4, START = 5, SINK = 6, FS = 7, VAR = 8, 
    RULES = 9, PLUS = 10, MINUS = 11, TIMES = 12, BWAND = 13, EXP = 14, 
    LPAR = 15, RPAR = 16, RBRACK = 17, LBRACK = 18, LCURL = 19, RCURL = 20, 
    TO = 21, COMMA = 22, AND = 23, OR = 24, LT = 25, LEQ = 26, EQ = 27, 
    NEQ = 28, GEQ = 29, GT = 30, CONDSEP = 31, ID = 32, INT = 33, WS = 34, 
    COMMENT = 35
  };

  explicit KoatLexer(antlr4::CharStream *input);

  ~KoatLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

