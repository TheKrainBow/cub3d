/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 12:03:50 by magostin          #+#    #+#             */
/*   Updated: 2020/12/01 13:00:27 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	color(char *line, t_data *data)
{
	if (*line == 'F' && data->pars.f != 0)
		aff_err("Multiple definition of F\n", data);
	if (*line == 'C' && data->pars.c != 0)
		aff_err("Multiple definition of C\n", data);
	if (*line == 'F')
	{
		line++;
		line = ft_strtrim(line, " ");
		fill_color(line, 1, data);
		data->pars.f = 1;
	}
	if (*line == 'C')
	{
		line++;
		line = ft_strtrim(line, " ");
		fill_color(line, 0, data);
		data->pars.c = 1;
	}
}

int		aff_err(char *str, t_data *data)
{
	(void)data;
	printf("Error.\n%s", str);
	exit(1);
}

int		redirect_function(char *line, t_data *data)
{
	void		(*redirect[10])(char *, t_data *);
	int			param;

	redirect[0] = reso;
	redirect[1] = texture;
	redirect[2] = color;
	param = detect_param(&line, data);
	if (param >= 3)
		return (0);
	redirect[param](line, data);
	return (0);
}

void	check_parsing(t_data *data)
{
	int			i;

	i = -1;
	while (++i < 5)
		if (data->pars.t[i] == 0)
			aff_err("Some textures are missing!\n", data);
	ft_init_player(data);
	if (data->pars.f == 0)
		aff_err("No floor color\n", data);
	if (data->pars.c == 0)
		aff_err("No ceiling color\n", data);
	if (data->pars.r == 0)
		aff_err("No resolution\n", data);
	if (data->pars.player == 0)
		aff_err("No player on the map\n", data);
}

int		parsing(t_data *data)
{
	char		*line;
	char		*temp;
	int			ret;

	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(data->fd, &line);
		temp = line;
		if (line && redirect_function(line, data))
		{
			free(temp);
			return (0);
		}
		free(temp);
	}
	check_parsing(data);
	data->r.x = data->r.x > data->max_x ? data->max_x : data->r.x;
	data->r.y = data->r.y > data->max_y ? data->max_y : data->r.y;
	return (1);
}
