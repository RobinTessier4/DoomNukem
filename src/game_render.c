#include "proto_global.h"

int	render_game(t_data *d, int ac, char **av)
{
	while (d->run_game == 1)
	{
		d->time_last_frame = d->time;
		d->time = SDL_GetTicks();
		d->diff_time = (float)(d->time - d->time_last_frame) / 1000;
		SDL_PumpEvents();
		handle_poll_event(d);
		handle_key_event(d);
		gravity(d);
		create_obj_raybox(d);
		process_mobs_gameplay(d);
		check_props_collect(d, d->props, &d->hud);
		raycast_thread_init(d);
		sprite_anim_gun(d);
		update_player_pos_mini_map(d, &d->map);
		print_player_look_vector(d, &d->map, d->rot);
		calc_n_disp_framerate(d);
		print_data2screen(d, &d->map, &d->hud);
	}
	return (0);
}