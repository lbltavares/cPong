#ifndef _GAME_H
#define _GAME_H

#include "SDL2/SDL.h"
#include "vector.h"
#include "define.h"

typedef struct _GameObject
{
    int type;
    int w, h;
    vector position, speed;
} GameObject;

GameObject ball, players[NUM_PLAYERS];
unsigned int scores[NUM_PLAYERS];

void initGame();
void updatePlayer(GameObject *p);
void manageBallCollision(GameObject *paddle);
void updateBall();
void updateScore();
GameObject createPaddle(int type), createBall(int type);
SDL_Rect createRect(GameObject *obj);

#endif