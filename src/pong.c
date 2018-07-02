#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "define.h"
#include "game.h"
#include "vector.h"
#include "SDL2/SDL.h"

SDL_bool running = SDL_FALSE;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

const int control_mode = CONTROL_MODE_MOUSE;

void initSDL();
void mainLoop();
void render();
void update();
void quit();

void initSDL()
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
            else if (event.type == SDL_KEYDOWN)
            {
                if (control_mode == CONTROL_MODE_KEYBOARD)
                {
                    for (int i = 0; i < NUM_PLAYERS; i++)
                    {
                        if (players[i].type == TYPE_PADDLE_BOTTOM)
                        {
                            if (event.key.keysym.sym == PADDLE_BOTTOM_KEY_LEFT)
                            {
                                players[i].speed.x = -PADDLE_SPEED;
                            }
                            else if (event.key.keysym.sym == PADDLE_BOTTOM_KEY_RIGHT)
                            {
                                players[i].speed.x = PADDLE_SPEED;
                            }
                        }
                        else if (players[i].type == TYPE_PADDLE_TOP)
                        {
                            if (event.key.keysym.sym == PADDLE_TOP_KEY_LEFT)
                            {
                                players[i].speed.x = -PADDLE_SPEED;
                            }
                            else if (event.key.keysym.sym == PADDLE_TOP_KEY_RIGHT)
                            {
                                players[i].speed.x = PADDLE_SPEED;
                            }
                        }
                        else if (players[i].type == TYPE_PADDLE_LEFT)
                        {
                            if (event.key.keysym.sym == PADDLE_LEFT_KEY_UP)
                            {
                                players[i].speed.y = -PADDLE_SPEED;
                            }
                            else if (event.key.keysym.sym == PADDLE_LEFT_KEY_DOWN)
                            {
                                players[i].speed.y = PADDLE_SPEED;
                            }
                        }
                        else if (players[i].type == TYPE_PADDLE_RIGHT)
                        {
                            if (event.key.keysym.sym == PADDLE_RIGHT_KEY_UP)
                            {
                                players[i].speed.y = -PADDLE_SPEED;
                            }
                            else if (event.key.keysym.sym == PADDLE_RIGHT_KEY_DOWN)
                            {
                                players[i].speed.y = PADDLE_SPEED;
                            }
                        }
                    }
                }
            }
            else if (event.type == SDL_KEYUP)
            {
                if (control_mode == CONTROL_MODE_KEYBOARD)
                {
                    for (int i = 0; i < NUM_PLAYERS; i++)
                    {
                        if (players[i].type == TYPE_PADDLE_BOTTOM)
                        {
                            if (event.key.keysym.sym == PADDLE_BOTTOM_KEY_LEFT)
                            {
                                players[i].speed.x = 0;
                            }
                            else if (event.key.keysym.sym == PADDLE_BOTTOM_KEY_RIGHT)
                            {
                                players[i].speed.x = 0;
                            }
                        }
                        else if (players[i].type == TYPE_PADDLE_TOP)
                        {
                            if (event.key.keysym.sym == PADDLE_TOP_KEY_LEFT)
                            {
                                players[i].speed.x = 0;
                            }
                            else if (event.key.keysym.sym == PADDLE_TOP_KEY_RIGHT)
                            {
                                players[i].speed.x = 0;
                            }
                        }
                        else if (players[i].type == TYPE_PADDLE_LEFT)
                        {
                            if (event.key.keysym.sym == PADDLE_LEFT_KEY_UP)
                            {
                                players[i].speed.y = 0;
                            }
                            else if (event.key.keysym.sym == PADDLE_LEFT_KEY_DOWN)
                            {
                                players[i].speed.y = 0;
                            }
                        }
                        else if (players[i].type == TYPE_PADDLE_RIGHT)
                        {
                            if (event.key.keysym.sym == PADDLE_RIGHT_KEY_UP)
                            {
                                players[i].speed.y = 0;
                            }
                            else if (event.key.keysym.sym == PADDLE_RIGHT_KEY_DOWN)
                            {
                                players[i].speed.y = 0;
                            }
                        }
                    }
                }
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                if (control_mode == CONTROL_MODE_MOUSE)
                {
                    int mx = event.motion.x;
                    int my = event.motion.y;
                    for (int i = 0; i < NUM_PLAYERS; i++)
                    {
                        if (players[i].type == TYPE_PADDLE_BOTTOM || players[i].type == TYPE_PADDLE_TOP)
                        {
                            if (abs(my - players[i].position.y) < MOUSE_RANGE)
                            {
                                if (players[i].position.x + players[i].w / 2 < mx)
                                {
                                    players[i].speed.x = PADDLE_SPEED;
                                }
                                else
                                {
                                    players[i].speed.x = -PADDLE_SPEED;
                                }
                            }
                            else
                            {
                                players[i].speed.x = 0;
                            }
                        }
                        else if (players[i].type == TYPE_PADDLE_LEFT || players[i].type == TYPE_PADDLE_RIGHT)
                        {
                            if (abs(mx - players[i].position.x) < MOUSE_RANGE)
                            {
                                if (players[i].position.y + players[i].h / 2 < my)
                                {
                                    players[i].speed.y = PADDLE_SPEED;
                                }
                                else
                                {
                                    players[i].speed.y = -PADDLE_SPEED;
                                }
                            }
                            else
                            {
                                players[i].speed.y = 0;
                            }
                        }
                    }
                }
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect rect;

    // Draw Players
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        rect = createRect(&players[i]);
        SDL_RenderFillRect(renderer, &rect);
    }

    // Draw Ball
    rect = createRect(&ball);
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}

void update()
{
    // Update Players
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        vec_sum(&players[i].position, players[i].speed);
        updatePlayer(&players[i]);
    }

    // Update Ball
    vec_sum(&ball.position, ball.speed);
    updateBall();

    // Update Score
    updateScore();
}

void quit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argv, char **args)
{
    srand(time(NULL));

    initSDL();
    initGame();
    mainLoop();
    quit();

    return 0;
}