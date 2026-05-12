#include "utility.h"
#include <random>
using namespace std;

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
	random_device rd;
	mt19937 rand(rd());
	for (int i = n - 1; i > 0; i--) {
		const int j = uniform_int_distribution<>(0, i)(rand);
		const int tmp = indices[i];
		indices[i] = indices[j];
		indices[j] = tmp;
	}

	return indices;
}