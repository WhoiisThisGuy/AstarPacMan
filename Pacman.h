#include "Animation.h" //Animation includes the Grahpics.hpp
#include "Map.h"

#ifndef H_PACMAN
#define H_PACMAN

#define PACMANTEXTUREPATH "Textures/pacman.png"
#define PACMANSTARTPOSX 13
#define PACMANSTARTPOSY 28

class Pacman
{

public:

	Pacman();
	~Pacman();
	void Draw(RenderWindow& window);
	bool Update(const float& dTime, RenderWindow& window);

	//Vector2i getTempCoordsOnLevel() const;
	Vector2f getTempPosOnLevel() const { return body.getPosition(); };

	Vector2i getTempDirection() const { return tempDirection; }

	Vector2i getTempCoordsOnLevel() const;



public:
	static float speed;
	static bool normalSpeedOn;
	static Vector2i sTempCoordsOnLevel;
	static Vector2i sTempDirectionOnLevel;
private:

	bool checkCollision(const float& dTime);
	unsigned short int rowToSetForAnimation();
	void tunnelTeleport();
private:
	
	/*
	Constants START
	*/
	//All the OFFSET and the
	
	const float OFFSET = 10.0f; //For collision check.
	const float TURNNZONELOWERBOUND = 0.30f;
	const float TURNNZONEUPPERBOUND = 0.70f;
	const float PACMANSIZEX = 50.0f;
	const float PACMANSIZEY = 50.0f;
	const float  OFFSETMOVE = 6.0f;
	const float ANIMATIONSWITCHTIME = 0.08f;
	const Vector2i STARTDIRECTION = {-1,0};
	const Vector2u textureRowNColNumber = {2,4};

	float PACMANSPEED = 142;
	/*
	Constants END
	*/
	RectangleShape body;
	Texture PacmanTexture;//Have to do this at every single character... change it
	string health;

	bool havebufferedmove;
	
	unsigned int row;

	Animation* animation;

	Vector2i tempDirection;
	Vector2i bufferedDirection;
	Event event;
	Clock deathClock; //used for death animation
	bool deathStarted;
	
};

#endif