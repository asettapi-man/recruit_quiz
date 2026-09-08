#pragma once

#include <string>
#include <vector>

struct Question
{
	std::string q;	//–â‘è•¶
	std::string a;		//“š‚¦
	std::vector<std::string> b; // “š‚¦(•¡”‚ ‚éê‡)
};

using QuestionList = std::vector<Question>;