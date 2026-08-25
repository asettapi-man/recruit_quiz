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
#include <fstream>
#include <time.h>
using namespace std;

int main()
{
	//教科データ配列
	static const struct
	{
		const char* name;	//教科名
		QuestionList(*create)();	//問題作成関数
	} subjectData[] = {
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

	vector<int> questionCounts(size(subjectData));	//各教科の問題数
	int subject;
	cin >> subject;
	if (subject > 0 && subject <= size(subjectData))
	{
		questions = subjectData[subject - 1].create();
	}
	else if (subject == 0)
	{
		//総合テスト
		questions.clear();
		for (int i = 0; i < size(subjectData); i++)
		{
			const QuestionList tmp = subjectData[i].create();
			questions.insert(questions.end(), tmp.begin(), tmp.end());
			questionCounts[i] = (int)tmp.size();
		}
	}

	vector<int> correctCounts(size(subjectData));	//各教科の正解数
	int currentSubjectNo = 0;	//出題中の教科番号
	int currentAnsweredCount = 0;	//回答済みの問題数

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
			correctCounts[currentSubjectNo]++;
		}
		else
		{
			cout << "間違い！正解は" << e.a << "\n";
		}

		//回答済み問題数が教科の問題数以上になったら、次の教科に進む
		if (subject == 0)
		{
			currentAnsweredCount++;	//回答済み問題数をカウント
			if (currentAnsweredCount >= questionCounts[currentSubjectNo])
			{
				currentSubjectNo++;	//次の教科に進む
				currentAnsweredCount = 0;	//回答済み問題数をリセット
			}
		}
	}	//for questions <- for文の閉じカッコを分かりやすくするためのもの

	//成績を表示
	cout << "\n- - - 成績 - - -\n";
	if (subject > 0 && subject <= size(subjectData))
	{
		cout << subjectData[subject - 1].name << "：" << correctCounts[0] << "/" << questions.size() << "\n";
	}
	else if (subject == 0)
	{
		size_t totalCorrect = 0;	//総合正解数
		for (int i = 0; i < size(subjectData); i++)
		{
			cout << subjectData[i].name << "：" << correctCounts[i] << "/" << questionCounts[i] << "\n";
			totalCorrect += correctCounts[i];
		}
		cout << "合計 : " << totalCorrect << "/" << questions.size() << "\n";
	}

	//成績をファイルに出力する
	static const char filename[] = "リクルート対策試験成績表.txt";
	ofstream ofs(filename, ios_base::app);
	if (!ofs)
	{
		cerr << "エラー: " << filename << "を開けません\n";
	}
	else
	{
		//現在の時刻（協定世界時）を取得
		const time_t t = time(nullptr);

		//協定世界時を時間構造体型に変換
		tm examDate;
		localtime_s(&examDate, &t);

		//時間構造体を文字列に変換
		char strDate[100];
		strftime(strDate, size(strDate), "%Y/%m/%d(%a) %T", &examDate);

		if (subject > 0 && subject <= size(subjectData))
		{
			//教科テストの場合、試験した教科の成績だけを出力し、それ以外は空欄とする
			ofs << strDate;
			for (int i = 0; i < size(subjectData); i++)
			{
				ofs << ",";
				if (i == subject - 1)
				{
					ofs << correctCounts[0] << '/' << questions.size();
				}
			}
			ofs << "\n";
			cout << "成績を" << filename << "に出力しました\n";
		}
		else if (subject == 0)
		{
			//総合テストの場合、全教科の成績を出力する
			ofs << strDate;
			for (int i = 0; i < size(subjectData); i++)
			{
				ofs << "," << correctCounts[i] << '/' << questionCounts[i];
			}
			ofs << "\n";
			cout << "成績を" << filename << "に出力しました\n";
		}

	}	//if !ofs
}