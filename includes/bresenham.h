#ifndef BRESENHAM_H
# define BRESENHAM_H


# include "SDL.h"


typedef struct  s_oct
{
    int         inc[2];
    int         d[2];
    int         e;
    int         bool;
    int         boolxy;
    int         ecart;
}               t_oct;

#endif