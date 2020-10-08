/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 00:16:59 by magostin          #+#    #+#             */
/*   Updated: 2020/10/07 14:42:56 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int				double_equal(double a, double b, double round)
{
	return (a > b - round && a < b + round);
}

unsigned int	get_color(t_point ray)
{
	int		a,b;

	a = fabs(ray.x - (int)ray.x) > fabs(ray.y - (int)ray.y);
	b = fabs(ray.x - ((int)ray.x + 0.5)) > fabs(ray.y - ((int)ray.y + 0.5));
	if (a && b)
		return (NORTH);
	else if (a && !b)
		return (SOUTH);
	else if (!a && b)
		return (EAST);
	else
		return (WEST);
}

void			draw_wall(double f, t_point ray, t_data *data, unsigned int color)
{
	int		y;
	t_point	a;
	t_point	b;

	y = (int)data->r.y/2 - (((int)(data->r.y / 2) / (10)));
	a.x = (((f / data->fov) * data->r.x));
	a.y = (int)data->r.y/2 + (((int)(data->r.y / 2) / get_dist(data->player.pos, ray)));
	b.x = (((f / data->fov) * data->r.x));
	b.y = (int)data->r.y/2 - (((int)(data->r.y / 2) / get_dist(data->player.pos, ray)));
	draw_line(b, a, data, color);
}

unsigned int		tessst(t_point p, t_point inc)
{
	int		a;
	int		b;

	a = (int)p.y - (int)(p.y - inc.y);
	b = (int)p.x - (int)(p.x - inc.x);
	if (a == -1)
		return (NORTH);
	if (b == -1)
		return (WEST);
	if (a == 1)
		return (SOUTH);
	if (b == 1)
		return (EAST);
	else
	{
		//printf("%d %d\n", a, b);
		return (0x01000000);
	}
}

t_sprite	*new_sprite(t_point pos, t_data *data)
{
	t_sprite	*sprite;

	if (!(sprite = (t_sprite *)malloc(sizeof(t_sprite))))
		return (0);
	sprite->pos.x = (int)pos.x + 0.5;
	sprite->pos.y = (int)pos.y + 0.5;
	sprite = get_sprite(sprite, data);
	sprite->dist = get_dist(data->player.pos, sprite->pos);
	sprite->next = NULL;
	return (sprite);
}

void		sprite_push_front(t_sprite **first, t_sprite *new)
{
	if (!first || !new)
		return ;
	new->next = *first;
	*first = new;
}

int			ft_check_point(t_point p, t_data *data)
{
	if (p.x >= 0 && p.x < data->game_size.y && p.y >= 0 && p.y < data->game_size.x)
		return (1);
	return (0);
}

void		fix_sprite_angle(t_sprite **sprite, t_data *data)
{
	t_sprite *temp;

	temp = *sprite;
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

void		dda_test(int x, t_point a, t_data *data)
{
	t_point		p;
	t_point		inc;
	t_point		b;
	double		f;
	int			steps;
	t_sprite	*sprites;
	t_sprite	*temp;

	f = (x * data->fov) / (data->r.x - 1);
	sprites = NULL;
	b.x = data->player.pos.x + (cosf((data->player.angle - (data->fov / 2) + f) * (PI / 180)) * 100);
	b.y = data->player.pos.y + (sinf((data->player.angle - (data->fov / 2) + f) * (PI / 180)) * 100);
	steps = abs((int)(b.x - data->player.pos.x)) > abs((int)(b.y - data->player.pos.y)) ? abs((int)(b.x - data->player.pos.x)) : abs((int)(b.y - data->player.pos.y));
	inc.x = (b.x - data->player.pos.x) / (double)(steps * 3);
	inc.y = (b.y - data->player.pos.y) / (double)(steps * 3);
	p.x = data->player.pos.x;
	p.y = data->player.pos.y;
	while (ft_check_point(p, data) && data->game[(int)p.y][(int)p.x] != '1')
	{
		if (data->game[(int)p.y][(int)p.x] == '2')
			sprite_push_front(&sprites, new_sprite(p, data));
		p.x += inc.x;
		p.y += inc.y;
	}
	fix_sprite_angle(&sprites, data);
	draw_height_sprite(x, a, sprites, data);
}

void		sprite_add_sorted(t_sprite **first, t_sprite *new)
{
	t_sprite		*temp;

	if (!first || !new)
		return ;
	if (!(*first) || (*first)->dist < new->dist)
	{
		sprite_push_front(first, new);
		return ;
	}
	temp = *first;
	while (temp->next && temp->next->dist > new->dist)
		temp = temp->next;
	new->next = temp->next;
	temp->next = new;
}

void		init_sprites(t_data *data)
{
	int			c[2];
	t_point		p;

	data->sprites = NULL;
	c[0] = -1;
	while (++c[0] < data->game_size.x)
	{
		c[1] = -1;
		while (++c[1] < data->game_size.y)
			if (data->game[c[0]][c[1]] == '2')
			{
				p.x = c[1];
				p.y = c[0];
				sprite_add_sorted(&data->sprites, new_sprite(p, data));
			}
	}
}