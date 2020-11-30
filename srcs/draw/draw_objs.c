/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 15:28:09 by magostin          #+#    #+#             */
/*   Updated: 2020/11/30 00:58:13 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_screen(t_data *data)
{
	double		angle;
	int			x;
	t_point		a;

	x = -1;
	while (++x < data->r.x - 1)
	{
		angle = (x * data->fov) / (data->r.x - 1);
		a.x = data->player.pos.x + (cosf(
		(data->player.angle - (data->fov / 2) + angle) * (PI / 180)));
		a.y = data->player.pos.y + (sinf(
		(data->player.angle - (data->fov / 2) + angle) * (PI / 180)));
		data->mirrored = 0;
		data->bounced = 0;
		closest_wall(x, data);
	}
}

int		between(t_point inter, t_point c, t_point d)
{
	return ((((inter.x >= c.x && inter.x <= d.x)
	|| (inter.x >= d.x && inter.x <= c.x))
	&& ((inter.y >= c.y && inter.y <= d.y)
	|| (inter.y >= d.y && inter.y <= c.y))));
}

double	calculate_f(int x, t_data *data)
{
	return (fix_angle(fabs((data->player.angle - (data->fov / 2) + (
	(x * data->fov) / (data->r.x - 1))) - data->player.angle)));
}

void	draw_sprite(int x, t_sprite *sp, t_data *data)
{
	t_sprite	*temp;
	int			y;
	double		f;
	t_point		a;

	f = xtoa(x, data);
	a.x = data->player.pos.x + cos(ator(f));
	a.y = data->player.pos.y + sin(ator(f));
	while (sp)
	{
		sp->inter = intersect(data->player.pos, a, sp->p[0], sp->p[1]);
		sp->dist = get_dist(sp->inter, data->player.pos);
		if (sp->dist < data->distance[x] &&
		between(sp->inter, sp->p[0], sp->p[1]))
		{
			data->distance[x] = sp->dist;
			f = calculate_f(x, data);
			y = (((int)(data->r.x / 2 - data->fov) / (
			get_dist(sp->inter, data->player.pos) * cosf(f / 180 * PI))));
			sprite_slice(x, y, sp, data);
		}
		temp = sp;
		sp = sp->next;
		free(temp);
	}
}

void	sprite_slice(int x, int y, t_sprite *temp, t_data *data)
{
	int				i;
	t_pixel			color;
	t_point			a;
	t_point			coor;
	int				y_temp;

	y_temp = y;
	y = (int)data->player.h - y;
	i = (int)data->player.h - y_temp - 1;
	a.x = temp->inter.x;
	a.y = temp->inter.y;
	while ((++i < (int)data->player.h + y_temp))
	{
		coor.x = (int)((double)(data->t[SPRITE].wth) * (
		get_dist(temp->p[1], temp->inter))) % data->t[SPRITE].wth;
		coor.y = map(i, point((int)data->player.h - y_temp - 1,
		(int)data->player.h + y_temp), point(0, data->t[SPRITE].lth));
		color = data->t[SPRITE].tab[(int)coor.x +
		(int)coor.y * data->t[SPRITE].wth];
		draw_pt(x, i, data,
		fog_color(color, get_dist(data->player.pos, a), data));
	}
	return ;
}
