#include "exam_science.h"
#include "utility.h"
#include <random>
using namespace std;

/// <summary>
/// 物理の問題作成
/// </summary>
/// <returns>物理の問題が返る</returns>
QuestionList CreatePhysicsExam()
{
	QuestionList questions;
	questions.reserve(10);
	random_device rd;

	{	//等速直線運動
		constexpr int divisors[] = { 1, 2, 3, 4, 5, 6, 10, 12, 15, 20, 30, 60 };
		int i = uniform_int_distribution<>(0, size(divisors) - 1)(rd);
		int v = uniform_int_distribution<>(1, 10)(rd) * 60 / divisors[i];	//時速
		int t = uniform_int_distribution<>(1, 10)(rd) * divisors[i];		//時間
		questions.push_back({
			"時速" + to_string(v) + "kmで移動する車がある。\nこの車が" + to_string(v * t / 60) +
			"km移動するのにかかる時間を分単位で求めよ",
			to_string(t) });

		i = uniform_int_distribution<>(0, size(divisors) - 1)(rd);
		v = uniform_int_distribution<>(1, 10)(rd) * 60 / divisors[i]; // 速度
		t = uniform_int_distribution<>(1, 10)(rd) * divisors[i]; // 時間
		questions.push_back({
		"ある車が" + to_string(v * t / 60) + "km離れた地点まで移動するのに" + to_string(t) +
		"分かかった。\nこの車の平均時速を求めよ",
		to_string(v) });
	}	//等速直線運動

	{ // 等加速度直線運動
		// 公式: v = v0 + at を使って解く問題
		int v0 = uniform_int_distribution<>(1, 10)(rd); // 初速
		int a = uniform_int_distribution<>(1, 5)(rd);   // 加速度
		int t = uniform_int_distribution<>(1, 20)(rd);  // 移動時間
		questions.push_back({
		"秒速" + to_string(v0) + "kmで移動していた車が、進行方向に大きさ" + to_string(a) +
		"km/s^2で等加速度直線運動をはじめた。\n" + to_string(t) + "秒後の速度をm/s単位で求めよ。",
		to_string(v0 + a * t) });

		// 公式: x = v0t + 1/2*at^2 を使って解く問題
		v0 = uniform_int_distribution<>(5, 20)(rd);   // 初速
		a = uniform_int_distribution<>(1, 5)(rd) * 2; // 加速度
		t = uniform_int_distribution<>(1, 10)(rd);    // 移動時間
		questions.push_back({
		"秒速" + to_string(v0) + "で移動していた車が、進行方向に大きさ" + to_string(a) +
		"km/sで等加速度直線運動をはじめた。\n加速を始めてから" + to_string(t) +
		"秒後までに移動した距離をm単位で求めよ。",
		to_string(v0 * t + a * t * t / 2) });

		// 公式: v^2 - v0^2 = 2ax を使って解く問題
		a = -uniform_int_distribution<>(1, 5)(rd) * 2; // 加速度
		t = uniform_int_distribution<>(1, 10)(rd);     // 移動時間
		v0 = -a * t; // 初速
		questions.push_back({
		"秒速" + to_string(v0) + "mで移動していた車がブレーキをかけたところ、" +
		to_string(v0 * t + a * t * t / 2) + "m進んで停止した。\n" +
		"ブレーキの加速度をm/s^2単位で求めよ。",
		to_string(a) });
	}	//等加速度直線運動

	return questions;
}