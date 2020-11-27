/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 12:03:50 by magostin          #+#    #+#             */
/*   Updated: 2020/11/27 19:58:09 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "mlx.h"
#include "mlx_int.h"

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
	if (!(data->game[i][j] == '0' || ft_strchr("NSWE2", data->game[i][j])))
		return ;
	if (i == 0 || j == 0 || i == data->game_size.x - 1 || j == data->game_size.y - 1)
		aff_err("Map not valid!\n", data);
	if (ft_strchr(" ", data->game[i - 1][j]))
		aff_err("Map not valid!\n", data);
	if (ft_strchr(" ", data->game[i + 1][j]))
		aff_err("Map not valid!\n", data);
	if (ft_strchr(" ", data->game[i][j - 1]))
		aff_err("Map not valid!\n", data);
	if (ft_strchr(" ", data->game[i][j + 1]))
		aff_err("Map not valid!\n", data);
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
	int		j;

	if (!(data->game = malloc(sizeof(char *) * (nbr_line + 1))))
		return ;
	line_size = longest_line(map);
	i = -1;
	while (++i < nbr_line)
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
		map = map->next;
	}
	data->game[i] = NULL;
	data->game_size.y = line_size;
	data->game_size.x = nbr_line;
	check_game(data);
}

int		ft_map(char **line, t_data *data)
{
	int			ret;
	int			nbr_line;
	char		*temp;
	t_map		*game;

	temp = *line;
	nbr_line = 0;
	game = NULL;
	while (ft_whitespace((**line)) && (**line))
		(*line)++;
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
	create_game(game, nbr_line, data);
	return (1);
}

int		detect_param(char **line, t_data *data)
{
	if (ft_map(line, data))
		return (4);
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

void	reso(char *line, t_data *data)
{
	line++;
	line = ft_strtrim(line, " ");
	if (!is_nb(*line))
		aff_err("Invalide char in resolution line.\n", data);
	data->r.x = ft_atoi(line);
	if (data->r.x <= 0)
		aff_err("Resolutions must be positives numbers.\n", data);
	while (line && is_nb(*line))
		line++;
	if (!(*line == ' '))
		aff_err("Invalide char in resolution line.\n", data);
	while (line && *line == ' ')
		line++;
	if (!is_nb(*line))
		aff_err("Invalide char in resolution line.\n", data);
	data->r.y = ft_atoi(line);
	if (data->r.y <= 0)
		aff_err("Resolutions must be positives numbers.\n", data);
	while (line && is_nb(*line))
		line++;
	if (*line)
		aff_err("Invalide char in resolution line.\n", data);
	data->pars.r = 1;
}

void	fill_texture(char *line, int n, t_data *data)
{
	int		trash;

	line += 2;
	line = ft_strtrim(line, " ");
	if (data->pars.t[n] != 0)
		aff_err("Multiple definition of textures.\n", data);
	data->t[n].ptr
	 = mlx_xpm_file_to_image(data->mlx, line, &data->t[n].wth, &data->t[n].lth);
	if (!data->t[n].ptr)
		aff_err("Texture path is not valid.\n", data);
	data->t[n].tab
	 = (t_pixel *)mlx_get_data_addr(data->t[n].ptr, &trash, &trash, &trash);
	data->pars.t[n] = 1;
}

void	texture(char *line, t_data *data)
{
	if (*line == 'E')
		fill_texture(line, 0, data);
	else if (*line == 'N')
		fill_texture(line, 1, data);
	else if (*line == 'W')
		fill_texture(line, 2, data);
	else if (*line == 'S' && *(line + 1) == 'O')
		fill_texture(line, 3, data);
	else if (*line == 'S')
		fill_texture(line, 4, data);
}

void	fill_color(char *line, int n, t_data *data)
{
	int		color[3];
	int		i;

	i = -1;
	while (line[++i])
		if (!ft_strchr(" ,0123456789", line[i]))
			aff_err("C and F line must contain numbers, spaces, and commas only\n", data);
	if (!is_nb(line[ft_strlen(line) - 1]))
		aff_err("C and F line must end with spaces or numbers only\n", data);
	i = -1;
	while (++i < 3)
	{
		if (!is_nb(*line))
			aff_err("C and F line must contain numbers, spaces, and commas only\n", data);
		color[i] = ft_atoi(line);
		if (color[i] < 0 || color[i] > 255)
			aff_err("C and F numbers must be positive, and less than 255.\n", data);
		while (*line && is_nb(*line))
			line++;
		while (*line && ft_strchr(" ,", *line))
			line++;
	}
	if (*line)
		aff_err("C and F line must have only 3 colors\n", data);
	data->color[n] = pixel(color[0], color[1], color[2], 5);
}

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

void	ft_void(char *line, t_data *data)
{
	(void)line;
	(void)data;
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