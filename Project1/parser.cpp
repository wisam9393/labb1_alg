
#include "parser.h"
#include "lexer.h"

// hat kommenterat bort curent++; i rad 86
// add more chek t.ex rad 160+ 246 to cheak size 
/*if (curent >= tokens.size())
	{
	return nullptr;
	}
*/

parser::parser(std::vector<Token> tokens):tokens(tokens)
{
}

//<prgm>
ASTNode* parser::parse() {
	std::cout << "prgmnod" << std::endl;
	prgm* nod = new prgm();
	
	auto out_nod1 = parseout();
	if (out_nod1 != nullptr)
	{
		nod->operands.push_back(out_nod1);
		return nod;
		
	}
	//exprnode* child = parseexpr();   // innan 
	auto  child = parseex(); //exnode* till auto,  byta  parseexpr till parseex och exprnode
	if (child == nullptr)
		return nullptr;
	else
	{
		nod->operands.push_back(child);
	}
	return nod;
}

exnode* parser::parseex()
{
	exnode* exNode = new exnode();

	auto child = parseexpr();
	
	if (child == nullptr)
		return nullptr;
	else
	{
		exNode->operands.push_back(child);

	}
	
	//curent++;
	//curent++;

	auto child2 = parseex();

	if (child2 == nullptr)
		return exNode;
	else
	{
		exNode->operands.push_back(child2);
	}
	
	return exNode;


}

/*


*/
 
/// <expr>
exprnode* parser::parseexpr()
{
	exprnode* exprNode = new exprnode();
	
	auto group_nod1 = parseignor();
	if (group_nod1 != nullptr)
	{
		exprNode->operands.push_back(group_nod1);
		return exprNode;
	}

	sub_exprnod* child = sub_expr();
	if (child == nullptr)
		return nullptr;

	//curent++;
	
	exprNode->operands.push_back(child);
	return exprNode;

}


sub_exprnod* parser::sub_expr()
{

	std::cout << "exprnod" << std::endl;
	sub_exprnod* sub_exprNod = new sub_exprnod();
 	
		auto group_nod1 = parsegroup();
		if (group_nod1 != nullptr)
		{
			//expr_nod->operands.push_back(group_nod1); //
			sub_exprNod->operands.push_back(group_nod1);
			return sub_exprNod;
		}
		

		auto value_nod= parsevalue();  //to get if it char eller dot
		// if ska kolla om det Or eller Star
		//om det Or
		auto or_nod1 = parseor(value_nod);
		if (or_nod1 != nullptr)
		{
			//expr_nod->operands.push_back(group_nod1); //
			sub_exprNod->operands.push_back(or_nod1);
			return sub_exprNod;
		}
		//om det Star
		auto star_nod1 = parsestar(value_nod);
		if (star_nod1 != nullptr)
		{
			//expr_nod->operands.push_back(group_nod1); //
			sub_exprNod->operands.push_back(star_nod1);
			return sub_exprNod;
		}
		//om det Count
		auto count_nod1 = parsecount(value_nod);
		if (count_nod1 != nullptr)
		{
			sub_exprNod->operands.push_back(count_nod1);
			return sub_exprNod;
		}


		/*
		if (group_nod1 == nullptr)
			return nullptr;
		*/
		if (value_nod == nullptr)
			return nullptr;
		else
		{
			sub_exprNod->operands.push_back(value_nod);
			return sub_exprNod;
		}
	//}
}

stringnode* parser::parsestring()
{
	std::cout << "charnode" << std::endl;

	stringnode* nod = new stringnode(" ");
	std::string ord;

	if (curent >= tokens.size())
	{
		return nullptr;
	}

	if (tokens[curent].type != TokenType::CHAR)
		return nullptr;
	
	while (tokens[curent].type == TokenType::CHAR) {
		auto charnod  = new charnode(tokens[curent].value);
		nod->operands.push_back(charnod);
		curent++;
	}
	
	 
	return nod;
}


ornode* parser::parseor(ASTNode* child1)
{
	std::cout << "parseor" << std::endl;
	
	if (child1 == nullptr)
		return nullptr;
	
	// nu 2021-05-01
	//starnode* Str = parsestar(child1);
	//if (!Str)    return nullptr;



	if (tokens[curent].type != TokenType::OR)
		return nullptr;

	curent++;
	auto child2 = parsestring();
	if (child2 == nullptr)
		return nullptr;

	ornode* nod = new ornode(child1, child2);


	//nu
	//nod->operands.push_back(Str);
	// 
	// 
	//nod->operands.push_back(child1);
	return nod;
}


