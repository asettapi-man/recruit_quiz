#include "exam_geography.h"
#include "utility.h"
#include <iostream>
#include <fstream>
#include <random>
using namespace std;

QuestionList CreatePrefecturesExam()
{
	struct PrefectureData
	{
		string name;
		string capital;
		vector<string> features;
	};
	vector<PrefectureData> data;

	{	// 都道府県データを読み込む
		constexpr char filename[] = "japanese_prefectures.txt";
		ifstream ifs(filename);
		if (!ifs)
		{
			//エラーメッセージ
			cerr << "エラー:" << filename << "を読み込めません\n";
			return {};
		}

		string s;
		while (true)
		{
			getline(ifs, s);
			if (!ifs)
			{
				break;	//ファイル終端に達したので終了
			}
			const vector<string> v = Split(s, ',');
			data.push_back({ v[0], v[1], vector<string>(v.begin() + 2, v.end()) });
		}
	}	// 都道府県データを読み込む

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	vector<int> indices = CreateRandomIndices((int)data.size());
	random_device rd;

	const int type = uniform_int_distribution<>(0, 2)(rd);
	switch (type)
	{
	case 0:	//特徴から都道府県を答える
		for (int i = 0; i < quizCount; i++)
		{
			//正解遺体の答えをランダムに選ぶ
			const int correctIndex = indices[i];
			vector<int> answers = CreateWrongIndices((int)data.size(), correctIndex);

			//ランダムな位置を正しい番号で上書き
			const int correctNo = uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			//問題文を作成
			string s = "以下の特徴を持つ都道府県の番号を選べ\n";

			//都道府県の特徴をランダムな順番で連結し、問題文に追加
			const auto& features = data[correctIndex].features;
			vector<int> featureIndices = CreateRandomIndices((int)features.size());
			s += features[featureIndices[0]];
			for (int j = 1; j < features.size(); j++)
			{
				s += ", ";
				s += features[featureIndices[j]];
			}

			//答えとなる都道府県を問題文に追加
			for (int j = 0; j < 3; j++)
			{
				s += "\n " + to_string(j + 1) + ":" + data[answers[j]].name;
			}

			// 問題文と答えのペアを問題配列に追加
			questions.push_back({ s, to_string(correctNo) });
		}
		break;

	case 1:	//都道府県をあらわす特徴を答える
		break;

	case 2:	//都道府県から県庁所在地を答える
		break;
	}	// switch (type)

	return questions;
}
