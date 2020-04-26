/* Blinky wandering after PACMAN, if Blinky gets into a short range of Pacman,

he gets aggressive and starts chasing until he catches PACMAN or PACMAN gets out of the range. */

#include "Ghost.h"
//#include "ActorState.h"
//#include "Scatter.h"
#ifndef H_PINKY
#define H_PINKY
#define PINKYTEXTUREPATH "Textures/pinky.png"

class Pinky :public Ghost
{

public:

	Pinky();
	~Pinky();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	void setTargetNode(Vector2i) override;

	virtual void moveUpAndDown() override;
	virtual bool moveToFourteenDotThirtyFive() override;
	void setChaseTargetNode() override;
	void setScatterTargetNode() override;
	
public:
	Vector2i pacmanTempDirection;

private:
	/* Constants start */
	const float PINKYSTARTX = 13.60f; //13.60
	const float PINKYSTARTY = 14.0f;

	const Vector2i scatterTargetNode = { 0,0 };
	Texture PinkyTexture;//Have to do this at every single character... change it
	Texture targettexture;

	/* Constants end */
	Animation* animation;
};

#endif