starnode* parser::parsestar(ASTNode* child1)
{
	std::cout << "parsestar" << std::endl;

	if (child1 == nullptr)
		return nullptr;

	/*
	if (child1 == nullptr &&
		tokens[curent].type == TokenType::DOT)
	{
		curent++;
		auto dot_nod = new dotnode();

		if (dot_nod != nullptr)
		{
			expr_nod->operands.push_back(dot_nod);
			return expr_nod;
		}
		return nullptr;
	}
	*/

	if (tokens[curent].type != TokenType::STAR)
		return nullptr;

	curent++;

	starnode* nod = new starnode();

	nod->operands.push_back(child1);
	return nod;
}

dotnode* parser::parsedot()
{
	std::cout << "parsedot" << std::endl;
	if (curent >= tokens.size())
	{
		return nullptr;
	}
	if (tokens[curent].type != TokenType::DOT)
		return nullptr;

	curent++;

	dotnode* dotNode = new dotnode();
	return dotNode;
}



ASTNode* parser::parsevalue()
{
	auto ch_n = parsestring();
	if (ch_n == nullptr)
	{
		auto dot_nod = parsedot();
		if (dot_nod == nullptr)
		{
			
			return nullptr;
	
		}
		return dot_nod;
	}
	return ch_n;
}
//

/*
valuenode* parser::parsevalue()
{
	valuenode* nod = new valuenode();
	if (tokens[curent].type == TokenType::CHAR)
	{
		auto ch_n = parsestring();
		nod->operands.push_back(ch_n);
		curent++;
		return nod;
	}
	if (tokens[curent].type == TokenType::DOT)
	{
		auto ch_n = parsedot();
		nod->operands.push_back(ch_n);
		curent++;
		return nod;
	}
	 
}
*/

/*
if (child1->operands.size() == 0) // kolla att barn ar string, om det dot
	{
		nod->operands.push_back(child1);
		return nod;
	}

*/
ASTNode* parser::parsecount(ASTNode* child1)
{
	std::string nr;
	std::cout << "parsecount" << std::endl;
	if (child1 == nullptr)
		return nullptr;

	if (tokens[curent].type != TokenType::COUNTER)
		return nullptr;

	nr = tokens[curent].value;

	std::cout << "parsecount  value" << nr << std::endl;

	countnode* nod = new countnode(nr);
	nod->operands.push_back(child1);
	return nod;
}

groupnode* parser::parsegroup()
{
	std::cout << "parsegroup" << std::endl;
	if (curent >= tokens.size())
	{
		return nullptr;
	}
	if (tokens[curent].type != TokenType::LEFT_PAREN)
		return nullptr;
	curent++;

	auto value_nod = parsevalue();
	if (value_nod == nullptr)
		return nullptr;

	/*
	auto pars_char = parsechar();
	if (pars_char == nullptr)
		return nullptr;
		*/

	auto or_nod1 = parseor(value_nod);
	if (or_nod1 == nullptr)
		return nullptr;
 
	if (tokens[curent].type != TokenType::RIGHT_PAREN)
		return nullptr;

	curent++;

	groupnode* groupNode = new groupnode();
	groupNode->operands.push_back(or_nod1);
	return groupNode;
}




ignornode* parser::parseignor()
{
	int mow_curent = curent;
	auto group_nod1 = parsegroup();
	if (group_nod1 == nullptr)
	{
		curent = mow_curent;
		return nullptr;
	}

	std::cout << "parseignor" << std::endl;
	if (tokens[curent].type != TokenType::IGNORE_CAPS) {

		curent = mow_curent;
		return nullptr;
	}
		
	curent++;

	ignornode* ignorNode = new ignornode();
	ignorNode->operands.push_back(group_nod1);
	return ignorNode;

}

outnode* parser::parseout()
{
	/*
	//mow_curent= curent;
	auto value_nod = parsegroup();
	if (value_nod == nullptr)
	{
		//curent = mow_curent;
		return nullptr;
	}
	
	std::cout << "parseignor" << std::endl;
	if (tokens[curent].type != TokenType::OUTPUT_GROUP) {

		//curent = mow_curent;
		return nullptr;
	}
	*/
	int mow_curent = curent;
	auto value_nod = parsegroup();
	if (value_nod == nullptr)
	{
		curent = mow_curent;
		return nullptr;
	}

	std::cout << "parseignor" << std::endl;
	if (tokens[curent].type != TokenType::OUTPUT_GROUP) {

		curent = mow_curent;
		return nullptr;
	}

	curent++;

	outnode* outNode = new outnode();
	outNode->operands.push_back(value_nod);
	return outNode;
}



/*
leftnode* parser::parseleft()
{


	return nullptr;
}
*/




/*
std::cout << "charnode" << std::endl;

	charnode* nod;
	std::string ord;

	if (tokens[curent].type != TokenType::CHAR)
		return nullptr;

	while (tokens[curent].type == TokenType::CHAR) {
		ord += tokens[curent].value;
		curent++;
	}
	nod = new charnode(ord);

	return nod;
	*/