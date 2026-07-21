#pragma once
#include <vector>
#include <string>

//配列をシャッフルする関数
void Shuffle(std::vector<int>& indices);

//シャッフルした番号配列を作成する関数
std::vector<int> CreateRandomIndices(int n);

//間違った番号の配列を作成する関数
//n				作成する番号の範囲
//correctIndex	正解の番号
std::vector<int> CreateWrongIndices(int n, int correctIndex);

/// <summary>
/// 文字列を分解する関数
/// </summary>
/// <param name="s">分解する文字列</param>
/// <param name="c">区切り文字</param>
/// <returns>文字列が分割されたものが返る</returns>
std::vector<std::string> Split(const std::string& s, char c);

/// <summary>
/// SJIS数値文字列をASCII数値文字列に変換する
/// </summary>
/// <param name="sjis">変換元のsjis文字列</param>
/// <returns>SJIS数値文字列をASCII数値文字列に変換されたものが返る</returns>
std::string ConvertSjisNumberToAscii(const std::string& sjis);
