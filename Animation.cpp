#include "Animation.h"
#include <iostream>

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount)
{
	AimageCount = imageCount;
	//this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;
	currentImage.y = 0;
	uvRect.width = texture->getSize().x / float(AimageCount.x);
	uvRect.height = texture->getSize().y / float(AimageCount.y);
}

void Animation::Update(int row, float deltaTime, float switchTime)
{
	currentImage.y = row;
	totalTime += deltaTime;
	if (totalTime >= switchTime) {

		totalTime = 0; // jobban meggondolni az = 0át totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= AimageCount.x) {
			currentImage.x = 0;
		}
	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}