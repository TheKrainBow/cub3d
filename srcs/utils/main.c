/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:30:33 by magostin          #+#    #+#             */
/*   Updated: 2020/12/02 22:45:38 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		swap_images(t_data *data)
{
	void	*img_temp;
	void	*draw_temp;

	img_temp = data->img;
	draw_temp = data->draw;
	data->img = data->img2;
	data->draw = data->draw2;
	data->img2 = img_temp;
	data->draw2 = draw_temp;
}

void		update(t_data *data)
{
	draw_screen(data);
	draw_hud(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	swap_images(data);
}

void		start_game(char *str, t_data *data)
{
	int				size;

	size = ft_strlen(str);
	if (ft_strstr(str, ".cub") != str + size - 4)
		aff_err("File must end with .cub\n", data);
	data->fd = open(str, O_RDONLY);
	if (data->fd < 0)
		aff_err("Can't open the file.\n", data);
	init_keys(data);
	init_mlx(data);
	exit_game(data);
}

void		start_save(char **av, t_data *data)
{
	int				size;

	size = ft_strlen(av[1]);
	data->save = 1;
	if (ft_strstr(av[2], "--save") != av[2])
		aff_err("Second argument must be --save if 3 arguments\n", data);
	if (ft_strstr(av[1], ".cub") != av[1] + size - 4)
		aff_err("File must end with .cub\n", data);
	data->fd = open(av[1], O_RDONLY);
	if (data->fd < 0)
		aff_err("Can't open the file.\n", data);
	init_mlx(data);
	init_keys(data);
	draw_screen(data);
	draw_hud(data);
	ft_save(data);
	exit_game(data);
}

int			main(int ac, char **av)
{
	t_data			data;

	if (ac == 2)
		start_game(av[1], &data);
	else if (ac == 3)
		start_save(av, &data);
	else
		aff_err("Must have 2 or 3 arguments.\n", &data);
	return (0);
}
