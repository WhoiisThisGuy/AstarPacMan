/* Blinky wandering after PACMAN, if Blinky gets into a short range of Pacman,

he gets aggressive and starts chasing until he catches PACMAN or PACMAN gets out of the range. */

#include "Ghost.h"
//#include "ActorState.h"
//#include "Scatter.h"
#ifndef H_INKY
#define H_INKY
#define INKYTEXTUREPATH "Textures/inky.png"

class Inky :public Ghost
{

public:

	Inky();//Have to do this at every single character... change it);
	~Inky();
	void Update(const float& dt);
	//void Draw(RenderWindow& window);
	void setTargetNode(Vector2i) override;

	virtual void moveUpAndDown() override;
	virtual bool moveToFourteenDotThirtyFive() override;
	void setChaseTargetNode() override;
	void setScatterTargetNode() override;
	void setStartPositions();

public:
	Vector2i pacmanTempDirection;
	Vector2i blinkyTempCoordsOnLevel;

private:
	/* Constants start */
	const float INKYSTARTX = 11.40f; //13.60
	const float INKYSTARTY = 14.0f;

	const Vector2i scatterTargetNode = { 27,34 };
	
	Texture targettexture;
	Texture InkyTexture;
	/* Constants end */
};

#endif