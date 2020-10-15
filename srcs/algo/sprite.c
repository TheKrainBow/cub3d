/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 03:54:13 by magostin          #+#    #+#             */
/*   Updated: 2020/10/15 01:39:56 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** Create a new sprite node
*/
double			ator(double a);
t_sprite	*new_sprite(t_point pos, t_data *data)
{
	t_sprite	*sprite;

	if (!(sprite = (t_sprite *)malloc(sizeof(t_sprite))))
		return (0);
	sprite->pos.x = (int)pos.x + 0.5;
	sprite->pos.y = (int)pos.y + 0.5;
	sprite->dist = get_dist(sprite->pos, data->player.pos);
	sprite->p[1].x = cosf(ator(data->player.angle) - PI/2) / 2 + sprite->pos.x;
	sprite->p[1].y = sinf(ator(data->player.angle) - PI/2) / 2 + sprite->pos.y;
	sprite->p[0].x = cosf(ator(data->player.angle) + PI/2) / 2 + sprite->pos.x;
	sprite->p[0].y = sinf(ator(data->player.angle) + PI/2) / 2 + sprite->pos.y;
	sprite->dist = get_dist(data->player.pos, sprite->pos);
	sprite->next = NULL;
	return (sprite);
}

/*
** Add a node at the beginning of the linked list
*/
void		sprite_push_front(t_sprite **first, t_sprite *new)
{
	if (!first || !new)
		return ;
	new->next = *first;
	*first = new;
}