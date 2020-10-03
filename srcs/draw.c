/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 15:28:09 by magostin          #+#    #+#             */
/*   Updated: 2020/10/03 04:12:58 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		draw_pt(int x, int y, t_data *data, unsigned int color)
{
	if (y > 0 && y < data->r.y && x > 0 && x < data->r.x && color)
	{
		data->draw[(y * (int)data->r.x) + x] = color;
	}
}

double			get_dist(t_point a, t_point b)
{
	return (sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2)));
}

void		draw_walls(t_data *data, int mult)
{
	int			i;
	t_point		a;
	t_point		b;

	i = -1;
	while (++i < data->n_objs)
	{
		a.x = data->objs[i].p[0].x * mult;
		a.y = data->objs[i].p[0].y * mult;
		b.x = data->objs[i].p[1].x * mult;
		b.y = data->objs[i].p[1].y * mult;
		draw_line(a, b, data, data->objs[i].color);
	}
}

void		draw_line(t_point a, t_point b, t_data *data, unsigned int color)
{
	int			i;
	double		x,y;
	int			dx, dy;
	int			steps;
	double		xinc, yinc;

	dx = b.x - a.x;
	dy = b.y - a.y;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	xinc = dx / (double)steps;
	yinc = dy / (double)steps;
	x = a.x;
	y = a.y;
	i = -1;
	while (++i <= steps)
	{
		draw_pt(x, y, data, color);
		x += xinc;
		y += yinc;
	}
}

void		draw_circle(t_point center, int radius, t_data *data, unsigned int color)
{
	double i;
	/*t_point a;
	t_point b;*/
	center.x *= MULT;
	center.y *= MULT;

	i = 0;
	while (i < 360)
	{
		/*a.x = center.x + (cos(i * PI / 180) * radius);
		a.y = center.y + (sin(i * PI / 180) * radius);
		b.x = center.x + (cos((i + 1) * PI / 180) * radius);
		b.y = center.y + (sin((i + 1) * PI / 180) * radius);*/
		draw_pt(center.x + (cos(i * PI / 180) * radius), center.y + (sin(i * PI / 180) * radius), data, color);
		i += 1;
	}
}

t_point			get_intersect(t_point b, t_point a, t_object obj)
{
	double		t;
	double		u;
	double		denum;
	t_point		c;
	t_point		d;
	t_point		inter;

	c = obj.p[0];
	d = obj.p[1];
	denum = ((a.x - b.x) * (c.y - d.y)) - ((a.y - b.y) * (c.x - d.x));
	t = (((a.x - c.x) * (c.y - d.y)) - ((a.y - c.y) * (c.x - d.x)));
	u = -(((a.x - b.x) * (a.y - c.y)) - ((a.y - b.y) * (a.x - c.x)));
	inter.x = 0;
	inter.y = 0;
	if (denum != 0)
	{
		t /= denum;
		u /= denum;
		if ((t <= 1) && (0 <= u && u <= 1))
		{
			inter.x = a.x + (t * (b.x - a.x));
			inter.y = a.y + (t * (b.y - a.y));
			return (inter);
		}
	}
	return (inter);
}

void		get_texture(int y, int x, t_data *data, t_object obj)
{
	int				i;
	//int				x;
	t_point			temp;
	double			col;
	unsigned int	color;

	//x = (((angle / data->fov) * data->r.x));
	if (obj.color == NORTH || obj.color == SOUTH)
		col = ((double)obj.t->wth * ft_sub_abs(obj.inter.y, obj.p[0].y));
	else
		col = ((double)obj.t->wth * ft_sub_abs(obj.inter.x, obj.p[0].x));
	i = -1;
	while ((++i < data->r.y))
	{
		if (i <= y)
			draw_pt(x, i, data, data->color[0]);
		else if (i > y && i < ((int)data->r.y - y))
		{
			color = obj.t->tab[(int)(((int)col % obj.t->wth) + (((i - y) * ((int)obj.t->lth) / ((int)data->r.y - y - y)) * ((int)obj.t->wth)))];
			draw_pt(x, i, data, color);
		}
		else
			draw_pt(x, i, data, data->color[1]);
	}
}

double			get_angle(t_point a, t_point player)
{
	return ((acosf((a.x - player.x) / get_dist(a, player)) * (180/PI)) < 0
	? (acosf((a.x - player.x) / get_dist(a, player)) * (180/PI))
	: (asinf((a.y - player.y) / get_dist(a, player))) * (180/PI));
}

void			draw_height(int x, t_object obj, t_data *data)
{
	int		y;
	double	f;

	f = data->player.angle - (data->fov / 2) + ((x * FOV) / (data->r.x - 1));
	f = ft_sub_abs(f, data->player.angle);
	y = (int)data->r.y/2 - (((int)(data->r.y / 2) / (obj.inter.dist * cosf(f / 180*PI))));
	get_texture(y, x, data, obj);
}

t_point			get_inter(t_point b, t_point a, t_sprite *obj)
{
	double		t;
	double		u;
	double		denum;
	t_point		c;
	t_point		d;
	t_point		inter;

	c = obj->p[0];
	d = obj->p[1];
	denum = ((a.x - b.x) * (c.y - d.y)) - ((a.y - b.y) * (c.x - d.x));
	t = (((a.x - c.x) * (c.y - d.y)) - ((a.y - c.y) * (c.x - d.x)));
	u = -(((a.x - b.x) * (a.y - c.y)) - ((a.y - b.y) * (a.x - c.x)));
	inter.x = 0;
	inter.y = 0;
	if (denum != 0)
	{
		t /= denum;
		u /= denum;
		if ((t <= 1) && (0 <= u && u <= 1))
		{
			inter.x = a.x + (t * (b.x - a.x));
			inter.y = a.y + (t * (b.y - a.y));
		}
	}
	return (inter);
}

