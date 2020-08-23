#include "SFML\Graphics.hpp"

#ifndef ANIM_H
#define ANIM_H

/* Coordinates burned in based on the Ghost.png */

extern class Pacman;
extern class Ghost;

using namespace sf;

class Animation
{

public:
	Animation();
	Animation (Pacman*); //This is the constructor for pacman.
	Animation(Ghost*); //This is the constructor for the Ghosts.
	~Animation();
	void Update(const float&, const float& ); //New version, Only ghosts using these for now
	void UpdateFrightenAnimation(const float&, const float&, unsigned short int&); //New version, Only ghosts using these for now
	 
	void Update(const int&, const float&, const float&); //Old version, Pacman uses it.
	int UpdateCustomOfColumns(int, int, const float&, float ); //Old version, Pacman uses it.

	void UpdateSingleImage(); //When the ghost is heading back to the house.
	void setScoreImage(const unsigned short int&); //If a ghost is eaten.

public:

	IntRect uvRect;// the uvRect will select the image area from selectBox.
	Vector2u AimageCount;
	
	
	/* This is hard coded to work only in this game. Wierd implementation, faster than smarter solution.
	The idea is that in every state, before updating animation, I change these parameters to set up what pictures should be updated.
	They are all public bc I did not want to write get-set for every single one of these parameters it is unneccessary, they are only changing in the ghost states.
	Note: Only ghosts are using these.
	*/
	
	int firstImage; //col number of the first image
	int lastImage; //number of columns to go trough
	//unsigned short int gap; //number of empty pixels between images
	Vector2u imageToSet; //Actual image x and y coordinates on the Texture.
	Vector2u selectBox; //image size + gap between images = selectBox size, for the ghosts this is 16x16 pixels, using this to step between images. 

private:

	
	Vector2u currentImage;
	float totalTime;

};
#endif