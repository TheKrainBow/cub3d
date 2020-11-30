/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 01:19:38 by magostin          #+#    #+#             */
/*   Updated: 2020/11/30 01:20:32 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		ft_whitespace(char c)
{
	if (c == '\f' || c == '\t' || c == '\n'
	|| c == '\r' || c == '\v' || c == ' ')
		return (1);
	return (0);
}

int		is_nb(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

t_map	*new_map_line(char *line)
{
	t_map		*game;
	int			i;

	if (!(game = malloc(sizeof(t_map)))
	|| !(game->line = malloc(sizeof(char) * (ft_strlen(line) + 1))))
		return (NULL);
	i = -1;
	while (line && line[++i])
		game->line[i] = line[i];
	game->line[i] = 0;
	game->next = NULL;
	return (game);
}

void	map_push_back(t_map **first, t_map *new)
{
	t_map	*temp;

	if (!first || !new)
		return ;
	if (!(*first))
	{
		*first = new;
		return ;
	}
	temp = *first;
	while (temp && temp->next)
		temp = temp->next;
	temp->next = new;
}

int		ft_check_line(char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] != '1')
		return (0);
	while (line[i])
	{
		if (!ft_strchr("0123NSEW ", line[i]))
			return (0);
		i++;
	}
	return (1);
}
