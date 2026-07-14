#include "utility.h"
#include <random>
using namespace std;

/*
	配列をシャッフルする関数
*/
void Shuffle(std::vector<int>& indices)
{
	const int n = static_cast<int>(indices.size());

	random_device rd;
	mt19937 rand(rd());
	for (int i = n - 1; i > 0; i--) {
		const int j = uniform_int_distribution<>(0, i)(rand);
		const int tmp = indices[i];
		indices[i] = indices[j];
		indices[j] = tmp;
	}
}

/*
	ランダムな番号配列を作成する関数
*/
vector<int> CreateRandomIndices(int n)
{
	//番号を配列に格納
	vector<int> indices(n);
	for (int i = 0; i < n; i++){
		indices[i] = i;
	}

	//番号の配列をシャッフル
	Shuffle(indices);

	return indices;
}
/*
	間違った番号の配列を作成する関数
*/
std::vector<int> CreateWrongIndices(int n, int correctIndex)
{
	vector<int> indices(n - 1);
	for (int i = 0; i < correctIndex; i++) {
		indices[i] = i;
	}
	for (int i = correctIndex; i < n - 1; i++) {
		indices[i] = i + 1;
	}

	//番号の配列をシャッフル
	Shuffle(indices);

	return indices;
}

//文字列を分割する関数
vector<string> Split(const string& s, char c)
{
	vector<string> v;	//分割した文字列を格納配列（戻り値）

	//全ての文字列をループ処理
	auto begin = s.begin();	//分割範囲の先頭位置
	const auto end = s.end();	//文字列の終端
	for (auto p = begin; p != end; ++p)
	{
		//区切り文字の前までを文字列を分割
		if (*p == c)
		{
			v.push_back(string(begin, p));	//分割した文字列を配列に格納
			begin = p + 1;	//次の分割範囲の先頭位置を更新
		}
	}

	//残りの部分を配列に追加
	v.push_back(string(begin, end));

	return v;
}
