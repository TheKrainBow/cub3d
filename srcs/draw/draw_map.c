/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 00:35:55 by magostin          #+#    #+#             */
/*   Updated: 2020/11/30 01:09:51 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_map(t_data *data)
{
	t_point	p;

	p.y = -1;
	data->average = 1;
	while (++p.y < data->game_size.x)
	{
		p.x = -1;
		while (++p.x < data->game_size.y)
		{
			if (ft_strchr("0NSEW2", data->game[(int)p.y][(int)p.x]))
				draw_square(p, data->mult, pixel(20, 20, 20, 1), data);
			if (data->game[(int)p.y][(int)p.x] == '1')
				draw_square(p, data->mult, pixel(80, 80, 80, 1), data);
		}
	}
	data->average = 0;
	draw_player_map(data);
}

void	draw_player_map(t_data *data)
{
	int		x;
	t_point	a;
	t_point	b;
	t_point	temp;

	temp.x = data->player.pos.x * data->mult;
	temp.y = data->player.pos.y * data->mult;
	x = data->r.x / 2;
	a.x = data->ray_inter[x].x * data->mult;
	a.y = data->ray_inter[x].y * data->mult;
	draw_line(temp, a, data, pixel(255, 255, 255, 1));
	if (data->ray_bounced[x].x != -1)
	{
		a.x = data->ray_inter[x].x * data->mult;
		a.y = data->ray_inter[x].y * data->mult;
		b.x = data->ray_bounced[x].x * data->mult;
		b.y = data->ray_bounced[x].y * data->mult;
		if (get_dist(a, b) < 1000)
			draw_line(a, b, data, pixel(0, 255, 0, 1));
	}
	draw_circle(temp, 2, data, pixel(255, 255, 255, 1));
}
