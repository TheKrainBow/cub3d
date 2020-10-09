/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 03:31:46 by magostin          #+#    #+#             */
/*   Updated: 2020/10/09 05:47:47 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** find the closest wall for the xth vertical line of the screen
*/
void			closest_wall(int x, t_point a, t_data *data)
{
	int			i;
	int			best_wall;

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
	draw_height_wall(x, data->objs[best_wall], data);
	return ;
}

/*
** Create a sorted list of all sprite for the xth vertical line of the screen
*/
void		find_sprite(int x, t_point a, t_data *data)
{
	t_point		p;
	t_point		inc;
	t_point		b;
	double		f;
	int			steps;
	t_sprite	*sprites;

	f = (x * data->fov) / (data->r.x - 1);
	sprites = NULL;
	b.x = data->player.pos.x + (cosf((data->player.angle - (data->fov / 2) + f) * (PI / 180)) * 50);
	b.y = data->player.pos.y + (sinf((data->player.angle - (data->fov / 2) + f) * (PI / 180)) * 50);
	steps = abs((int)(b.x - data->player.pos.x)) > abs((int)(b.y - data->player.pos.y)) ? abs((int)(b.x - data->player.pos.x)) : abs((int)(b.y - data->player.pos.y));
	inc.x = (b.x - data->player.pos.x) / (double)(steps * 3);
	inc.y = (b.y - data->player.pos.y) / (double)(steps * 3);
	p.x = data->player.pos.x;
	p.y = data->player.pos.y;
	while (check_point(p, data) && data->game[(int)p.y][(int)p.x] != '1')
	{
		if (data->game[(int)p.y][(int)p.x] == '2')
			sprite_push_front(&sprites, new_sprite(p, data));
		p.x += inc.x;
		p.y += inc.y;
	}
	fix_sprite_angle(&sprites, data);
	draw_height_sprite(x, a, sprites, data);
}