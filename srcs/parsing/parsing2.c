/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 01:20:39 by magostin          #+#    #+#             */
/*   Updated: 2020/12/03 15:52:35 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		longest_line(t_map *game)
{
	t_map		*temp;
	int			maxsize;

	maxsize = 0;
	temp = game;
	while (temp)
	{
		if (temp->line && ft_strlen(temp->line) > maxsize)
			maxsize = ft_strlen(temp->line);
		temp = temp->next;
	}
	return (maxsize);
}

void	check_surround(int i, int j, t_data *data)
{
	int		a;
	int		b;

	if (!(data->game[i][j] == '0' || ft_strchr("NSWE2", data->game[i][j])))
		return ;
	if (i == 0 || j == 0 || i == data->game_size.x - 1
	|| j == data->game_size.y - 1)
	{
		free_map(data);
		aff_err("Map not valid!\n", data);
	}
	a = -2;
	while (++a <= 1)
	{
		b = -2;
		while (++b <= 1)
			if (ft_strchr(" ",
			data->game[i + a][j + b]) && (!(a == 0 && b == 0)))
			{
				free_map(data);
				aff_err("Map not valid!\n", data);
			}
	}
}

void	check_game(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (++i < data->game_size.x)
	{
		j = -1;
		while (++j < data->game_size.y)
			check_surround(i, j, data);
	}
}

void	create_game2(int line_size, int i, t_data *data)
{
	int		j;
	t_map	*map;
	t_map	*tmp;

	map = data->pars.game;
	line_size = longest_line(map);
	i = 0;
	while (map)
	{
		if (!(data->game[i] = malloc(sizeof(char) * (line_size + 1))))
			return ;
		j = -1;
		while (map->line[++j] && j < line_size)
			data->game[i][j] = map->line[j];
		j--;
		while (++j < line_size)
			data->game[i][j] = ' ';
		data->game[i][j] = 0;
		tmp = map;
		map = map->next;
		i++;
	}
	data->game[i] = NULL;
	data->game_size.y = line_size;
	data->game_size.x = data->pars.nbr_line;
}

void	create_game(t_data *data)
{
	if (!(data->game = malloc(sizeof(char *) * (data->pars.nbr_line + 1))))
		return ;
	create_game2(0, 0, data);
	check_game(data);
	free_map(data);
	check_parsing(data);
}
