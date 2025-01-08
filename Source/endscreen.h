#pragma once
#include "raylib.h"
#include <string>
#include <vector>

struct PlayerData
{
	std::string name;
	int score;
};

class EndScreen
{
public:
	char name[9 + 1] = "\0";      //One extra space required for null terminator char '\0'
	int finalScore = 0;
	int letterCount = 0;
	int framesCounter = 0;
	bool mouseOnText = false;
	bool newHighScore = false;
	Rectangle textBox = { 600, 500, 225, 50 };
	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };

	bool CheckNewHighScore();
	void InsertNewHighScore(std::string name);

	void update();
	void render();
};