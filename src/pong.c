#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"

#define WIDTH 640
#define HEIGHT 480

SDL_bool running = SDL_FALSE;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

struct _Paddle
{
    int x, y, w, h;
    int xspeed, yspeed;
} p1, p2;

struct _Ball
{
    int x, y, w, h;
    int xspeed, yspeed;
} ball;

void init();
void initGameObjects();
void mainLoop();
void render();
void update();
void quit();

void init()
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        exit(-1);
    }

    window = SDL_CreateWindow("Pong",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        exit(-1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        exit(-1);
    }
}

void initGameObjects()
{
    p1.x = 0;
    p1.y = 0;
    p1.w = 50;
    p1.h = 100;
}

void mainLoop()
{
    running = SDL_TRUE;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }
    }
}

void render()
{
}

void update()
{
}

void quit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argv, char **args)
{
    init();
    mainLoop();
    quit();

    return 0;
}