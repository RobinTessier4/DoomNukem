/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_icon2obj_type.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 21:37:20 by ahippoly          #+#    #+#             */
/*   Updated: 2020/07/06 14:04:47 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proto_global.h"

t_mob	add_mob_demon(t_data *d, SDL_Point pos)
{
	t_mob	mob;

	mob.life = AFRIT_PV;
	mob.dmg_per_hit = AFRIT_ATTACK;
	mob.attack_delay = AFRIT_ATTACK_DELAY;
	mob.attack_dist = AFRIT_ATTACK_RANGE;
	mob.speed = AFRIT_MOVE_SPEED;
	mob.aggro_range = AFRIT_AGGRO_RANGE;
	mob.size = AFRIT_SIZE;
	mob.pos.x = (float)pos.x / UNIT;
	mob.pos.y = (float)pos.y / UNIT;
	mob.sprite = sprite_init_afrit(d->sprite_img[SPRITE_ID_AFRIT]);
	mob.z_pos = 10;
	mob.z_size = 1;
	mob.attack_timer = 0;
	return (mob);
}

t_mob	add_mob_pyro(t_data *d, SDL_Point pos)
{
	t_mob	mob;

	mob.life = PYRO_PV;
	mob.dmg_per_hit = PYRO_ATTACK;
	mob.attack_delay = PYRO_ATTACK_DELAY;
	mob.attack_dist = PYRO_ATTACK_RANGE;
	mob.speed = PYRO_MOVE_SPEED;
	mob.aggro_range = PYRO_AGGRO_RANGE;
	mob.size = PYRO_SIZE;
	mob.pos.x = (float)pos.x / UNIT;
	mob.pos.y = (float)pos.y / UNIT;
	mob.sprite = sprite_init_pyro(d->sprite_img[SPRITE_ID_PYRO]);
	mob.z_pos = 10;
	mob.z_size = 1;
	mob.attack_timer = 0;
	return (mob);
}

t_props	add_prop_key(t_data *d, SDL_Point pos)
{
	t_props	prop;

	prop.pos.x = (float)pos.x / UNIT;
	prop.pos.y = (float)pos.y / UNIT;
	prop.size = KEY_SIZE;
	prop.collectable = KEY_COLLECTABLE;
	prop.can_collide = 0;
	prop.id = KEY_ITEM_ID;
	prop.text = &d->img[IMG_KEY];
	prop.z_pos = 10;
	return (prop);
}

t_props	add_prop_heal_pack(t_data *d, SDL_Point pos)
{
	t_props	prop;

	prop.pos.x = (float)pos.x / UNIT;
	prop.pos.y = (float)pos.y / UNIT;
	prop.size = HEAL_PACK_SIZE;
	prop.collectable = HEAL_PACK_COLLECTABLE;
	prop.can_collide = 0;
	prop.id = HEAL_PACK_ITEM_ID;
	prop.text = &d->img[IMG_HEAL_PACK];
	prop.z_pos = 10;
	return (prop);
}

t_props	add_prop_ship(t_data *d, SDL_Point pos)
{
	t_props prop;

	prop.pos.x = (float)pos.x / UNIT;
	prop.pos.y = (float)pos.y / UNIT;
	prop.size = SHIP_SIZE;
	prop.collectable = SHIP_COLLECTABLE;
	prop.can_collide = 0;
	prop.id = SHIP_ITEM_ID;
	prop.text = &d->img[IMG_SHIP];
	prop.z_pos = 10;
	return (prop);
}
