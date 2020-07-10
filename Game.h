#include <stack>
#include "GameState.h"
#include "Menu.h"
#include "Playing.h"

using std::stack;

class Game {

public:

	Game();
	~Game();
	void run();
	void UpdateSfmlEvents();
private:
	
//	sf::Font font;

	//Info kiiras pacman poziciojarol
	float dt;
	RenderWindow window;
	Event event;
	unsigned short int stateFlag; // 0 = Quit, 1 = Menu, 2 = Play

	GameState* gameState;
	GameState* newStateToSet;
};
