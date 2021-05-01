
#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include "nodes.h"
#include "token.h"

/* Grammar:        

	<prgm> = <ex> |  <ex> <"/O{int}"> 
	<ex> =  <expr> | <expr><ex>  
	<expr> = <sub_expr> | <ignor> 
	<sub_expr> =  <or> |  <star>  | 
	              <count>|  <value> | <group>
	<char> = [A-Z a-z]
	<or> = <char> + <char>
	<star> = <value><"*">
	<count> = <value><"{N}">        som  <count> =  <char><{N}> | <dot><{N}>
	<value> = <char> | <dot> |						        
	<group> = <(>  <or> <)> 
	<ignor> = <group>  <"\I">       
	     	
*/
/*
	<prgm> = <expr>
	<expr> = <value> | <value><expr> 
	<value> = <char>  | <dot>  |
	<char> = [A-Z a-z] |  <char><or> |  <char><"*">
	<dot> = <".">    |  <"."><star>    |
	<or> = <char> + <char>

*/


class parser {
private:
	std::vector<Token> tokens;
	int curent = 0;
public:
	parser(std::vector<Token> tokens);
	ASTNode* parse();
	exnode* parseex();
	exprnode* parseexpr(); //  ny
	sub_exprnod* sub_expr();
	stringnode* parsestring();
	ornode* parseor(ASTNode* child1);
	starnode* parsestar(ASTNode* child1);
	dotnode* parsedot();
	valuenode* parsevalue();
	ASTNode* parsecount(ASTNode* child1);   // ska de vara countnode eller ASTNode??
	groupnode* parsegroup(); // ska de vara groupnode eller ASTNode??
	ignornode* parseignor();
	outnode* parseout();
}; 


#endif

/////


/*
<program> -> <output>
<output> -> <expr>|<expr>/O{int}
<expr> -> <match>| <match><expr>
<match> -> <ignore>|<group>|<or>|<str>
<ignore> -> <group>/I
<or> -> <str> + <str>
<count> -> <char>{<int>}
<str> -> <char>|<char><str>|<str><star>|<str><count>
<star> -> <char>*
<count> -> <char>{int}
<int> -> [0-9]|[0-9]<int>
<char> -> [A-Z]|[A-Z]<char>|<any><char>
<any> -> .
<ignore> -> /I
*/
