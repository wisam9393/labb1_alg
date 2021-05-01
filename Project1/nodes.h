#ifndef NODES_H
#define NODES_H

#include "token.h"
#include <algorithm>
#include <vector>



/* Grammar:        <expr> =  <op> | <op><expr>
	<prgm> = <expr> |  <expr> <"/O{int}">
	<expr> = <sub_expr> | <ignor>
	<sub_expr> =  <or> |  <star>  |  <count>|  <value> | <group>
	<char> = [A-Z a-z]
	<or> = <char> + <char>
	<star> = <value><"*">
	<count> = <value><"{N}">        som  <count> =  <char><{N}> | <dot><{N}>
	<value> = <char> | <dot> |             <group>
	<group> = <(>  <or> <)>
	<ignor> = <group>  <"\I">


	3<expr> =  <op> | <op><expr> .m
*/

// efter abo
//

using iterator = std::string::iterator&;
 

static std::string match;


struct ASTNode {
	bool virtual evaluate(iterator begin, iterator end) {
		return operands[0]->evaluate(begin, end);    //
		
	};
	std::string virtual print() { return " "; };
	std::vector<ASTNode*> operands;
};

//std::vector<std::string> evaluate_root(ASTNode* root, std::string txtt);


struct prgm :ASTNode {
	bool evaluate(iterator begin, iterator end) override {
		
		while (begin != end)
		{
			if (operands[0]->evaluate(begin, end) == true)
			{
				std::cout << match << "\n\n";
				return true;
			}
			begin++;
		}

		return false;
	};

};
//expr 111

struct exnode :ASTNode {
	bool evaluate(iterator begin, iterator end) override {
		return operands[0]->evaluate(begin, end);
	};

};

struct exprnode :ASTNode {
	bool evaluate(iterator begin, iterator end) override {
		return operands[0]->evaluate(begin, end);
	};

};
//sub_expr
struct sub_exprnod :ASTNode {
	bool evaluate(iterator begin, iterator end) override {
		return operands[0]->evaluate(begin, end);
	};

};
/// <summary>
/// 
/// </summary>
/// 
struct stringnode :ASTNode {
	std::string stav;
	stringnode(std::string stav) :stav(stav) {};
	bool evaluate(iterator begin, iterator end) override {

		if (begin == end)
		{
			return false;
		}
		
		for (int i = 0; i < operands.size(); i++)
		{
			if (operands[i]->evaluate(begin, end) == false)
			{
				begin -= i;
				match.clear();
				return false;
			}
			
		}
		return true;
	};

	std::string print() override {
		return stav;
	}
};

struct charnode :ASTNode {
	char ch;
	charnode(char ch):ch(ch) {};
	bool evaluate(iterator begin, iterator end) override {
		if (begin!=end && *begin == ch)    //          fixa om man skriver stor nummer i count
		{
			match += ch;
			begin++;
			return true;
		}
		return false;
	};
	std::string print() override {
		std::string stav (1,ch);
		return stav;
	}
	
};

//
struct ornode :ASTNode {
	ornode(ASTNode* child1, ASTNode* child2) {
		operands.push_back(child1);
		operands.push_back(child2);



	};

	bool evaluate(iterator begin, iterator end) override {
		
		if (operands[0]->evaluate(begin, end))
		{
			
			return true;
		}
		else if(operands[1]->evaluate(begin, end))
		{
			return true;
		}

		return false;
	};

};


struct starnode :ASTNode {
	bool evaluate(iterator begin, iterator end) override {
		if (operands[0]->evaluate(begin, end) == false)
		{
			return false;
		}
		while (operands[0]->operands.back()->evaluate(begin, end)){}
		return true;
	};
};

struct dotnode :ASTNode {
	bool evaluate(iterator begin, iterator end) override {
		return false;
	};

};



struct countnode :ASTNode {
	std::string nr;
	countnode(std::string nr) :nr(nr) {};

	int antal = std::stoi(nr);

	bool evaluate(iterator begin, iterator end) override {
		if (operands[0]->evaluate(begin, end) == false)
		{
			return false;
		}
		for (int i = 0; i < antal; i++) {
			if(operands[0]->operands.back()->evaluate(begin, end) == false)
			
				return false;
		}
		return true;

	
	};
	std::string print() override {
		return nr;
	}

};



struct ignornode :ASTNode {
	bool evaluate(iterator begin, iterator end) override {
		return false;
	};

};

struct groupnode :ASTNode {
	//groupnode(ASTNode* child1) {
	//	operands.push_back(child1);
	//};

	bool evaluate(iterator begin, iterator end) override {
		if (operands[0]->evaluate(begin, end))
		{
			return true;
		}
		return false;
	};
	

};

struct valuenode :ASTNode {
	//groupnode(ASTNode* child1) {
	//	operands.push_back(child1);
	//};

	bool evaluate(iterator begin, iterator end) override {
		if (operands[0]->evaluate(begin, end))
		{
			return true;
		}
		return false;
	};


};



struct outnode :ASTNode {
	bool evaluate(iterator begin, iterator end) override {
		return false;
	};

};
/*
* 
*/

/*

struct charnode :ASTNode {
	void evaluate() override {
	};

};
  */
#endif 