/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 01:33:06 by magostin          #+#    #+#             */
/*   Updated: 2020/12/02 23:40:02 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	free_map(t_data *data)
{
	t_map *map;
	t_map *tmp;

	map = data->pars.game;
	while (map)
	{
		tmp = map->next;
		free(map->line);
		free(map);
		map = tmp;
	}
}

void	ft_map(char *line, t_data *data)
{
	map_push_back(&data->pars.game, new_map_line(line));
	data->pars.nbr_line++;
}

int		detect_param(char **line)
{
	if (ft_check_line(*line))
		return (3);
	while (ft_whitespace((**line)) && (**line))
		(*line)++;
	if ((**line) == 0)
		return (4);
	if ((**line) == 'R' && ft_whitespace(*(*line + 1)))
		return (0);
	if ((ft_strstr(*line, "NO") == *line
	|| ft_strstr(*line, "SO") == *line
	|| ft_strstr(*line, "EA") == *line
	|| ft_strstr(*line, "WE") == *line) && ft_whitespace(*(*line + 2)))
		return (1);
	if ((**line) == 'S' && ft_whitespace(*(*line + 1)))
		return (1);
	if (ft_strchr("FC", **line) && ft_whitespace(*(*line + 1)))
		return (2);
	return (4);
}
