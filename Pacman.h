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
	void Update(float dTime);

	//Vector2i getTempCoordsOnLevel() const;
	Vector2f getTempPosOnLevel() const { return body.getPosition(); };

	Vector2i getTempDirection() const { return tempDirection; }

	Vector2i getTempCoordsOnLevel() const;

	static Vector2i sTempCoordsOnLevel;
	static Vector2i sTempDirectionOnLevel;
	static string sTempCoordsOnLevelString;

private:
	bool checkBufferedCollision(float& dTime);
	bool checkCollision(float& dTime);

private:

	/*
	Constants START
	*/
	//All the OFFSET and the
	const float PACMANSPEED = 150.0f;
	const float OFFSET = 12.0f; //For collision check.
	const float OFFSETB = 30.0f; //For changing direction, to prevent turning into walls in tunnels
	const float PACMANSIZEX = 40.0f;
	const float PACMANSIZEY = 40.0f;
	const float  OFFSETMOVE = 6.0f;
	const float ANIMATIONSWITCHTIME = 0.08f;
	const Vector2i STARTDIRECTION = {-1,0};
	const Vector2u textureRowNColNumber = {2,4};

	/*
	Constants END
	*/
	RectangleShape body;
	Texture PacmanTexture;//Have to do this at every single character... change it
	string health;

	bool havebufferedmove;
	float speed;
	unsigned int row;

	Animation* animation;

	Vector2i tempDirection;
	Vector2i bufferedDirection;
	
};

#endif