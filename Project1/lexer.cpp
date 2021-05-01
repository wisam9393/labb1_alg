
#include "lexer.h"

#include <stdexcept>

//Returns an iterator pointing to the first character of the string
Lexer::Lexer(std::string str) :
	str(str)
{
	it = this->str.begin();  //ww this->str.begin();   ge den first string i listan
}

std::vector<Token> Lexer::tokenize()
{
	std::vector<Token> tokens;

	while (it != str.end())																	 // iterera genom hela texten 
	{
		Token token = Token(getTokenType());																			   // if  getSymbolType is CHAR so it go to token.h and give type(type) type=CHAR, so it constructor

		switch (token.type)   																			  // token.type = token.CHAR,,    type is from token.h   is  CHAR  OR  STAR  LEFT_PAREN
		{																										//  jhdhh hafdb + dfbfdb +dfb () dfb.//  *it= H, *it++= i 
		case TokenType::CHAR:           token.value = *it++;
			break;
		case TokenType::OUTPUT_GROUP:   it++;
		case TokenType::COUNTER:        token.value = parseBraces();
			break;

		default:                        it++;
		}

		tokens.push_back(token);   ////  ?????????????
	}
	std::cout << "Size : " << tokens.size();

	//for (auto it = tokens.begin(); it != tokens.end(); it++)
	//	std::cout << *it << " ";
	return tokens;
}

bool Lexer::isIdentifier(char c)
{
	return  (isalpha(c) || isdigit(c) || c == ' ' || c == '\'');
}

char Lexer::parseBraces()
{
	if (*it != '{')  throw std::runtime_error("ERROR: Expected { sign.");

	if (!std::isdigit(*++it)) throw std::runtime_error("ERROR: Found non integer as counter value");

	char value = *it++;

	if (*it++ != '}') throw std::runtime_error("ERROR: Found no closing counter brace");

	return value;
}

TokenType Lexer::getTokenType()
{
	char token_c = *it;							// put the first element from string input till token_c
	//std::cout << *it << "\n";
	//std::cout << &it << "\n";
	//std::cout << &it << "\n";


	if (isIdentifier(token_c))  return TokenType::CHAR;

	switch (token_c)                     //w TokenType  difenera sympoler nar de kommer in
	{
	case '+':   return TokenType::OR;
	case '*':   return TokenType::STAR;
	case '(':   return TokenType::LEFT_PAREN;
	case ')':   return TokenType::RIGHT_PAREN;
	case '.':   return TokenType::DOT;
	case '{':   return TokenType::COUNTER;
	case '\\':
	{
		token_c = *++it;
		if (token_c == 'I') return TokenType::IGNORE_CAPS;
		if (token_c == 'O') return TokenType::OUTPUT_GROUP;
	}

	default: throw std::runtime_error("Error: Unknown identifier");
	}
}

