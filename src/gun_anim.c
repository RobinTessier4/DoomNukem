#include "proto_global.h"
#include "proto_global.h"
#include "proto_global.h"
#include "proto_global.h"
#include "proto_global.h"


SDL_Rect    get_gun_pos(SDL_Rect srcdim, t_data *d, SDL_Point pos)
{
    srcdim.x = d->sprite[d->gun_ind].frame_size.w * pos.x;
    srcdim.y = d->sprite[d->gun_ind].frame_size.h * pos.y;
    srcdim.w = d->sprite[d->gun_ind].frame_size.w - d->sprite[d->gun_ind].anim[d->sprite[d->gun_ind].index].offset.x;
    srcdim.h = d->sprite[d->gun_ind].frame_size.h - d->sprite[d->gun_ind].anim[d->sprite[d->gun_ind].index].offset.y;
    return (srcdim);
}

SDL_Rect    gun_dimension(SDL_Rect dstdim, t_data *d)
{
    dstdim.x = HALF_WIN_SIZE_X - d->sprite[d->gun_ind].size.x;
    dstdim.y = HALF_WIN_SIZE_Y - d->sprite[d->gun_ind].size.y;
    dstdim.w = (HALF_WIN_SIZE_X + d->sprite[d->gun_ind].size.x) - dstdim.x;
    dstdim.h = HALF_WIN_SIZE_Y + d->sprite[d->gun_ind].size.y;
    return (dstdim);
}

void    gun_idle_anim(t_data *d)
{
    SDL_Rect srcdim;
    SDL_Rect dstdim;
    SDL_Point pos;

    if (d->sprite[d->gun_ind].aim_on == 0)
    {
    pos.x = d->sprite[d->gun_ind].anim[IDLE].pos->x;
    pos.y = d->sprite[d->gun_ind].anim[IDLE].pos->y;
    }
    else if (d->sprite[d->gun_ind].aim_on == 1)
    {
            pos.x = d->sprite[d->gun_ind].anim[AIM].pos->x;
            pos.y = d->sprite[d->gun_ind].anim[AIM].pos->y;
            d->sprite[d->gun_ind].index = AIM;
    }
    srcdim = get_gun_pos(srcdim, d, pos);
    dstdim = gun_dimension(dstdim, d);
	// d->displayed_gun = d->sprite[d->gun_ind].text;
	d->dst_gun = dstdim;
	d->src_gun = srcdim;
    // SDL_RenderCopy(d->rend, d->sprite[d->gun_ind].text, &srcdim, &dstdim);
}

void    sprite_anim_gun(t_data *d)
{
    SDL_Rect srcdim;
    SDL_Rect dstdim;
    SDL_Point pos;
    Uint32 currTime;
    int diff;

    diff = 0;
    if (d->sprite[d->gun_ind].on >= 0)
    {
        currTime = SDL_GetTicks();
        diff = (currTime - d->sprite[d->gun_ind].time) / 100;
    }
    pos.x = (d->sprite[d->gun_ind].anim[d->sprite[d->gun_ind].index].pos->x + diff) % d->sprite[d->gun_ind].nb_frame.x;
    pos.y = d->sprite[d->gun_ind].anim[d->sprite[d->gun_ind].index].pos->y + (d->sprite[d->gun_ind].anim[d->sprite[d->gun_ind].index].pos->x + diff) / d->sprite[d->gun_ind].nb_frame.x;
    if (diff < d->sprite[d->gun_ind].anim[d->sprite[d->gun_ind].index].nb_frame && d->sprite[d->gun_ind].on == 0)
    {
        srcdim = get_gun_pos(srcdim, d, pos);
        dstdim = gun_dimension(dstdim, d);
		// d->displayed_gun = d->sprite[d->gun_ind].text;
		d->dst_gun = dstdim;
		d->src_gun = srcdim;
        // SDL_RenderCopy(d->rend, d->sprite[d->gun_ind].text, &srcdim, &dstdim);
    }
    else if ((d->sprite[d->gun_ind].index == FIRE || d->sprite[d->gun_ind].index == AIMFIRE) && (d->sprite[d->gun_ind].on == 0) && d->sprite[d->gun_ind].anim_end == 0)
        d->sprite[d->gun_ind].time = SDL_GetTicks();
    else
    {
        d->sprite[d->gun_ind].index = IDLE;
        d->sprite[d->gun_ind].on = -1;
        gun_idle_anim(d);
    }
}