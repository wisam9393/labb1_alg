#include "nodes.h"
#include <vector>
/*
std::string::iterator txt_begin;
std::string::iterator txt_end;

std::string::iterator begin;
std::string::iterator end;

std::vector<std::string> evaluate_root(ASTNode* root, std::string txtt)
{
	txt_begin = txtt.begin();
	txt_end = txtt.end();

	begin = txtt.begin();
	end = txtt.begin();



	std::vector<std::string> matches;
	root->evaluate();
	if (begin != txt_end)
	{
		matches.push_back(std::string(begin, end));
	}

	return matches;
}

void charnode::evaluate()
{
	while (begin != txt_end)
	{
		if (*begin == stav.front())
		{

			auto it = begin+1;  // main
			auto it2 = stav.begin()+1;   // string  till char
			while (it2 !=stav.end() && it != txt_end &&*it == *it2  )
			{


				it++;
				it2++;
			}
			if (it2 == stav.end() )
			{
				end = it;
				return;
			}
			else
			{
				begin = it;
				end = it;
			}
		}

		begin++;
		end++;
	}

}
*/