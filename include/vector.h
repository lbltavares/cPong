#ifndef _VECTOR_H
#define _VECTOR_H

typedef struct _Vector
{
    float x, y;
} vector;

vector vec_create(float x, float y);

void vec_normalize(vector *v);
float vec_mag(vector v);

void vec_sum(vector *a, vector b);
void vec_sub(vector *a, vector b);

void vec_mult(vector *a, float m);
void vec_div(vector *a, float d);

#endif