/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 04:27:20 by magostin          #+#    #+#             */
/*   Updated: 2020/10/10 17:30:27 by magostin         ###   ########.fr       */
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

/*
** Initialize the player's position and angle depending on NESW on the map
*/
void			ft_init_player(t_data *data, int x, int y)
{
	char		c;

	c = data->game[x][y];
	if (data->pars.player == 1 && ft_strchr("NSEW", c))
		aff_err("Multiples player on the map\n", data);
	if (c == 'N')
	{
		data->player.angle = -90;
		data->player.pos.x = y + 0.5;
		data->player.pos.y = x + 0.5;
		data->pars.player = 1;
	}
	if (c == 'S')
	{
		data->player.angle = 90;
		data->player.pos.x = y + 0.5;
		data->player.pos.y = x + 0.5;
		data->pars.player = 1;
	}
	if (c == 'E')
	{
		data->player.angle = 0;
		data->player.pos.x = y + 0.5;
		data->player.pos.y = x + 0.5;
		data->pars.player = 1;
	}
	if (c == 'W')
	{
		data->player.angle = 180;
		data->player.pos.x = y + 0.5;
		data->player.pos.y = x + 0.5;
		data->pars.player = 1;
	}
	data->player.angle = fix_angle(data->player.angle);
	return ;
}