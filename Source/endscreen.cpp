#include "endscreen.h"

void EndScreen::InsertNewHighScore(std::string name)
{
	PlayerData newData;
	newData.name = name;
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

void EndScreen::drawTextBoxOutline() const noexcept
{
	if (mouseOnText)
	{
		DrawRectangleLinesEx(textBox, outlineWidth, RED);
	}
	else
	{
		DrawRectangleLinesEx(textBox, outlineWidth, DARKGRAY);
	}
}

void EndScreen::update()
{
	if (!newHighScore)
	{
		return;
	}

	mouseOnText = CheckCollisionPointRec(GetMousePosition(), textBox);

	if (mouseOnText)
	{
		SetMouseCursor(MOUSE_CURSOR_IBEAM);
		int key = GetCharPressed();

		while (key > 0)
		{
			if ((key >= 32) && (key <= 125) && (letterCount < maxLetterCount))
			{
				name[letterCount] = (char)key;
				name[letterCount + 1] = '\0';
				letterCount++;
			}
			key = GetCharPressed();
		}

		if (IsKeyPressed(KEY_BACKSPACE))
		{
			letterCount--;
			if (letterCount < 0) letterCount = 0;
			name[letterCount] = '\0';
		}
		framesCounter++;
	}
	else
	{
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		framesCounter = 0;
	}

	if (letterCount > 0 && letterCount < maxLetterCount && IsKeyReleased(KEY_ENTER))
	{
		std::string nameEntry(name);
		InsertNewHighScore(nameEntry);
		newHighScore = false;
	}
}

void EndScreen::render() noexcept
{
	if (!newHighScore)
	{
		DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);
		drawLeaderboard();
		return;
	}

	DrawText("NEW HIGHSCORE!", 600, 300, 60, YELLOW);
	DrawText("PLACE MOUSE OVER INPUT BOX!", 600, 400, 20, YELLOW);
	DrawRectangleRec(textBox, LIGHTGRAY);
	drawTextBoxOutline();
	DrawText(name, static_cast<int>(textBox.x) + 5, static_cast<int>(textBox.y) + 8, 40, MAROON);

	DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, 600, 20, YELLOW);

	if (mouseOnText)
	{
		if (letterCount < maxLetterCount)
		{
			if (((framesCounter / 20) % 2) == 0)
			{
				DrawText("_", static_cast<int>(textBox.x) + 8 + MeasureText(name, 40), static_cast<int>(textBox.y) + 12, 40, MAROON);
			}
		}
		else
		{
			DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
		}
	}

	if (letterCount > 0 && letterCount < maxLetterCount)
	{
		DrawText("PRESS ENTER TO CONTINUE", 600, 800, 40, YELLOW);
	}
}