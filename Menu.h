#pragma once
#include "GameState.h"
class Menu : public GameState
{
public:
	Menu();
	~Menu();
	GameState* Update(RenderWindow&);
	void Render(RenderWindow& );
	void EventsUpdate(GameState* , RenderWindow& );
	bool getPlay() { return play; }
	bool getQuit() { return quit; }
public:


	typedef struct MenuElem {
	
	public:
		MenuElem(unsigned short int pnum, MenuElem* pnext, MenuElem* pprevious) :num(pnum), next(pnext), previous(pprevious) {}
	public:
		MenuElem* previous;
		MenuElem* next;
		unsigned short int num;
		Text text;
	}MenuElem;

private:

	Font font;


	MenuElem menuElemPlay;
	MenuElem menuElemQuit;
	MenuElem* temp;
	Event event;
	bool play;
	bool quit;
};

