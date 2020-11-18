/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 04:27:20 by magostin          #+#    #+#             */
/*   Updated: 2020/11/11 18:22:31 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** Count how many neighbour the wall in x and y have
*/
int			check_nei(int x, int y, t_data *data)
{
	int compteur;

	compteur = 0;
	if (data->game[x][y] == '1')
	{
		if (x - 1 > 0 && data->game[x - 1][y] != '1')
			compteur++;
		if (y - 1 > 0 && data->game[x][y - 1] != '1')
			compteur++;
		if (y + 1 < data->game_size.y && data->game[x][y + 1] != '1')
			compteur++;
		if (x + 1 < data->game_size.x && data->game[x + 1][y] != '1')
			compteur++;
	}
	return (compteur);
}

/*
** Test if walls are neighbour and have the same direction
*/
int			test_pts(t_wall *old_objs, int i, int j)
{
	if (old_objs[i].color == old_objs[j].color
	&& ((old_objs[i].p[1].x == old_objs[j].p[0].x && old_objs[i].p[1].y == old_objs[j].p[0].y)))
		return (1);
	return (0);
}