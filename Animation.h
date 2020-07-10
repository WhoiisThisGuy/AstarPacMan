#include "SFML\Graphics.hpp"

#ifndef ANIM_H
#define ANIM_H

using namespace sf;

class Animation
{

public:
	Animation(Texture,Vector2u); //This is for pacman
	Animation (bool);
	Animation(); //This is for the Ghosts;

	void Update(const int&, const float&, const float&);
	int UpdateCustomOfColumns(int, int, const float&, float );
	void UpdateWithSingleImage(int);

public:

	IntRect uvRect;
	Vector2u AimageCount;
	
private:

	
	Vector2u currentImage;

	float totalTime;

};
#endif