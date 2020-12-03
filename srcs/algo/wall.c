/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 23:31:48 by magostin          #+#    #+#             */
/*   Updated: 2020/12/03 16:42:54 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point		wall_inter(t_block wall, t_point p, t_point a)
{
	return (intersect(
	p, a, point(wall.pos.x +
	(wall.texture == WEST), wall.pos.y + (wall.texture == NORTH)),
	point(wall.pos.x + (wall.texture != EAST),
	wall.pos.y + (wall.texture != SOUTH))));
}

t_point		change_wall_pos(t_block wall)
{
	if (wall.texture == NORTH)
		wall.pos.y--;
	if (wall.texture == SOUTH)
		wall.pos.y++;
	if (wall.texture == WEST)
		wall.pos.x--;
	if (wall.texture == EAST)
		wall.pos.x++;
	return (wall.pos);
}

double		wall_dir_return(int y, int x, t_point wall, t_point p_pos)
{
	return (fix_angle(rtoa(atan2(wall.y - p_pos.y + y, wall.x - p_pos.x + x))));
}

char		wall_dir(double f, t_point p_pos, t_point wall, t_data *data)
{
	if (data->player.dir == EAST)
	{
		if (f <= wall_dir_return(1, 1, wall, p_pos))
			return (EAST);
		return (SOUTH);
	}
	if (data->player.dir == SOUTH)
	{
		if (f <= wall_dir_return(1, 0, wall, p_pos))
			return (SOUTH);
		return (WEST);
	}
	if (data->player.dir == WEST)
	{
		if (f <= wall_dir_return(0, 0, wall, p_pos))
			return (WEST);
		return (NORTH);
	}
	if (data->player.dir == NORTH)
		if (f <= wall_dir_return(0, 1, wall, p_pos))
			return (NORTH);
	return (EAST);
}
