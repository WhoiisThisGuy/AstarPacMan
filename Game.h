#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"
//#include "Blinky.h"
#include "Pacman.h"

class Game {

public:

	Game();
	~Game();
	void run();
	void Update();
	void UpdateDt();
	void UpdateSfmlEvents();
	void Render();
private:
	
//	sf::Font font;

	//Info kiiras pacman poziciojarol
	float dt;
	RenderWindow window;
	Event event;
	Clock deltaClock;
	//Game futáshoz
	Sprite backgroundSprite;

	Map map;
	//pálya

	Pacman pacman;
	//The hero
	
	Blinky blinky;
	Pinky pinky;
	Inky inky;
	Clyde clyde;
	//Chasers

	
};
