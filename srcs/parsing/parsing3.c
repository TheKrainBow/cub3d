/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 01:22:00 by magostin          #+#    #+#             */
/*   Updated: 2020/12/02 23:07:51 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	reso2(char *line, t_data *data)
{
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

void	reso(char *line, t_data *data)
{
	char	*tmp;

	line++;
	line = ft_strtrim(line, " ");
	tmp = line;
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
	reso2(line, data);
	free(tmp);
}

void	fill_texture(char *line, int n, t_data *data)
{
	int		trash;

	line += 2;
	line = ft_strtrim(line, " ");
	if (data->pars.t[n] != 0)
		aff_err("Multiple definition of textures.\n", data);
	data->t[n].ptr = mlx_xpm_file_to_image(data->mlx, line,
	&data->t[n].wth, &data->t[n].lth);
	if (!data->t[n].ptr)
		aff_err("Texture path is not valid.\n", data);
	data->t[n].tab = (t_pixel *)mlx_get_data_addr(data->t[n].ptr,
	&trash, &trash, &trash);
	data->pars.t[n] = 1;
	free(line);
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
			aff_err(C_F_ERR, data);
	if (!is_nb(line[ft_strlen(line) - 1]))
		aff_err(C_F_ERR, data);
	i = -1;
	while (++i < 3)
	{
		if (!is_nb(*line))
			aff_err(C_F_ERR, data);
		color[i] = ft_atoi(line);
		if (color[i] < 0 || color[i] > 255)
			aff_err(C_F_INV, data);
		while (*line && is_nb(*line))
			line++;
		while (*line && ft_strchr(" ,", *line))
			line++;
	}
	if (*line)
		aff_err("C and F line must have only 3 colors\n", data);
	data->color[n] = pixel(color[0], color[1], color[2], 5);
}
