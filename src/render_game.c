#include "proto_global.h"

void 			print_data2screen(t_data *d, t_map_data *map, t_hud *hud)
{
    SDL_Rect 	tmp;

	tmp = set_sdl_rect(MINI_MAP_POS_X, MINI_MAP_POS_Y, MINI_MAP_SIZE_X, MINI_MAP_SIZE_Y);
	//SDL_RenderClear(d->rend);
	SDL_UpdateTexture(d->screen, NULL, d->p_screen, WIN_SIZE_X * 4);
	print_mini_map(d, map);
	SDL_RenderCopy(d->rend, d->screen, NULL, NULL);
	SDL_RenderCopy(d->rend, d->sprite[d->gun_ind].text, &d->src_gun, &d->dst_gun);
	SDL_RenderCopy(d->rend, d->mini_map, NULL, &tmp);
	render_hud(d);
    SDL_RenderPresent(d->rend);
}