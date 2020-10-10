/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 04:06:54 by magostin          #+#    #+#             */
/*   Updated: 2020/10/10 04:59:58 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** Merge walls that are close and have the same direction
*/
t_wall		*merge_wall(t_wall *old_walls, t_data *data)
{
	int		i;
	int		j;
	int		k;
	int		compt;

	i = -1;
	compt = 0;
	while (++i < data->n_objs)
	{
		old_walls[i].size = 0;
		if (old_walls[i].used == 0)
		{
			k = i;
			j = -1;
			while (++j < data->n_objs)
				if (test_pts(old_walls, k, j))
				{
					old_walls[j].used = 1;
					k = j;
					old_walls[i].size++;
				}
			old_walls[i].p[1].x = old_walls[k].p[1].x;
			old_walls[i].p[1].y = old_walls[k].p[1].y;
			compt++;
		}
	}
	return (compact_walls(old_walls, compt, data));
}

/*
** Second part of Merge Walls
*/
t_wall		*compact_walls(t_wall *old_walls, int size, t_data *data)
{
	t_wall		*walls;
	int				i;
	int				j;

	if (!(walls = malloc(sizeof(t_wall) * (size))))
		return (0);
	i = -1;
	j = 0;
	while (++i < data->n_objs)
		if (old_walls[i].used == 0)
		{
			walls[j].p[0] = old_walls[i].p[0];
			walls[j].p[1] = old_walls[i].p[1];
			walls[j].color = old_walls[i].color;
			walls[j].size = old_walls[i].size;
			walls[j].t = old_walls[i].t;
			walls[j].used = 1;
			j++;
		}
	data->n_objs = j;
	free(old_walls);
	return (walls);
}

/*
** Create walls from char **map, used in raycasting
*/
t_wall		*create_wall(t_data *data)
{
	int			c[2];
	int			compteur;
	t_wall		*walls;

	c[0] = -1;
	compteur = 0;
	while (++c[0] < data->game_size.x)
	{
		c[1] = -1;
		while (++c[1] < data->game_size.y)
		{
			ft_init_player(data, c[0], c[1]);
			compteur += check_nei(c[0], c[1], data);
		}
	}
	if (!(walls = malloc(sizeof(t_wall) * (compteur + 1))))
		return (NULL);
	return (fill_wall(walls, data));
}