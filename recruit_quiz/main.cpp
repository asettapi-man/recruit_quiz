#include "question.h"
#include "utility.h"
#include "exam_japanese.h"
#include "exam_english.h"
#include "exam_science.h"
#include "exam_geography.h"
#include "exam_politics.h"
#include "exam_mathematics.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>
using namespace std;

int main()
{
	//教科データ配列
	static const struct
	{
		const char* name;	//教科名
		QuestionList(*create)();	//問題作成関数
	}	subjectData[] = {
		{"数学", CreateMathematicsExam},
		{"国語", CreateJapaneseExam},
		{"英語", CreateEnglishExam},
		{"理科", CreatePhysicsExam},
		{"地理", CreatePrefecturesExam},
		{"政治", CreatePoliticsExam}
	};

	vector<Question> questions(3);

	cout << "[リクルート試験対策クイズ]\n";

	cout << "教科を選んでください\n";
	for (int i = 0; i < size(subjectData); i++)
	{
		cout << i + 1 << "=" << subjectData[i].name << "\n";
	}

	int subject;
	cin >> subject;
	if (subject > 0 && subject <= size(subjectData))
	{
		questions = subjectData[subject - 1].create();
	}

	for (const auto& e : questions)
	{
		cout << e.q << "\n";

		string answer;
		cin >> answer;

		// 変換が成功した場合はASCII文字列に置き換える
		string ascii = ConvertSjisNumberToAscii(answer);
		if (!ascii.empty())
		{
			answer = ascii;
		}

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