void			sprite_slice(int x, int y, t_sprite *temp, t_data *data)
{
	int				i;
	double			col;
	unsigned int	color;

	col = ((double)(data->sprt.wth) * (get_dist(temp->p[0], temp->inter)));
	i = y - 1;
	while ((++i < (int)data->r.y - y))
	{
		color = data->sprt.tab[(int)(((int)col % data->sprt.wth) + (((i - y) * ((int)data->sprt.lth) / ((int)data->r.y - y - y)) * ((int)data->sprt.wth)))];
		draw_pt(x, i, data, color);
	}
	return ;
}

void			draw_height_sprite(int x, t_point a, t_data *data)
{
	t_sprite	*temp;
	int		y;
	double	f;

	temp = data->sprites;
	while (temp)
	{
		temp->inter = get_inter(data->player.pos, a, temp);
		if (get_dist(temp->inter, data->player.pos) < data->distance[x] && temp->inter.x)
		{
			f = data->player.angle - (data->fov / 2) + ((x * FOV) / (data->r.x - 1));
			f = ft_sub_abs(f, data->player.angle);
			y = (int)data->r.y/2 - (((int)(data->r.y / 2) / (get_dist(temp->inter, data->player.pos) * cosf(f / 180*PI))));
			sprite_slice(x, y, temp, data);
		}
		temp = temp->next;
	}
}

void			closest_object(int x, t_point a, t_data *data)
{
	int			i;
	int			best_wall;
	int			best_sprite;
	int			dist;

	i = -1;
	best_wall = -1;
	while (++i < data->n_objs)
	{
		data->objs[i].inter = get_intersect(data->player.pos, a, data->objs[i]);
		data->objs[i].inter.dist = get_dist(data->player.pos, data->objs[i].inter);
		if ((best_wall == -1 || data->objs[i].inter.dist <= data->objs[best_wall].inter.dist) && (data->objs[i].inter.x && data->objs[i].inter.y))
			best_wall = i;
	}
	data->distance[x] = data->objs[best_wall].inter.dist;
	draw_height(x, data->objs[best_wall], data);
	draw_height_sprite(x, a, data);
	return ;
}

void			draw_grid(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (++i < MAP_H)
	{
		j = -1;
		while (++j < MAP_L)
		{
			if (data->game[i][j] == '0')
				draw_square(j * MULT, i * MULT, MULT - 2, 0x424242, data);
			if (data->game[i][j] == '1')
				draw_square(j * MULT, i * MULT, MULT - 1, 0xAAAAAA, data);
			if (data->game[i][j] == '2')
				draw_square(j * MULT + MULT / 4, i * MULT + MULT / 4, MULT / 2, 0xEEEEEE, data);
		}
	}
}

double			ft_atan2(t_point a, t_point player)
{
	return (atan2(a.y - player.y, a.x - player.x));
}

t_sprite		*sorted_merge_list(t_sprite *a, t_sprite *b)
{
	t_sprite		*temp;

	temp = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (a->dist > b->dist)
	{
		temp = a;
		temp->next = sorted_merge_list(a->next, b);
	}
	else
	{
		temp = b;
		temp->next = sorted_merge_list(a, b->next);
	}
	return (temp);
}

void			split_list(t_sprite *src, t_sprite **a, t_sprite **b)
{
	t_sprite	*fast;
	t_sprite	*slow;

	slow = src;
	fast = src->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*a = src;
	*b = slow->next;
	slow->next = NULL;
}
void			sprites_sort(t_sprite **sprites)
{
	t_sprite		*temp;
	t_sprite		*a;
	t_sprite		*b;

	temp = *sprites;
	if (!(temp) || !(temp->next))
		return ;
	split_list(temp, &a, &b);
	sprites_sort(&a);
	sprites_sort(&b);
	*sprites = sorted_merge_list(a, b);
}

void			draw_sprites_v2(t_data *data)
{
	t_sprite		*temp;
	t_point			a;
	t_point			b;

	temp = data->sprites;
	sprites_sort(&temp);
	while (temp)
	{
		temp->dist = get_dist(temp->pos, data->player.pos);
		temp->angle = ft_atan2(data->player.pos, temp->pos);
		temp->p[0].x = cosf(temp->angle - PI/2) / 2 + temp->pos.x;
		temp->p[0].y = sinf(temp->angle - PI/2) / 2 + temp->pos.y;
		temp->p[1].x = cosf(temp->angle + PI/2) / 2 + temp->pos.x;
		temp->p[1].y = sinf(temp->angle + PI/2) / 2 + temp->pos.y;
		temp = temp->next;
	}
}

void			draw_screen(t_data *data)
{
	int			i;
	double		f;
	int			j;
	double		x;
	t_point		a;
	int			closest;

	x = -1;
	draw_sprites_v2(data);
	while (x < data->r.x)
	{
		f = (x * FOV) / (data->r.x - 1);
		a.x = data->player.pos.x + (cosf((data->player.angle - (data->fov / 2) + f) * (PI / 180)));
		a.y = data->player.pos.y + (sinf((data->player.angle - (data->fov / 2) + f) * (PI / 180)));
		closest_object(x, a, data);
		x += 1;
	}
}