#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "game.h"
#include "SDL2/SDL.h"

GameObject createPaddle(int type)
{
    GameObject p;
    if (type == TYPE_PADDLE_BOTTOM)
    {
        p.h = PADDLE_THICKNESS;
        p.w = PADDLE_LENGTH;
        p.position = vec_create(WIDTH / 2 - p.w / 2, HEIGHT - p.h - PADDLE_MARGIN);
    }
    else if (type == TYPE_PADDLE_TOP)
    {
        p.h = PADDLE_THICKNESS;
        p.w = PADDLE_LENGTH;
        p.position = vec_create(WIDTH / 2 - p.w / 2, PADDLE_MARGIN);
    }
    else if (type == TYPE_PADDLE_LEFT)
    {
        p.h = PADDLE_LENGTH;
        p.w = PADDLE_THICKNESS;
        p.position = vec_create(PADDLE_MARGIN, HEIGHT / 2 - p.h / 2);
    }
    else if (type == TYPE_PADDLE_RIGHT)
    {
        p.h = PADDLE_LENGTH;
        p.w = PADDLE_THICKNESS;
        p.position = vec_create(WIDTH - p.w - PADDLE_MARGIN, HEIGHT / 2 - p.h / 2);
    }
    p.speed = vec_create(0, 0);
    p.type = type;
    return p;
}

SDL_Rect createRect(GameObject *obj)
{
    SDL_Rect result;
    result.x = obj->position.x;
    result.y = obj->position.y;
    result.w = obj->w;
    result.h = obj->h;
    return result;
}

GameObject createBall(int type)
{
    GameObject ball;
    if (type == TYPE_BALL_DEFAULT)
    {
        ball.w = BALL_WIDTH;
        ball.h = BALL_HEIGHT;
        ball.position = vec_create(WIDTH / 2 - BALL_WIDTH / 2, HEIGHT / 2 - BALL_HEIGHT / 2);
        ball.speed = vec_create(CHOOSERANDOM(-BALL_SPEED, BALL_SPEED), CHOOSERANDOM(-BALL_SPEED, BALL_SPEED));
    }
    else if (type == TYPE_BALL_SMALL)
    {
        ball.w = BALL_WIDTH / 2;
        ball.h = BALL_HEIGHT / 2;
        ball.position = vec_create(WIDTH / 2 - BALL_WIDTH / 2, HEIGHT / 2 - BALL_HEIGHT / 2);
        ball.speed = vec_create(CHOOSERANDOM(-BALL_SPEED, BALL_SPEED), CHOOSERANDOM(-BALL_SPEED, BALL_SPEED));
    }
    ball.type = type;
    return ball;
}

void initGame()
{
    players[0] = createPaddle(TYPE_PADDLE_LEFT);
    players[1] = createPaddle(TYPE_PADDLE_RIGHT);
    players[2] = createPaddle(TYPE_PADDLE_BOTTOM);
    players[3] = createPaddle(TYPE_PADDLE_TOP);

    ball = createBall(TYPE_BALL_DEFAULT);
}

void updatePlayer(GameObject *p)
{
    if (p->position.y < 0)
        p->position.y = 0;
    if (p->position.y > HEIGHT - p->h)
        p->position.y = HEIGHT - p->h;
    if (p->position.x < 0)
        p->position.x = 0;
    if (p->position.x > WIDTH - p->w)
        p->position.x = WIDTH - p->w;
}

void manageBallCollision(GameObject *paddle)
{
    SDL_Rect rball = createRect(&ball);
    SDL_Rect rpad = createRect(paddle);
    if (SDL_HasIntersection(&rball, &rpad))
    {
        if (paddle->type == TYPE_PADDLE_RIGHT)
        {
            ball.position.x = paddle->position.x - ball.w;
            ball.speed.x *= -1;
        }
        else if (paddle->type == TYPE_PADDLE_LEFT)
        {
            ball.position.x = paddle->position.x + paddle->w;
            ball.speed.x *= -1;
        }
        else if (paddle->type == TYPE_PADDLE_TOP)
        {
            ball.position.y = paddle->position.y + paddle->h;
            ball.speed.y *= -1;
        }
        else if (paddle->type == TYPE_PADDLE_BOTTOM)
        {
            ball.position.y = paddle->position.y - ball.h;
            ball.speed.y *= -1;
        }
    }
}

void updateBall()
{
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        manageBallCollision(&players[i]);
    }
}

void updateScore()
{
    if (ball.position.x > WIDTH)
    {
        for (int i = 0; i < NUM_PLAYERS; i++)
        {
            if (players[i].type == TYPE_PADDLE_LEFT)
            {
                scores[i]++;
            }
        }
        initGame();
    }
    else if (ball.position.x + ball.w < 0)
    {
        for (int i = 0; i < NUM_PLAYERS; i++)
        {
            if (players[i].type == TYPE_PADDLE_RIGHT)
            {
                scores[i]++;
            }
        }
        initGame();
    }
    else if (ball.position.y > HEIGHT)
    {
        for (int i = 0; i < NUM_PLAYERS; i++)
        {
            if (players[i].type == TYPE_PADDLE_TOP)
            {
                scores[i]++;
            }
        }
        initGame();
    }
    else if (ball.position.y + ball.h < 0)
    {
        for (int i = 0; i < NUM_PLAYERS; i++)
        {
            if (players[i].type == TYPE_PADDLE_BOTTOM)
            {
                scores[i]++;
            }
        }
        initGame();
    }
}