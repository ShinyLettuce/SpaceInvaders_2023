#pragma once
#include "raylib.h"
#include <string>
#include <vector>
#include <array>

struct PlayerData
{
	std::string name;
	int score = 0;
};

class EndScreen
{
	std::array<char,10> name;
	int finalScore = 0;
	int letterCount = 0;
	int framesCounter = 0;
	int maxLetterCount = 9;
	bool mouseOnText = false;
	bool isNewHighScore = false;
	Rectangle textBox = { 600, 500, 225, 50 };
	float outlineWidth = 1.f;
	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };

	void InsertNewHighScore(std::string_view newName);
	void addInputCharacter() noexcept;
	void deleteCharacter() noexcept;
	void drawLeaderboard() noexcept;
	void updateTextBox() noexcept;
	void drawTextBox() const noexcept;
public:

	bool getIsNewHighScore() const noexcept { return isNewHighScore;  };
	void setFinalScore(int score) noexcept { finalScore = score; };
	void setIsNewHighScore(bool newRecord) noexcept { isNewHighScore = newRecord; };

	bool CheckNewHighScore() noexcept;
	void update();
	void render() noexcept;

};