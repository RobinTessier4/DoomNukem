/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_mobs2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahippoly <ahippoly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:26:26 by ahippoly          #+#    #+#             */
/*   Updated: 2020/07/17 03:51:47 by ahippoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proto_global.h"

void	kill_mob(t_param param)
{
	t_data *d;

	d = param.d;
	del_obj(d->obj_list, &d->nb_obj, param.mob->obj_ref);
	del_from_array(d->mobs, &d->nb_mob, param.mob, sizeof(t_mob));
	ref_origin(d->mobs, d->nb_mob, TYPE_MOB);
}

void	change_mob_life(t_data *d, t_mob *mob, int damage)
{
	mob->life -= damage;
	if (mob->life < 1 && mob->life > -9999)
	{
		mob->life = -9999;
		mob->sprite.idle_anim = -1;
		load_anim(&mob->sprite, d->time, ANIM_MOB_DEATH);
	}
}

void	change_player_life(t_data *d, int *hp, int damage)
{
	*hp -= damage;
	if (*hp < 1)
		d->run_game = GAMEOVER;
}

void	check_mob_attack(t_param param)
{
	float dist;

	dist = get_dist(param.d->player_pos, param.mob->obj_ref->pos);
	if (dist < param.mob->attack_dist + 1)
		change_player_life(param.d, &param.d->hud.hp, param.mob->dmg_per_hit);
}

void	move_mobs_in_range(t_data *d, t_mob *mobs, int nb_mob)
{
	int		i;
	t_mob	*mob;
	float	dist;

	i = 0;
	while (i < nb_mob)
	{
		mob = &mobs[i++];
		if (mob->life < -9998)
			continue ;
		dist = get_dist(mob->obj_ref->pos, d->player_pos);
		if (dist < mob->aggro_range && dist > MOB_MIN_RANGE)
			move_with_collide(d, mob->obj_ref,
				get_angle(mob->obj_ref->pos, d->player_pos), mob->speed);
		if (dist < mob->attack_dist && d->time
			- mob->attack_timer > mob->attack_delay)
		{
			mob->attack_timer = d->time;
			set_sprite_callback(&mob->sprite, check_mob_attack,
				(t_param){d, mob});
			load_anim(&mob->sprite, d->time, ANIM_MOB_MELEE);
		}
	}
}
