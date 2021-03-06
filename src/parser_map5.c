/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 15:32:51 by robin             #+#    #+#             */
/*   Updated: 2020/07/09 15:41:27 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proto_global.h"

static void		set_wall(t_wall *wall)
{
	wall->length = hypot(wall->p2.x - wall->p1.x, wall->p2.y - wall->p1.y);
	wall->rotation = calc_line_angle(wall->p1, wall->p2);
	wall->alpha = (float)(100 - wall->transparency) / 100;
	wall->p1_z_start = (float)wall->p1_height.start / UNIT;
	wall->p1_z_size = (float)(wall->p1_height.end - wall->p1_height.start)
		/ UNIT;
	wall->p2_z_start = (float)wall->p2_height.start / UNIT;
	wall->p2_z_size = (float)(wall->p2_height.end - wall->p2_height.start)
		/ UNIT;
	wall->z_text_offset = 0;
}

int				read_wall_list(int fd, t_map_data *map)
{
	char	*line;
	int		i;

	if (get_next_line(fd, &line) == 1)
	{
		if ((read_param(line, "WALL_COUNT", &map->wall_count)))
			return (-1);
	}
	else
		return (-1);
	free(line);
	if (!(map->wall_list = (t_wall*)malloc(sizeof(t_wall) * map->wall_count)))
		return (-1);
	i = 0;
	while (get_next_line(fd, &line) == 1 && *line != '\0' &&
			i < map->wall_count)
	{
		if ((read_wall(line, &map->wall_list[i++])) < 0)
			return (-1);
		free(line);
	}
	free(line);
	return (0);
}

int				read_wall(char *line, t_wall *wall)
{
	if ((read_param_wall(line, wall)) < 0)
		return (-1);
	set_wall(wall);
	return (0);
}

int				read_room(char *line, t_room *room)
{
	int error;

	error = 0;
	error += read_param(line, "id", &room->room_id);
	error += read_param(line, "nb_wall", &room->nb_wall);
	error += read_param(line, "wall_ref_range", &room->wall_ref.start);
	error += read_param(line, "height", &room->height.start);
	error += read_param(line, "floor_text", &room->floor_text);
	if (error > 0)
	{
		ft_putendl("error while assigning value to room on map reader\n");
		return (-1);
	}
	room->z_ground = (float)room->height.start / UNIT;
	room->z_ceil = (float)room->height.end / UNIT;
	return (0);
}
