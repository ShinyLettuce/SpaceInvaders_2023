#include "endscreen.h"

void EndScreen::InsertNewHighScore(std::string_view newName)
{
	PlayerData newData;
	newData.name = newName.data();
	newData.score = finalScore;

	for (int i = 0; i < Leaderboard.size(); i++)
	{
		if (newData.score > Leaderboard[i].score)
		{
			Leaderboard.insert(Leaderboard.begin() + i, newData);
			Leaderboard.pop_back();
			break;
		}
	}
}

bool EndScreen::CheckNewHighScore() noexcept
{
	return (finalScore > Leaderboard[4].score);
}

void EndScreen::update()
{
	if (!isNewHighScore)
	{
		return;
	}

	if (letterCount > 0 && letterCount < maxLetterCount && IsKeyReleased(KEY_ENTER))
	{
		const std::string_view nameEntry(name);
		InsertNewHighScore(nameEntry);
		isNewHighScore = false;
	}

	mouseOnText = CheckCollisionPointRec(GetMousePosition(), textBox);
	updateTextBox();
}

void EndScreen::render() noexcept
{
	if (!isNewHighScore)
	{
		DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);
		drawLeaderboard();
		return;
	}

	DrawText("NEW HIGHSCORE!", 600, 300, 60, YELLOW);
	DrawText("PLACE MOUSE OVER INPUT BOX!", 600, 400, 20, YELLOW);

	drawTextBox();
}

void EndScreen::updateTextBox() noexcept
{
	if (!mouseOnText)
	{
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		framesCounter = 0;
		return;
	}

	SetMouseCursor(MOUSE_CURSOR_IBEAM);
	addInputCharacter();

	if (IsKeyPressed(KEY_BACKSPACE))
	{
		deleteCharacter();
	}
	framesCounter++;
}

void EndScreen::addInputCharacter() noexcept
{
	int key = GetCharPressed();
	while (key > 0)
	{
		if ((key >= 32) && (key <= 125) && (letterCount < maxLetterCount))
		{
			name[letterCount] = static_cast<char>(key);
			letterCount++;
		}
		key = GetCharPressed();
	}
}

void EndScreen::deleteCharacter() noexcept
{
	letterCount--;
	if (letterCount < 0)
	{
		letterCount = 0;
	}
	name[letterCount] = '\0';
}

void EndScreen::drawLeaderboard() noexcept
{
	DrawText("LEADERBOARD", 50, 100, 40, YELLOW);

	for (int i = 0; i < Leaderboard.size(); i++)
	{
		std::string tempNameDisplay = Leaderboard[i].name;
		DrawText(tempNameDisplay.data(), 50, 140 + (i * 40), 40, YELLOW);
		DrawText(TextFormat("%i", Leaderboard[i].score), 350, 140 + (i * 40), 40, YELLOW);
	}
}

void EndScreen::drawTextBox() const noexcept
{
	DrawRectangleRec(textBox, LIGHTGRAY);
	DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, 600, 20, YELLOW);
	DrawText(name.data(), static_cast<int>(textBox.x) + 5, static_cast<int>(textBox.y) + 8, 40, MAROON);

	if (letterCount > 0 && letterCount < maxLetterCount)
	{
		DrawText("PRESS ENTER TO CONTINUE", 600, 800, 40, YELLOW);
	}

	if (!mouseOnText)
	{
		DrawRectangleLinesEx(textBox, outlineWidth, DARKGRAY);
		return;
	}

	DrawRectangleLinesEx(textBox, outlineWidth, RED);

	if (letterCount < maxLetterCount)
	{
		if (((framesCounter / 20) % 2) == 0)
		{
			DrawText("_", static_cast<int>(textBox.x) + 8 + MeasureText(name.data(), 40), static_cast<int>(textBox.y) + 12, 40, MAROON);
		}
	}
	else
	{
		DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
	}
}