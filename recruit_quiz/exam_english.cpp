#include "exam_english.h"
#include "utility.h"
using namespace std;

/*
	英単語の問題作成
*/
QuestionList CreateEnglishWordExam()
{
	const struct {
		const char* word;	//英単語
		const char* reading;	//読み
		const char* meaning;	//意味
	} data[] = {
		{ "state", "ステート", "状態"},
		{ "business", "ビジネス", "事業、仕事"},
		{ "abstract", "アブストラクト", "抽象的な"},
		{ "concrete", "コンクリート", "具体的な"},
		{ "digital", "デジタル", "数字で情報を伝える"},
		{ "analogue", "アナログ", "類似している、類似物"},
		{ "exchange", "エクスチェンジ", "交換、両替、為替"},
		{ "infrastructure", "インフラストラクチャ", "下部構造、基盤となる施設や設備"},
		{ "knowledge", "ナレッジ", "知識"},
		{ "credit", "クレジット", "信用"},
	};

	constexpr int quizCount = 5;	//出題数
	QuestionList questions;
	questions.reserve(quizCount);	//問題の数だけメモリを確保しておく
	const vector<int> indices = CreateRandomIndices(size(data));	//問題の順番をランダムにするための番号配列
	
	for (int i = 0; i < quizCount; i++)
	{
		const auto& e = data[indices[i]];
		questions.push_back({
			"「" + string(e.meaning) + "」を意味する英単語を答えよ",
			e.word });
	}

	return questions;
}