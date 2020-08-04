/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 12:03:50 by magostin          #+#    #+#             */
/*   Updated: 2020/07/18 22:51:02 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int			ft_whitespace(char c)
{
	if (c == '\f' || c == '\t' || c == '\n'
	|| c == '\r' || c == '\v' || c == ' ')
		return (1);
	return (0);
}

int			is_nb(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int			detect_param(char (**line))
{
	while (ft_whitespace((**line)) && (**line))
		(*line)++;
	if ((**line) == 0)
		return (0);
	if ((**line) == 'R' && ft_whitespace(*(*line + 1)))
		return (1);
	if ((**line) == 'N' && *(*line + 1) == 'O' && ft_whitespace(*(*line + 2)))
		return (2);
	if ((**line) == 'S' && *(*line + 1) == 'O' && ft_whitespace(*(*line + 2)))
		return (3);
	if ((**line) == 'W' && *(*line + 1) == 'E' && ft_whitespace(*(*line + 2)))
		return (4);
	if ((**line) == 'E' && *(*line + 1) == 'A' && ft_whitespace(*(*line + 2)))
		return (5);
	if ((**line) == 'S' && ft_whitespace(*(*line + 1)))
		return (6);
	if ((**line) == 'F' && ft_whitespace(*(*line + 1)))
		return (7);
	if ((**line) == 'C' && ft_whitespace(*(*line + 1)))
		return (8);
	return (8);
}

int		reso(char *line, t_data *data)
{
	line++;
	while (ft_whitespace(*line) && (*line))
		line++;
	if (!is_nb(*line))
		return (ERR_RES);
	data->r.x = ft_atoi(line);
	while (is_nb(*line) && (*line))
		line++;
	if (!ft_whitespace(*line))
		return (ERR_RES);
	while (ft_whitespace(*line) && (*line))
		line++;
	if (!is_nb(*line))
		return (ERR_RES);
	data->r.y = ft_atoi(line);
	while (is_nb(*line) && (*line))
		line++;
	if (!ft_whitespace(*line) && (*line))
		return (ERR_RES);
	while (ft_whitespace(*line) && (*line))
		line++;
	if (*line)
		return (ERR_RES);
	return (NO_ERR);
}

int		text_no(char *line, t_data *data)
{
	char	*temp;
	int		trash;

	line += 2;
	if (!ft_whitespace(*line) && (*line))
		return (ERR_NO);
	while (ft_whitespace(*line) && (*line))
		line++;
	temp = line;
	while (!ft_whitespace(*line) && (*line))
		line++;
	if (!ft_whitespace(*line) && (*line))
		return (ERR_NO);
	if (*line)
	{
		*line = 0;
		line++;
		while (ft_whitespace(*line) && (*line))
			line++;
		if (*line)
			return (ERR_NO);
	}
	data->no.ptr = mlx_xpm_file_to_image(data->mlx, temp, &(data->no.wth), &(data->no.lth));
	if (data->no.ptr == NULL)
		return (ERR_NO);
	data->no.tab = (unsigned int *)mlx_get_data_addr(data->no.ptr, &trash, &trash, &trash);
	return (NO_ERR);
}

int		text_so(char *line, t_data *data)
{
	char	*temp;
	int		trash;

	line += 2;
	if (!ft_whitespace(*line) && (*line))
		return (ERR_SO);
	while (ft_whitespace(*line) && (*line))
		line++;
	temp = line;
	while (!ft_whitespace(*line) && (*line))
		line++;
	if (!ft_whitespace(*line) && (*line))
		return (ERR_SO);
	if (*line)
	{
		*line = 0;
		line++;
		while (ft_whitespace(*line) && (*line))
			line++;
		if (*line)
			return (ERR_SO);
	}
	data->so.ptr = mlx_xpm_file_to_image(data->mlx, temp, &(data->so.wth), &(data->so.lth));
	if (data->so.ptr == NULL)
		return (ERR_SO);
	data->so.tab = (unsigned int *)mlx_get_data_addr(data->so.ptr, &trash, &trash, &trash);
	return (NO_ERR);
}

int		text_we(char *line, t_data *data)
{
	char	*temp;
	int		trash;

	line += 2;
	if (!ft_whitespace(*line) && (*line))
		return (ERR_WE);
	while (ft_whitespace(*line) && (*line))
		line++;
	temp = line;
	while (!ft_whitespace(*line) && (*line))
		line++;
	if (!ft_whitespace(*line) && (*line))
		return (ERR_WE);
	if (*line)
	{
		*line = 0;
		line++;
		while (ft_whitespace(*line) && (*line))
			line++;
		if (*line)
			return (ERR_WE);
	}
	data->we.ptr = mlx_xpm_file_to_image(data->mlx, temp, &(data->we.wth), &(data->we.lth));
	if (data->we.ptr == NULL)
		return (ERR_WE);
	data->we.tab = (unsigned int *)mlx_get_data_addr(data->we.ptr, &trash, &trash, &trash);
	return (NO_ERR);
}

int		text_ea(char *line, t_data *data)
{
	char	*temp;
	int		trash;

	line += 2;
	if (!ft_whitespace(*line) && (*line))
		return (ERR_EA);
	while (ft_whitespace(*line) && (*line))
		line++;
	temp = line;
	while (!ft_whitespace(*line) && (*line))
		line++;
	if (!ft_whitespace(*line) && (*line))
		return (ERR_EA);
	if (*line)
	{
		*line = 0;
		line++;
		while (ft_whitespace(*line) && (*line))
			line++;
		if (*line)
			return (ERR_EA);
	}
	data->ea.ptr = mlx_xpm_file_to_image(data->mlx, temp, &(data->ea.wth), &(data->ea.lth));
	if (data->ea.ptr == NULL)
		return (ERR_EA);
	data->ea.tab = (unsigned int *)mlx_get_data_addr(data->ea.ptr, &trash, &trash, &trash);
	return (NO_ERR);
}

int		text_sp(char *line, t_data *data)
{
	return (0);
}

int		color_f(char *line, t_data *data)
{
	char			value[7];
	int				temp;
	unsigned int	res;
	int				i;

	line++;
	if (!ft_whitespace(*line) && (*line))
		return (ERR_F);
	while (ft_whitespace(*line) && (*line))
		line++;
	i = -1;
	while (++i < 3)
	{
		temp = ft_atoi(line);
		while (is_nb(*line) && (*line))
			line++;
		if (*line == ',')
			line++;
		else if (i < 2)
			return (ERR_F);
		value[i * 2] = temp / 16;
		value[(i * 2) + 1] = temp % 16;
	}
	value[6] = 0;
	i = -1;
	res = 0;
	while (++i < 6)
		res = res * 16 + (value[i]);
	data->color[1] = res;
	return (0);
}

int		color_c(char *line, t_data *data)
{
	char			value[7];
	int				temp;
	unsigned int	res;
	int				i;

	line++;
	if (!ft_whitespace(*line) && (*line))
		return (ERR_C);
	while (ft_whitespace(*line) && (*line))
		line++;
	i = -1;
	while (++i < 3)
	{
		temp = ft_atoi(line);
		while (is_nb(*line) && (*line))
			line++;
		if (*line == ',')
			line++;
		else if (i < 2)
			return (ERR_C);
		value[i * 2] = temp / 16;
		value[(i * 2) + 1] = temp % 16;
	}
	value[6] = 0;
	i = -1;
	res = 0;
	while (++i < 6)
		res = res * 16 + (value[i]);
	data->color[0] = res;
	return (0);
}

int			ft_void(char *line, t_data *data)
{
	return (0);
}

int			aff_err(int n, int line_n)
{
	if (n == 0)
		return (0);
	else if (n == 1)
		printf("Error in resolution line %d.\n", line_n);
	else if (n == 2)
		printf("Error in north Texture line %d.\n", line_n);
	else if (n == 3)
		printf("Error in south Texture line %d.\n", line_n);
	else if (n == 4)
		printf("Error in west Texture line %d.\n", line_n);
	else if (n == 5)
		printf("Error in east Texture line %d.\n", line_n);
	else if (n == 6)
		printf("Error in sprite Texture line %d.\n", line_n);
	else if (n == 7)
		printf("Error in floor Color line %d.\n", line_n);
	else if (n == 8)
		printf("Error in celling Color line %d.\n", line_n);
	return (1);
}

int			redirect_function(char *line, t_data *data, int line_n)
{
	int			(*redirect[10])(char *, t_data *);
	int			n;
	int			param;

	redirect[0] = ft_void;
	redirect[1] = reso;
	redirect[2] = text_no;
	redirect[3] = text_so;
	redirect[4] = text_we;
	redirect[5] = text_ea;
	redirect[6] = text_sp;
	redirect[7] = color_f;
	redirect[8] = color_c;
	param = detect_param(&line);
	n = redirect[param](line, data);
	return (aff_err(n, line_n));
}

int			parsing(int fd, t_data *data)
{
	char		*line;
	char		*temp;
	int			i;
	i = 0;
	while (i < 9)
	{
		get_next_line(fd, &line);
		temp = line;
		if (redirect_function(line, data, i + 1))
		{
			free(temp);
			return (0);
		}
		free(temp);
		i++;
	}
	return (1);
}