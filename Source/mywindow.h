#pragma once
#include "raylib.h"
#include <stdexcept>

class MyWindow {
	int screenWidth = 1920;
	int screenHeight = 1080;
public:
	MyWindow()
	{
		InitWindow(screenWidth, screenHeight, "SPACE INVADERS");
		if (!IsWindowReady)
		{
			throw std::runtime_error("Failed to open window");
		}
		SetTargetFPS(60);
	}

	MyWindow(const MyWindow& other) = delete;
	MyWindow& operator=(const MyWindow& other) = delete;
	MyWindow(MyWindow&& other) = delete;
	MyWindow& operator=(MyWindow&& other) = delete;

	~MyWindow()
	{
		CloseWindow();
	}
};