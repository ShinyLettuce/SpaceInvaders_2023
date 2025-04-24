#pragma once
#include "mathutils.h"

constexpr Vector2i INVALID_POSITION = { -99,-99 };

constexpr Box PROJECTILE_BOUNDING_BOX = { 6, 42 };

constexpr auto FORMATION_STARTING_X = 100;
constexpr auto FORMATION_STARTING_Y = 50;
constexpr auto ALIEN_FORMATION_HEIGHT = 5;
constexpr auto ALIEN_FORMATION_WIDTH = 8;
constexpr auto ALIEN_SPACING = 80;
constexpr auto ALIEN_KILL_SCORE = 100;
constexpr auto ALIEN_SPEED = 2;
constexpr Box ALIEN_BOUNDING_BOX = { 85, 30 };

constexpr auto WALL_COUNT = 5;
constexpr Box WALL_BOUNDING_BOX = { 162, 70 };
constexpr auto WALL_TEXT_FONT_SIZE = 40;
constexpr auto WALL_TEXT_X_OFFSET = 21;
constexpr auto WALL_TEXT_Y_OFFSET = 10;

constexpr auto PLAYER_SPEED = 7;
constexpr Box PLAYER_BOUNDING_BOX = { 47, 94 };
constexpr auto PLAYER_ANIMATION_FRAME_COUNT = 3;
constexpr auto PLAYER_ANIMATION_FRAME_TIME = 0.4f;

const Color STAR_COLOR = SKYBLUE;

constexpr auto ENDSCREEN_MAX_LETTER_COUNT = 8;