#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "SDL2/SDL.h"

#define WIDTH 740
#define HEIGHT 480

SDL_bool running = SDL_FALSE;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

struct _Paddle
{
    SDL_Rect body;
    vector speed;
} p1, p2;

struct _Ball
{
    SDL_Rect body;
    vector speed;
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
    p1.body.x = 0;
    p1.body.y = 0;
    p1.body.w = 30;
    p1.body.h = 70;
    p1.speed = vec_create(1, 0);

    p2.body.x = 300;
    p2.body.y = 300;
    p2.body.w = 30;
    p2.body.h = 70;
    p2.speed = vec_create(0, 0);

    ball.body.x = 300;
    ball.body.y = 200;
    ball.body.w = 50;
    ball.body.h = 50;
    ball.speed = vec_create(0, 0);
}

void mainLoop()
{
    long time = SDL_GetTicks();
    int fps = 30;

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

        if (time + fps > SDL_GetTicks())
            continue;
        time = SDL_GetTicks();

        update();
        render();
    }
}

void render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Draw Player 1
    SDL_RenderFillRect(renderer, &p1.body);

    // Draw Player 2
    SDL_RenderFillRect(renderer, &p2.body);

    // Draw Ball
    SDL_RenderFillRect(renderer, &ball.body);

    SDL_RenderPresent(renderer);
}

void update()
{
    p1.body.x += p1.speed.x;
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
    initGameObjects();
    mainLoop();
    quit();

    return 0;
}