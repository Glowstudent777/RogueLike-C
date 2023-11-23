#ifndef ROGUE_H
#define ROGUE_H

#include <curses.h>
#include <stdlib.h>

typedef struct
{
	int y;
	int x;
} Position;

typedef struct
{
	char ch;
	bool walkable;
} Tile;

typedef struct
{
	Position pos;
	char ch;
} Entity;

void drawMap(void);
void drawEntity(Entity* entity);
void drawEverything(void);

void cursesSetup(void);
void gameLoop(void);
void closeGame(void);

Tile** createMapTiles(void);
void freeMap(void);
Position setupMap(void);

Entity* createPlayer(Position start_pos);
void handleInput(int input);
void movePlayer(Position newPos);

// externs
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern Entity* player;
extern Tile** map;

#endif // !ROGUE_H
