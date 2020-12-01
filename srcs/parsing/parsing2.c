/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 01:20:39 by magostin          #+#    #+#             */
/*   Updated: 2020/12/01 15:26:50 by magostin         ###   ########.fr       */
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
		if (ft_strlen(temp->line) > maxsize)
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
		aff_err("Map not valid!\n", data);
	a = -2;
	while (++a <= 1)
	{
		b = -2;
		while (++b <= 1)
			if (ft_strchr(" ",
			data->game[i + a][j + b]) && (!(a == 0 && b == 0)))
				aff_err("Map not valid!\n", data);
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

void	create_game(t_map *map, int nbr_line, t_data *data)
{
	int		line_size;
	int		i;
	t_map	*tmp;
	int		j;

	if (!(data->game = malloc(sizeof(char *) * (nbr_line + 1))))
		return ;
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
		free(tmp->line);
		free(tmp);
		i++;
	}
	data->game[i] = NULL;
	data->game_size.y = line_size;
	data->game_size.x = nbr_line;
	check_game(data);
}

int		ft_map(char *line, t_data *data)
{
	int			ret;
	int			nbr_line;
	char		*temp;
	t_map		*game;

	temp = line;
	nbr_line = 0;
	game = NULL;
	if (!(ft_check_line(temp)))
		return (0);
	ret = 1;
	while (ret != -1)
	{
		if (!(ft_check_line(temp)))
			break ;
		map_push_back(&game, new_map_line(temp));
		nbr_line++;
		ret = get_next_line(data->fd, &temp);
	}
	free(temp);
	create_game(game, nbr_line, data);
	return (1);
}
