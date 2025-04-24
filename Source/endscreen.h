#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include <string>
#include <vector>
#include <array>
#include "constants.h"
#pragma warning(push)
#pragma warning(disable: 26446) //gsl::at() warning

struct PlayerData
{
	std::string name;
	int score = 0;
};

class EndScreen
{
	std::string name;
	int finalScore = 0;
	int framesCounter = 0;
	bool mouseOnText = false;
	bool isNewHighScore = false;
	float outlineWidth = 1.f;
	Rectangle textBox = { 600, 500, 225, 50 };
	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };

	void InsertNewHighScore(std::string_view newName);
	void addInputCharacter() noexcept;
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