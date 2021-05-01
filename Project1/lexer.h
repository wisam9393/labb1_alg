#ifndef LEXER_H
#define LEXER_H

#include <vector>

#include "token.h"

//Ska vara recursive descent

class Lexer
{
public:
    Lexer(std::string str);    //Returns an iterator pointing to the first character of the string

    std::vector<Token> tokenize();

    static bool isIdentifier(char c);

private:
    char parseBraces();

    TokenType getTokenType();

    std::string str;
    std::string::iterator it;      //Returns an iterator pointing to the first character of the string
};

#endif


