/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 04:11:15 by magostin          #+#    #+#             */
/*   Updated: 2020/10/09 04:26:29 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** fill each wall with correct informations
*/
t_wall		*fill_wall(t_wall *walls, t_data *data)
{
	t_point		c;
	int			i;

	i = 0;
	c.y = -1;
	while (++c.y < data->game_size.x)
	{
		c.x = -1;
		while (++c.x < data->game_size.y)
		{
			if (data->game[(int)c.y][(int)c.x] == '1')
			{
				if ((int)c.y - 1 > 0 && data->game[(int)c.y - 1][(int)c.x] != '1')
					fill_wall_north(walls, &i, c, data);
				if ((int)c.x - 1 > 0 && data->game[(int)c.y][(int)c.x - 1] != '1')
					fill_wall_west(walls, &i, c, data);
				if ((int)c.y + 1 < data->game_size.x && data->game[(int)c.y + 1][(int)c.x] != '1')
					fill_wall_south(walls, &i, c, data);
				if ((int)c.x + 1 < data->game_size.y && data->game[(int)c.y][(int)c.x + 1] != '1')
					fill_wall_east(walls, &i, c, data);
			}
		}
	}
	data->n_objs = i;
	return (merge_wall(walls, data));
}

/*
** Fill all wall facing north
*/
void		fill_wall_north(t_wall *walls, int *i, t_point c, t_data *data)
{
	walls[*i].p[1].x = ((int)c.x);
	walls[*i].p[1].y = ((int)c.y);
	walls[*i].p[0].x = ((int)c.x + 1);
	walls[*i].p[0].y = ((int)c.y);
	walls[*i].color = NORTH;
	walls[*i].t = &data->no;
	walls[*i].used = 0;
	walls[*i].type = 0;
	*i += 1;
}

/*
** Fill all wall facing west
*/
void		fill_wall_west(t_wall *walls, int *i, t_point c, t_data *data)
{
	walls[*i].p[0].x = ((int)c.x);
	walls[*i].p[0].y = ((int)c.y);
	walls[*i].p[1].x = ((int)c.x);
	walls[*i].p[1].y = ((int)c.y + 1);
	walls[*i].color = WEST;
	walls[*i].t = &data->we;
	walls[*i].used = 0;
	walls[*i].type = 0;
	*i += 1;
}

/*
** Fill all wall facing south
*/
void		fill_wall_south(t_wall *walls, int *i, t_point c, t_data *data)
{
	walls[*i].p[0].x = ((int)c.x);
	walls[*i].p[0].y = ((int)c.y + 1);
	walls[*i].p[1].x = ((int)c.x + 1);
	walls[*i].p[1].y = ((int)c.y + 1);
	walls[*i].color = SOUTH;
	walls[*i].t = &data->so;
	walls[*i].used = 0;
	walls[*i].type = 0;
	*i += 1;
}

/*
** Fill all wall facing east
*/
void		fill_wall_east(t_wall *walls, int *i, t_point c, t_data *data)
{
	walls[*i].p[1].x = ((int)c.x + 1);
	walls[*i].p[1].y = ((int)c.y);
	walls[*i].p[0].x = ((int)c.x + 1);
	walls[*i].p[0].y = ((int)c.y + 1);
	walls[*i].color = EAST;
	walls[*i].t = &data->ea;
	walls[*i].used = 0;
	walls[*i].type = 0;
	*i += 1;
}