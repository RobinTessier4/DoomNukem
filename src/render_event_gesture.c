#include "global_header.h"
#include "render.h"
#include "editor.h"
#include "img_file.h"


void handle_key_event(t_data *d, t_map_data *map)
{
    d->clavier = SDL_GetKeyboardState(NULL);
    if (d->clavier[SDL_SCANCODE_E])
        d->rot += ROT_STEP;
    if (d->clavier[SDL_SCANCODE_Q])
        d->rot -= ROT_STEP;
	d->rot_calc = calc_sin_cos_rot(d->rot);
    if (d->clavier[SDL_SCANCODE_D])
        move_with_collide(d, &d->player_pos, (t_rot){d->rot + M_PI_2, cos(d->rot + M_PI_2), sin(d->rot + M_PI_2)}, MOVE_STEP * d->speed_modifier);
        //move_attempt(&d->player_pos, MOVE_STEP * d->speed_modifier, d->rot_calc + 1);
    if (d->clavier[SDL_SCANCODE_A])
        move_with_collide(d, &d->player_pos, (t_rot){d->rot - M_PI_2, cos(d->rot - M_PI_2), sin(d->rot - M_PI_2)}, MOVE_STEP * d->speed_modifier);
    if (d->clavier[SDL_SCANCODE_W])
        move_with_collide(d, &d->player_pos, d->rot_calc, MOVE_STEP * d->speed_modifier);
    if (d->clavier[SDL_SCANCODE_S])
        move_with_collide(d, &d->player_pos, (t_rot){d->rot + M_PI, cos(d->rot + M_PI), sin(d->rot + M_PI)}, MOVE_STEP * d->speed_modifier);
    if (d->clavier[SDL_SCANCODE_R])
        d->z_offset += 0.05;
    if (d->clavier[SDL_SCANCODE_F])
        d->z_offset -= 0.05;
    if (d->clavier[SDL_SCANCODE_ESCAPE])
        d->quit = 1;

	//debug
		if (d->clavier[SDL_SCANCODE_C])
			raycast_thread_init(d);
	//printf("player rot = %f\n", fabs(fmod(d->rot, 4)));
}

void inc_fov(t_data *d, float inc)
{
	d->fov_rad += inc * M_PI_2;
	d->fov += inc;
	printf("fov = %f\n", d->fov);
}

void handle_poll_event(t_data *d, t_map_data *map)
{
    while (SDL_PollEvent(&d->e))
    {
        if (d->e.type == SDL_WINDOWEVENT)
        {
            if (d->e.window.event == SDL_WINDOWEVENT_CLOSE)
                d->quit = 1;
        }
        if (d->e.type == SDL_MOUSEMOTION)
        {
            //printf("mouse x,y = %i,%i, mouse rel = %i,%i\n", d->e.motion.x, d->e.motion.y, d->e.motion.xrel, d->e.motion.yrel);
            d->rot += MOUSE_SENS * d->e.motion.xrel * M_PI_2;
            d->screen_height = HALF_WIN_SIZE_Y + (HALF_WIN_SIZE_Y - d->e.motion.y) * Y_VIEW_RANGE;
			move_z_grabbed_wall(d, - (float)d->e.motion.yrel * MOVE_WALL_Z_SPEED / WIN_SIZE_Y);
        }
        if (d->e.type == SDL_KEYDOWN)
        {
            if (d->e.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
            {
                printf("running\n");
                d->speed_modifier += 1;
            }
            if (d->e.key.keysym.scancode == SDL_SCANCODE_LCTRL)
            {
                printf("crouch\n");
                d->speed_modifier -= 0.5;
                d->z_offset -= PLAYER_HEIGHT / 2;
            }
            if (d->clavier[SDL_SCANCODE_SPACE])
                d->z_force = 0.07;
			//debug
			if (d->clavier[SDL_SCANCODE_G])
               	rot_grabbed_wall(d, 0.05 * M_PI_2, 0);
			if (d->clavier[SDL_SCANCODE_H])
               	rot_grabbed_wall(d, -0.05 * M_PI_2, 0);
			if (d->clavier[SDL_SCANCODE_J])
               	inc_fov(d, 0.05);
			if (d->clavier[SDL_SCANCODE_K])
               	inc_fov(d, -0.05);
			if (d->clavier[SDL_SCANCODE_V])
				print_floor(d);

        }
        if (d->e.type == SDL_KEYUP)
        {
            if (d->e.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
            {
                printf("no longer running\n");
                d->speed_modifier -= 1;
            }
            if (d->e.key.keysym.scancode == SDL_SCANCODE_LCTRL)
            {
                printf("no longer crouch\n");
				d->speed_modifier += 0.5;
                d->z_offset += PLAYER_HEIGHT / 2;
            }
            if (d->e.key.keysym.scancode == SDL_SCANCODE_Z)
            {
				// printf("checking room\n");
				// if (check_player_room(d, d->player_pos) > -1)
				// 	printf("Is in room\n");
				//print_wall(d, d->map.wall_list[0]);
				init_floors(d);
				raycast_screen(d, (t_range){400, 401}, d->rot, 0);
                // draw_vertical_line(d, 500, check_intersect_with_all_wall(d, d->player_pos, d->rot, d->rot));
                // printf("scale_z to wall test = %f\n", check_intersect_with_all_wall(d, d->player_pos, d->rot, d->rot).scale_z);
                // printf("d->rot = %f\n", d->rot);
            }
                
            if (d->e.key.keysym.scancode == SDL_SCANCODE_X)
            {
				if (d->grabbed_wall == NULL)
                	if (grab_wall(d, d->player_pos, d->rot_calc))
						printf("grabbed wall\n");
					else
						printf("attempt grab fail\n");
				else
				{
					d->grabbed_wall = NULL;
					printf("no longer grab wall\n");
				}
            }
        }
    }
}