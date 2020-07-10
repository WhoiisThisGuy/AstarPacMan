#include "Ghost.h"

//#include "ActorState.h"
//#include "Scatter.h"
#ifndef H_CLYDE
#define H_CLYDE
#define CLYDETEXTUREPATH "Textures/clyde.png"

class Clyde :public Ghost
{

public:

	Clyde();
	~Clyde();
	void Update(const float& dt);
	//void Draw(RenderWindow& window);
	void setTargetNode(Vector2i) override;
	void setChaseTargetNode() override;
	void setScatterTargetNode() override;
	Vector2i getTempCoordsOnLevel();

	static Vector2i sTempCoordsOnLevel;
	virtual void moveUpAndDown() override;
	virtual bool moveToFourteenDotThirtyFive() override;
	void setStartPositions();
private:
	/* Constants start */
	const float CLYDESTARTX = 15.70;
	const float CLYDESTARTY = 14;

	const Vector2i scatterTargetNode = { 0,34 };
	Texture ClydeTexture;//Have to do this at every single character... change it
	Texture targettexture;
	CircleShape clydeCircle;
	/* Constants end */
};

#endif
