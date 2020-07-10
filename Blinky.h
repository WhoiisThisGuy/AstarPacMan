/* Blinky wandering after PACMAN, if Blinky gets into a short range of Pacman,

he gets aggressive and starts chasing until he catches PACMAN or PACMAN gets out of the range. */

#include "Ghost.h"
//#include "ActorState.h"
//#include "Scatter.h"
#ifndef H_BLINKY
#define H_BLINKY
#define BLINKYTEXTUREPATH "Textures/blinky.png"

class Blinky:public Ghost
{

public:

	Blinky();
	~Blinky();
	void Update(const float& dt);
	//void Draw(RenderWindow& window);
	void setTargetNode(Vector2i) override;
	void setChaseTargetNode() override;
	void setScatterTargetNode() override;
	Vector2i getTempCoordsOnLevel() const;

	static Vector2i sTempCoordsOnLevel;
	void setStartPositions();
private:
	/* Constants start */
	const short unsigned int BLINKYSTARTX = 13;
	const short unsigned int BLINKYSTARTY = 11;

	const Vector2i scatterTargetNode = {27,9};
	Texture BlinkyTexture;//Have to do this at every single character... change it
	Texture targettexture;
	
	/* Constants end */
};

#endif