#include <iostream>
#include <string>
using namespace std;

struct Question
{
	string q;	//問題文
	int a;		//答え
};

int main()
{
	Question question[] =
	{
		{"13 * (-5)", 13 * -5 },
		{"(-21) / (-3)", -21 / -3 },
		{"7 - (4 + 2) / 2", 7 - (4 + 2) / 2}
	};

	cout << "[リクルート試験対策クイズ]\n";

	for (const auto& e : question)
	{
		cout << e.q << "の答えは？\n";

		int answer;
		cin >> answer;

		if (answer == e.a)
		{
			cout << "正解！\n";
		}
		else
		{
			cout << "間違い！正解は" << e.a << "\n";
		}
	}	//for questions <- for文の閉じカッコを分かりやすくするためのもの
}