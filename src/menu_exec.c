/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 14:33:14 by robin             #+#    #+#             */
/*   Updated: 2020/07/09 14:34:52 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proto_global.h"
#include <errno.h>

int			is_mouse_on_target(t_data *d, SDL_Rect pos)
{
	if (d->e.motion.x > pos.x && d->e.motion.x < pos.x + pos.w
		&& d->e.motion.y > pos.y && d->e.motion.y < pos.y + pos.h)
	{
		if (d->e.type == SDL_MOUSEBUTTONDOWN)
			if (d->e.button.button == SDL_BUTTON_LEFT)
				return (1);
	}
	return (0);
}

int			catch_btn_event(t_data *d)
{
	if (is_mouse_on_target(d, set_sdl_rect(WIN_SIZE_X / 2, WIN_SIZE_Y / 3,
			200, 50)) == 1)
	{
		if (access("doom-nukem", X_OK))
			exit_game(d, "error : something went wrong with read()!");
		else
			d->run_game = GAME;
	}
	else if (is_mouse_on_target(d, set_sdl_rect(WIN_SIZE_X / 2, WIN_SIZE_Y / 3
				+ 100, 200, 50)) == 1)
	{
		if (access("./editor", X_OK))
			exit_game(d, "error : filed to access ./editor");
		else
			d->run_game = EDITOR;
	}
	else if (is_mouse_on_target(d, set_sdl_rect(WIN_SIZE_X / 2, WIN_SIZE_Y / 3
				+ 200, 200, 50)) == 1)
		exit_game(d, "exiting...");
	return (0);
}
