#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include <vector>
#include <string_view>
#include <stdexcept>
#include <format>

class MyTexture2D {
	Texture2D _tex;
public:
	explicit MyTexture2D(std::string_view path)
	{
		_tex = LoadTexture(path.data());
		if (_tex.id <= 0)
		{
			throw std::runtime_error(std::format("Failed to load texture: {}", path));
		}
	}

	MyTexture2D() = delete;

	MyTexture2D(const MyTexture2D& other) = delete;
	MyTexture2D& operator=(const MyTexture2D& other) = delete;

	MyTexture2D(MyTexture2D&& other) noexcept {
		std::swap(other._tex, _tex);
	};
	MyTexture2D& operator=(MyTexture2D&& other) noexcept {
		std::swap(other._tex, _tex);
		return *this;
	};

	~MyTexture2D()
	{
		UnloadTexture(_tex);
	}

	const Texture2D& get() const noexcept {
		return _tex;
	}

	int getWidth() const noexcept { return _tex.width; }
	int getHeight() const noexcept { return _tex.height; }
	int getHalfWidth() const noexcept { return _tex.width / 2; }
	int getHalfHeight() const noexcept { return _tex.height / 2; }
};
