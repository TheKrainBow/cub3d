/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 01:19:38 by magostin          #+#    #+#             */
/*   Updated: 2020/12/02 23:38:11 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	if (!(game = malloc(sizeof(t_map))))
		return (NULL);
	game->line = line;
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
