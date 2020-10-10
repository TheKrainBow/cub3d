/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 15:28:09 by magostin          #+#    #+#             */
/*   Updated: 2020/10/10 05:19:46 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** cast rays to draw 3D view on screen
*/
void			draw_screen(t_data *data)
{
	double		angle;
	int			x;
	t_point		a;

	x = -1;
	while (x < data->r.x)
	{
		angle = (x * data->fov) / (data->r.x - 1);
		a.x = data->player.pos.x + (cosf((data->player.angle - (data->fov / 2) + angle) * (PI / 180)));
		a.y = data->player.pos.y + (sinf((data->player.angle - (data->fov / 2) + angle) * (PI / 180)));
		closest_wall(x, a, data);
		find_sprite(x, a, data);
		x += 1;
	}
}

/*
** draw a specific wall on the xth vertical lien of the screen
*/
void			draw_height_wall(int x, t_wall obj, t_data *data)
{
	int		y;
	double	f;

	f = data->player.angle - (data->fov / 2) + ((x * data->fov) / (data->r.x - 1));
	f = fabs(f - data->player.angle);
	y = ((((data->r.x/2 - data->fov)) / ((obj.inter.dist * cosf(f / 180*PI)))));
	y = (int)data->r.y/2 - y;
	get_texture(y, x, data, obj);
}

/*
** draw all sprite on the xth vertical line of the screen
*/
void			draw_height_sprite(int x, t_point a, t_sprite *sp, t_data *data)
{
	t_sprite	*temp;
	int			y;
	double		f;

	temp = sp;
	while (temp)
	{
		temp->inter = get_inter(data->player.pos, a, temp);
		temp->dist = get_dist(temp->inter, data->player.pos);
		if (temp->dist < data->distance[x] && temp->inter.x)
		{
			data->distance[x] = temp->dist;
			f = data->player.angle - (data->fov / 2) + ((x * data->fov) / (data->r.x - 1));
			f = fabs(f - data->player.angle);
			y = (int)data->r.y/2 - (((int)(data->r.x/2 - data->fov) / (get_dist(temp->inter, data->player.pos) * cosf(f / 180*PI))));
			sprite_slice(x, y, temp, data);
		}
		temp = temp->next;
	}
}

/*
** draw a specific sprite on the xth vertical lien of the screen
*/
void			sprite_slice(int x, int y, t_sprite *temp, t_data *data)
{
	int				i;
	double			col;
	unsigned int	color;
	t_point			a;

	col = ((double)(data->t[SPRITE].wth) * (get_dist(temp->p[1], temp->inter)));
	i = y - 1;
	a.x = temp->inter.x;
	a.y = temp->inter.y;
	while ((++i < (int)data->r.y - y))
	{
		color = data->t[SPRITE].tab[(int)(((int)col % data->t[SPRITE].wth) + (((i - y) * ((int)data->t[SPRITE].lth) / ((int)data->r.y - y - y)) * ((int)data->t[SPRITE].wth)))];
		draw_pt(x, i, data, fog_color(color, get_dist(data->player.pos, a), data));
	}
	return ;
}

/*
** map the x and y pixel, to the corresponding texture's color
*/
void		get_texture(int y, int x, t_data *data, t_wall obj)
{
	int				i;
	double			col;
	unsigned int	color;

	if (obj.color == EAST || obj.color == WEST)
		col = ((double)obj.t->wth * fabs(obj.inter.y - obj.p[0].y));
	else
		col = ((double)obj.t->wth * fabs(obj.inter.x - obj.p[0].x));
	i = -1;
	while ((++i < data->r.y))
	{
		if (i <= y)
			draw_pt(x, i, data, data->color[0]);
		else if (i > y && i < ((int)data->r.y - y))
		{
			color = obj.t->tab[(int)(((int)col % obj.t->wth) + (((i - y) * ((int)obj.t->lth) / ((int)data->r.y - y - y)) * ((int)obj.t->wth)))];
			draw_pt(x, i, data, fog_color(color, data->distance[x], data));
		}
		else
			draw_pt(x, i, data, data->color[1]);
	}
}
