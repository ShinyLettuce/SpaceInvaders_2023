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
	for (Star& star : Stars) //TODO: change to ranged for
	{
		star.Update(offset);
	}

}

void Background::Render()
{
	for (Star& star : Stars) //TODO: change to ranged for
	{
		star.Render();
	}
}