/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 00:16:59 by magostin          #+#    #+#             */
/*   Updated: 2020/10/01 17:26:31 by magostin         ###   ########.fr       */
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
	int y;
	t_point a;
	t_point b;

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
		printf("%d %d\n", a, b);
		return (0x01000000);
	}
}

t_sprite	*new_sprite(t_point pos)
{
	t_sprite	*sprite;

	if (!(sprite = (t_sprite *)malloc(sizeof(t_sprite))))
		return (0);
	sprite->pos.x = (int)pos.x + 0.5;
	sprite->pos.y = (int)pos.y + 0.5;
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

void		dda_test(double f, t_data *data)
{
	t_point		p;
	t_point		inc;
	t_point		b;
	int			steps;

	data->sprites = NULL;
	b.x = data->player.pos.x + (cosf((data->player.angle - (data->fov / 2) + f) * (PI / 180)) * 1000);
	b.y = data->player.pos.y + (sinf((data->player.angle - (data->fov / 2) + f) * (PI / 180)) * 1000);
	steps = abs((int)(b.x - data->player.pos.x)) > abs((int)(b.y - data->player.pos.y)) ? abs((int)(b.x - data->player.pos.x)) : abs((int)(b.y - data->player.pos.y));
	inc.x = (b.x - data->player.pos.x) / (double)(steps);
	inc.y = (b.y - data->player.pos.y) / (double)(steps);
	p.x = data->player.pos.x;
	p.y = data->player.pos.y;
	while (data->game[(int)p.y][(int)p.x] != '1')
	{
		if (data->game[(int)p.y][(int)p.x] == '2')
			sprite_push_front(&data->sprites, new_sprite(p));
		p.x += inc.x;
		p.y += inc.y;
	}
	printf("\n");
	//printf("%f %f %c\n", x, y, data->game[(int)y][(int)x]);
	t_sprite *temp;
	temp = data->sprites;
	while (temp)
	{
		printf("%f\n", get_dist(data->player.pos, temp->pos));
		temp = temp->next;
	}
	//draw_wall(f, p, data, tessst(p, inc));
}