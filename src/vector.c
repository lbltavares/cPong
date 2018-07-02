#include <math.h>
#include "vector.h"

vector vec_create(float x, float y)
{
    vector v;
    v.x = x;
    v.y = y;
    return v;
}

void vec_normalize(vector *v)
{
    float mag = vec_mag(*v);
    vec_div(v, mag);
}

float vec_mag(vector v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

void vec_sum(vector *a, vector b)
{
    a->x += b.x;
    a->y += b.y;
}

void vec_sub(vector *a, vector b)
{
    a->x -= b.x;
    a->y -= b.y;
}

void vec_mult(vector *v, float m)
{
    v->x *= m;
    v->y *= m;
}

void vec_div(vector *v, float d)
{
    if (d != 0)
    {
        v->x /= d;
        v->y /= d;
    }
}