
#include <iostream>
#include <string>
#include <vector>

#include "token.h"
#include "lexer.h"
//#include "nodes.h"
#include "parser.h"

void printTree(ASTNode* p, int i) {
    if (!p)
        return;
    std::cout << "<" << typeid(*p).name() << " " << p->print() << ">\n";
    i++;
    for (ASTNode* child : p->operands) {
        for (int j = 0; j != i; j++)
            std::cout << '\t';
        printTree(child, i);
    }
}

int main()
{
    std::string txt = "Waterloooo I was defeated, you won the war Waterloooo promise to love you for ever more Waterloo couldn't escape if I wanted to Waterloo knowing my fate is to be with you Waterloo finally facing my Waterloo";

    std::string line;

    std::cout << "\n";

    while (std::getline(std::cin, line))
    {
        if (line == "exit") return 0;       //w  controll that someting come in  

        Lexer lexer(line);                 //w  constructor retunera first pointer till first input string, lexer is a obj from Lexer, return  first place , this->str.begin()

        std::vector<Token> tokens = lexer.tokenize();           // w  lexer.tokenize() return tokens vector;  create a vector tokens av typ lexer.tokenize()

        //std::cout << "\nTokens: ";
        for(auto token: tokens)  token.print();
        std::cout << "\n\n";

        parser par(tokens);
        auto root = par.parse();
        printTree(root, 0);
        if (root == nullptr)
        {
            std::cout << "root == nullptr" << std::endl;
        }
        else
        {
            
            std::string::iterator begin = txt.begin();
            std::string::iterator end = txt.end();
           
            root->evaluate(begin, end);
            //std::cout << match << "\n\n";

            //std::cout << "root != nullptr" << std::endl;
           /*
            std::vector<std::string> matches = evaluate_root(root, txt);
            for (auto matches1 : matches)
            {
                std::cout << matches1;
                std::cout << "\n\n";
            }
            */
            std::cout << "\n\n";
        }

            //root->print();

        
    }


    /*
    PrgmNode* root = Parser::buildTree(tokens.begin(), tokens.end());

    if (!root) std::cout << "Failed to build tree\n";
    else
    {
        //root->print();

        std::vector<std::string> matches = root->eval(txt.begin(), txt.end());

        if (!matches.empty())
        {
            int group_index = 0;

            Token lastToken = tokens.back();

            if (lastToken.type == TokenType::OUTPUT_GROUP)
                group_index = lastToken.value - '0';

            std::cout << "MATCH: " << matches[group_index] << "\n";
        }
        else    std::cout << "Coudln't find regexp\n";

        std::cout << "\n";
    }
    */

    return 0;
}

