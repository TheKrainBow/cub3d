/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 03:22:04 by magostin          #+#    #+#             */
/*   Updated: 2020/10/15 02:24:27 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "struct.h"

/*
** call all draw hud functions
*/
void			draw_hud(t_data *data)
{
	draw_map(data);
	//draw_crosshair(data->r.x / 40, data);
}
/*
** draw a minimap of the current stage
*/
void			draw_map(t_data *data)
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
				draw_square(p, MULT - 5, 0x424242, data);
			if (data->game[(int)p.y][(int)p.x] == '1')
				draw_square(p, MULT - 5, 0xAAAAAA, data);
		}
	}
	data->average = 0;
	draw_player_map(data);
}

/*
** Draw 2D player's view
*/
void		draw_player_map(t_data *data)
{
	int		x;
	t_point	a;
	t_point	b;
	t_point	temp;
	double	dist;
	double	f;

	temp.x = data->player.pos.x * MULT;
	temp.y = data->player.pos.y * MULT;
	x = data->r.x/2;
	//while (++x < data->r.x)
	//{
		(void)dist;
		//dist = fmin(data->distance[x], 8);
		f = (x * data->fov) / (data->r.x - 1);
		//a.x = temp.x + (cosf((data->player.angle - (data->fov / 2) + f) * (PI / 180)) * (dist * MULT));
		//a.y = temp.y + (sinf((data->player.angle - (data->fov / 2) + f) * (PI / 180)) * (dist * MULT));
		a.x = data->ray_inter[x].x * MULT;
		a.y = data->ray_inter[x].y * MULT;
		if (x < 20 || x > data->r.x - 20)
			draw_line(temp, a, data, 0x0000FF);
		else
			draw_line(temp, a, data, WHITE);
	//}
	//x = 0;
	//while (x < data->r.x)
	//{
		if (data->ray_bounced[x].x != -1)
		{
			a.x = data->ray_inter[x].x * MULT;
			a.y = data->ray_inter[x].y * MULT;
			b.x = data->ray_bounced[x].x * MULT;
			b.y = data->ray_bounced[x].y * MULT;
			if (get_dist(a, b) < 1000)
				draw_line(a, b, data, 0x00FF00);
		}
		x++;
	//}
	draw_circle(temp, 2, data, WHITE);
}

/*
** Draw a crosshair
*/
void		draw_crosshair(int size, t_data *data)
{
	int		i;
	t_point	center;
	t_point	p1;
	t_point	p2;

	i = -1;
	while (++i <= 1)
	{
		p1.x = data->r.x / 2 - (size * i);
		p1.y = data->r.y / 2 - (size * !i);
		p2.x = data->r.x / 2 + (size * i);
		p2.y = data->r.y / 2 + (size * !i);
		draw_line(p1, p2, data, WHITE);
	}
	center.x = data->r.x / 2;
	center.y = data->r.y / 2;
	draw_circle(center, size / 2, data, WHITE);
}