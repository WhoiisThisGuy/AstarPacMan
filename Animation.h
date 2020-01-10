#pragma once
#include <SFML/Graphics.hpp>

class Animation
{

public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount);


	void Update(int row, float deltaTime, float switchTime);

public:
	sf::IntRect uvRect;

private:
	sf::Vector2u AimageCount;
	sf::Vector2u currentImage;

	float totalTime;
	//float switchTime;
};
