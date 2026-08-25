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
	vector<Question> questions(3);

	cout << "[リクルート試験対策クイズ]\n";

	cout << "今日かを選んでください\n１=数学\n２=国語\n３=英語\n４=理科\n５=地理\n６=政治\n";
	int subject;
	cin >> subject;
	if (subject == 1) {
		questions = CreateMathematicsExam();
	}
	else if (subject == 2) {
		questions = CreateKanjiExam();
		QuestionList idioExam = CreateIdiomExam();
		questions.insert(questions.end(), idioExam.begin(), idioExam.end());
		QuestionList homophoneExam = CreateHomophoneExam();
		questions.insert(questions.end(), homophoneExam.begin(), homophoneExam.end());
		QuestionList antonyExam = CreateAntonyExam();
		questions.insert(questions.end(), antonyExam.begin(), antonyExam.end());
		QuestionList synonymExam = CreateSynonymExam();
		questions.insert(questions.end(), synonymExam.begin(), synonymExam.end());
	}
	else if (subject == 3) {
		questions = CreateEnglishWordExam();
		QuestionList phraseExam = CreateEnglishPhraseExam();
		questions.insert(questions.end(), phraseExam.begin(), phraseExam.end());
	}
	else if (subject == 4)
	{
		questions = CreatePhysicsExam();
	}
	else if (subject == 5)
	{
		questions = CreatePrefecturesExam();
	}
	else if (subject == 6)
	{
		questions = CreatePoliticsExam();
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