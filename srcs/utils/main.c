/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:30:33 by magostin          #+#    #+#             */
/*   Updated: 2020/11/30 00:07:37 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void		init_keys(t_data *data)
{
	data->keys.forward = 0;
	data->keys.backward = 0;
	data->keys.move_left = 0;
	data->keys.move_right = 0;
	data->keys.look_left = 0;
	data->keys.look_right = 0;
	data->keys.open_map = 0;
	data->keys.run = 0;
	data->keys.crouch = 0;
	data->keys.jump = 0;
	data->keys.shoot = 0;
	data->player.h = data->r.y / 2;
}

int			main(int ac, char **av)
{
	t_data			data;
	int				size;

	data.save = 0;
	if (ac == 2)
	{
		size = ft_strlen(av[1]);
		if (ft_strstr(av[1], ".cub") != av[1] + size - 4)
			aff_err("File must end with .cub\n", &data);
		data.fd = open(av[1], O_RDONLY);
		if (data.fd < 0)
			aff_err("Can't open the file.\n", &data);
		init_mlx(&data);
		init_keys(&data);
		mlx_loop(data.mlx);
	}
	else if (ac == 3)
	{
		data.save = 1;
		if (ft_strstr(av[2], "--save") != av[2])
			aff_err("Second argument must be --save if 3 arguments\n", &data);
		size = ft_strlen(av[1]);
		if (ft_strstr(av[1], ".cub") != av[1] + size - 4)
			aff_err("File must end with .cub\n", &data);
		data.fd = open(av[1], O_RDONLY);
		if (data.fd < 0)
			aff_err("Can't open the file.\n", &data);
		init_mlx(&data);
		init_keys(&data);
		draw_screen(&data);
		draw_hud(&data);
		ft_save(&data);
	}
	else
		aff_err("Must have 2 or 3 arguments.\n", &data);
	close(data.fd);
	return (0);
}
