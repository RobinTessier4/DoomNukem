/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahippoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:48:11 by ahippoly          #+#    #+#             */
/*   Updated: 2019/10/15 16:44:56 by ahippoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global_header.h"
#include "editor.h"

double calc_a(t_point p1, t_point p2)
{
	return ((p2.y - p1.y) / (p2.x - p1.x));
}

double calc_b(t_point p1, double a)
{
	return (p1.y - p1.x * a);
}

t_point calc_intersect(double a1, double b1, double a2, double b2)
{
	t_point inter;

	inter.x = (b2 - b1) / (a1  - a2);
	inter.y = a1 * inter.x + b1;
	return (inter);
}

t_point default_case(t_point p1, t_point p2, t_point p3, t_point p4)
{
	double a1;
	double a2;
	double b1;
	double b2;
	t_point inter;

	a1 = (p2.y - p1.y) / (p2.x - p1.x);
	b1 = p1.y - p1.x * a1;

	a2 = (p4.y - p3.y) / (p4.x - p3.x);
	b2 = p3.y - p3.x * a2;
	
	if (a1 == a2 && b1 == b2 
	&& ((p1.x > p3.x && p1.x < p4.x)
	|| (p2.x > p3.x && p2.x < p4.x)
	|| (p3.x > p1.x - INTER_TOLERANCE && p3.x < p2.x - INTER_TOLERANCE))
	)
		return (create_t_point(-41, -41));
	inter.x = (b2 - b1) / (a1  - a2);
	//printf("inter.x = %f, max x = %f, min x = %f\n", inter.x, ft_fmax(p2.x, p1.x), ft_fmin(p2.x, p1.x));
	if (inter.x < p2.x - INTER_TOLERANCE && inter.x > p1.x + INTER_TOLERANCE
		&& inter.x < p4.x - INTER_TOLERANCE && inter.x > p3.x + INTER_TOLERANCE
		&& (a1 != a2))
		inter.y = a1 * inter.x + b1;
	else
		inter = create_t_point(-42, -42);
	return (inter);
}

t_point first_segment_vertical_case(t_point p1, t_point p2, t_point p3, t_point p4)
{
	double a2;
	double b2;
	t_point inter;

	a2 = (p4.y - p3.y) / (p4.x - p3.x);
	b2 = p3.y - p3.x * a2;
	inter.x = p1.x;
	inter.y = a2 * inter.x + b2;
	//printf("inter.y = %f, max x = %f, min x = %f\n", inter.y, ft_fmax(p2.y, p1.y), ft_fmin(p2.y, p1.y));
	if (inter.y > ft_max(p2.y, p1.y) - INTER_TOLERANCE || inter.y < ft_min(p1.y, p2.y) + INTER_TOLERANCE
		|| inter.x > p4.x - INTER_TOLERANCE || inter.x < p3.x + INTER_TOLERANCE)
	{
		inter.x = - 42;
		inter.y = - 42;
	}
	return (inter);
}

t_point convert_sdlpoint2tpoint(SDL_Point point)
{
	t_point new_point;

	new_point.x = point.x;
	new_point.y = point.y;
	return (new_point);
}

t_point find_intersect(t_point p1, t_point p2, t_point p3, t_point p4)
{
	t_point inter;

	sort_t_point_by_x(&p1, &p2);
	sort_t_point_by_x(&p3, &p4);
	if (p2.x - p1.x != 0 && p4.x - p3.x != 0)
		inter = default_case(p1, p2, p3, p4);
	else if (p4.x - p3.x != 0)
		inter = first_segment_vertical_case(p1, p2, p3, p4);
	else if (p2.x - p1.x != 0)
		inter = first_segment_vertical_case(p3, p4, p1, p2);
	else
	{
		inter.x = - 42;
		inter.y = - 42;
	}
	//printf("a1 = %f, b1 = %f\na2 = %f, b2 = %f\n",a1, b1, a2, b2);
	//printf("sin_rot = %f, cos_rot = %f\n", sin_rot, cos_rot);
	//printf("inter.x = %f, inter.y = %f\n", inter.x, inter.y);
	return (inter);
}

t_point segment_intersect(SDL_Point point1, SDL_Point point2, SDL_Point point3, SDL_Point point4)
{
	t_point inter;
	t_point p1;
	t_point p2;
	t_point p3;
	t_point p4;

	p1 = convert_sdlpoint2tpoint(point1);
	p2 = convert_sdlpoint2tpoint(point2);
	p3 = convert_sdlpoint2tpoint(point3);
	p4 = convert_sdlpoint2tpoint(point4);
	return (find_intersect(p1, p2, p3, p4));
}

t_point inter_with_dir(t_point pos, double rot, t_point p3, t_point p4)
{
	t_point p2;

	p2.x = pos.x + cos(rot * M_PI_2) * 30; 
	p2.y = pos.y + sin(rot * M_PI_2) * 30;
	return (find_intersect(pos, p2, p3, p4));
}

t_point	line_intersect(t_point pos, double rot, t_point p1, t_point p2)
{
	double a1;
	double b1;
	double a2;
	double b2;
	t_point inter;

	sort_t_point_by_x(&p1, &p2);
	a1 = sin(rot * M_PI_2) / cos(rot * M_PI_2);
	printf("a1 = %f\n",a1);
	b1 = calc_b(pos, a1);
	a2 = calc_a(p1, p2);
	b2 = calc_b(p1, a2);
	if (a1 == a2)
		return (create_t_point(-42, -42));
	inter = calc_intersect(a1, b1 , a2, b2);
	if (inter.x < p1.x || inter.x > p2.x)
		return (create_t_point(-42, -42));
	return (inter);
}