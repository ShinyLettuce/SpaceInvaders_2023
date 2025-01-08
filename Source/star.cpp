#include "star.h"

void Star::Update(float starOffset)
{
	position.x = initPosition.x + starOffset;
	position.y = initPosition.y;

}

void Star::Render()
{
	DrawCircle((int)position.x, (int)position.y, size, color);
}


void Background::Initialize(int starAmount)
{
	for (int i = 0; i < starAmount; i++)
	{
		const Star newStar;
		Stars.push_back(newStar);
	}
}

void Background::Update(float offset)
{
	for (int i = 0; i < Stars.size(); i++) //TODO: change to ranged for
	{
		Stars[i].Update(offset);
	}

}

void Background::Render()
{
	for (int i = 0; i < Stars.size(); i++) //TODO: change to ranged for
	{
		Stars[i].Render();
	}
}