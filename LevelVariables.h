#pragma once

#include "SFML\Graphics.hpp"

#ifndef H_LEVELVALUES
using namespace sf;
#define H_LEVELVALUES
/* This header file contains the values for timings, scores, fruits etc. depending on the level */
#define GAMESTARTPAUSETIME 3
#define GHOSTCAUGHTPAUSETIME 1

#define PACMANBASICSPEED 240 //100% speed
#define GHOSTBASICSPEED 237 //100% speed

extern Font font;

extern unsigned short int LEVELNUMBER;
extern constexpr unsigned short int percentage(unsigned short int n, unsigned short int p); //p % of the n number

/* This table contains the following informations:

The row number equals to the number of the level. The 12 columns contains the following inormations:

------0-------------1---------------2----------------3-----------4-----------------5-----------------6---------------7---------------8-----------------9---------------------10---------------------11-----------
|Bonus Points|Pac-Man Speed|Pac-Man Dots Speed|Ghost Speed|GhostTunnel Speed|Elroy 1 Dots Left|Elroy 1 Speed|Elroy 2 Dots Left|Elroy 2 Speed| Fright. Pac-Man Speed| Fright Pac-Man Dots Speed|Fright Ghost Speed|

percentage does a % calculation
every speed is calculated from the basic speed value of the characters
fruits: are numbered from 0 to 6 which is the order of the images on the texture sprite sheet
value 0 means, no value change in the speed limit or no limit like the frighten mode in the last rows has no time limit because there is no frighten mode anymore on those levels.
*/

extern unsigned short int levelValues[][15];

extern float scatterTimings[4][5];

/* 0 means infinite */

extern unsigned short int chaseTimings[4][5];

extern unsigned short int fruitAppear[22];
extern unsigned short int FRUITNUMBER; //0. is the first fruit

#endif