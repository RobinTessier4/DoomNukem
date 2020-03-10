/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:01:30 by apons             #+#    #+#             */
/*   Updated: 2020/02/07 22:41:48 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
** This function draws the walls the rays hit.
** The second 'if' statement allows reversing
** textures if seen from south or west.
*/

static double	get_where(t_enval *env)
{
	double wallwhere;

	if (env->ray.wallside == 0)
		wallwhere = env->player.pos.y + env->ray.perpwalldist * env->ray.dir.y;
	else
		wallwhere = env->player.pos.x + env->ray.perpwalldist * env->ray.dir.x;
	return (wallwhere - (int)wallwhere);
}

void			wall_draw(t_enval *env, int i, int t)
{
	int j;
	int d;

	env->ray.wallwhere = get_where(env);
	env->wt.x = (int)(env->ray.wallwhere * (double)env->wtex[t].img->w);
	if ((env->ray.wallside == 0 && env->ray.dir.x > 0)
			|| (env->ray.wallside == 1 && env->ray.dir.y < 0))
		env->wt.x = env->wtex[t].img->w - env->wt.x - 1;
	j = env->ray.walltop;
	while (j < env->ray.wallbot)
	{
		d = j * 256 - WIN_H * 128 + env->ray.height * 128;
		env->wt.y = ((d * env->wtex[t].img->h) / env->ray.height) / 256;
		put_pixel(env->sdl.screen, i, j,
		get_pixel_wall(env, t, env->wt.x, env->wt.y));
		j++;
	}
}