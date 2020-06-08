/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apons <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 10:51:21 by apons             #+#    #+#             */
/*   Updated: 2020/06/08 10:11:25 by apons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
** Calculates vertical offset (offset->y) according to reload time.
*/

static void	get_offset_vertical(t_enval *env, t_intxy *offset, t_intxy *id)
{
	double percentage;
	if (env->game.pc.equip.weapon_state == WEAPON_STATE_RELOADING)
	{
		percentage = (double)env->game.pc.equip.reload_cd
			/ (double)env->game.pc.arsenal[id->x].clip.reload;
		if (percentage >= 0.75)
			percentage = 1 - percentage;
		else if (percentage >= 0.25)
			percentage = 1;
	}
	else
		percentage = 0;
	env->game.pc.equip.off_vert.current = percentage * 1500;
	offset->y = 20 + env->user.bobbing.y + env->game.pc.equip.off_vert.current;
}

/*
** Chooses the right weapon sprite to apply and uses
** functions from get_id_arsenal.c if necessary.
*/

static int	get_id_weapon_texture(t_enval *env, t_intxy *id)
{
	if (env->game.pc.equip.weapon_state == WEAPON_STATE_READY
	|| env->game.pc.equip.weapon_state == WEAPON_STATE_RELOADING)		
		return (0);
	if (id->x <= 1)
	{
		return (get_id_arsenal_s(id->x,
		env->game.pc.arsenal[id->x].attack.delay.current,
		env->game.pc.arsenal[id->x].attack.delay.max,
		env->game.pc.fist_side));
	}
	if (id->x <= 3)
	{
		return (get_id_arsenal_xl(id->x,
		env->game.pc.arsenal[id->x].attack.delay.current,
		env->game.pc.arsenal[id->x].attack.delay.max));
	}
	return (get_id_arsenal_bfg(env->game.pc.arsenal[4].attack.delay.current,
	env->game.pc.arsenal[4].attack.delay.max, env->game.pc.equip.weapon_state));
}

/*
** Retrieves or calculates variables for the weapon_draw function.
*/

static void	get_draw_vars(t_enval *env, t_intxy *id,
	t_intxy *offset, Uint32 *z_pixel)
{
	id->x = env->game.pc.equip.current;
	offset->x = env->game.pc.arsenal[id->x].offset + env->user.bobbing.x;
	id->y = get_id_weapon_texture(env, id);
	get_offset_vertical(env, offset, id);
	*z_pixel = get_pixel_weapon(env, *id, 0, 0);
}

/*
** Draws the weapon texture, excludes the pixels that have the same color
** as the z-pixel which tells what pixel is not part of the weapon.
*/

void		weapon_draw(t_enval *env)
{
	t_intxy		id;
	t_intxy		offset;
	t_intxy		c;
	uint32_t	zpixel;
	uint32_t	pixel;

	get_draw_vars(env, &id, &offset, &zpixel);
	c.x = -1;
	while (++c.x < env->wptex[id.x][id.y].img->w * 3)
	{
		c.y = -1;
while (++c.y < env->wptex[id.x][id.y].img->h * 3)
		{
			pixel = get_pixel_weapon(env, id, c.x / 3, c.y / 3);
			if (pixel == zpixel)
				continue;
			put_pixel(env->sdl.screen,
			(WIN_W / 2) - (env->wptex[id.x][id.y].img->w * 3 / 2)
			+ c.x + offset.x,
			(WIN_H - env->wptex[id.x][id.y].img->h * 3)
			+ c.y + offset.y, pixel);
		}
	}
}
