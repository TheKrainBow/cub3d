/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 01:33:06 by magostin          #+#    #+#             */
/*   Updated: 2020/11/30 01:37:39 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_create_player(t_data *data, int x, int y, char c)
{
	if (data->pars.player != 0)
		aff_err("Multiple player definition.", data);
	data->player.pos.x = x + 0.5;
	data->player.pos.y = y + 0.5;
	if (c == 'N')
		data->player.angle = 270;
	if (c == 'S')
		data->player.angle = 90;
	if (c == 'E')
		data->player.angle = 0;
	if (c == 'W')
		data->player.angle = 180;
	data->pars.player = 1;
}

void	ft_init_player(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (++i < data->game_size.x)
	{
		j = -1;
		while (++j < data->game_size.y)
		{
			if (ft_strchr("NSWE", data->game[i][j]))
				ft_create_player(data, j, i, data->game[i][j]);
		}
	}
}
