#include "Animation.h"
#include <iostream>

Animation::Animation(sf::Texture texture,sf::Vector2u imageCount)
{
	AimageCount = imageCount;
	totalTime = 0.0f;
	currentImage.x = 0;
	currentImage.y = 0;
	uvRect.width = texture.getSize().x / float(AimageCount.x);
	uvRect.height = texture.getSize().y / float(AimageCount.y);
}

Animation::Animation(bool pacman)
{
	if (pacman) {
		AimageCount = { 2, 4 };
		totalTime = 0.0f;
		currentImage.x = 0;
		currentImage.y = 0;
		uvRect.width = 14.0f;
		uvRect.height = 14.0f;
	}
}

Animation::Animation()
{
	AimageCount = { 2, 10 };
	totalTime = 0.0f;
	currentImage.x = 0;
	currentImage.y = 0;
	uvRect.width = 14.0f;
	uvRect.height = 14.0f;
}

void Animation::Update(const int& row, const float& deltaTime, const float& switchTime)
{

	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime) {

		totalTime = 0;
		currentImage.x++;

		if (currentImage.x >= AimageCount.x) {
			currentImage.x = 0;
		}
	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;

}

void Animation::UpdateWithSingleImage(int row)
{
	uvRect.left = uvRect.width;
	uvRect.top = row * uvRect.height;

}

int Animation::UpdateCustomOfColumns(int row, int col, const float& deltaTime, float switchTime) //This function is to update with custom number of columns
{
	unsigned short int tempimgnum;
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime) {

		totalTime = 0;
		currentImage.x++;

		if (currentImage.x >= col) {
			tempimgnum = currentImage.x;
			currentImage.x = 0;
			return tempimgnum;
		}
	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;

	return 0;
}


