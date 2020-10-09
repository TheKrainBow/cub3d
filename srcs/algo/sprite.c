/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 03:54:13 by magostin          #+#    #+#             */
/*   Updated: 2020/10/09 03:57:45 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** Create a new sprite node
*/
t_sprite	*new_sprite(t_point pos, t_data *data)
{
	t_sprite	*sprite;

	if (!(sprite = (t_sprite *)malloc(sizeof(t_sprite))))
		return (0);
	sprite->pos.x = (int)pos.x + 0.5;
	sprite->pos.y = (int)pos.y + 0.5;
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

/*
** Adjust angle of all sprite so it face the player
*/
void		fix_sprite_angle(t_sprite **sprite, t_data *data)
{
	t_sprite *temp;

	temp = *sprite;
	while (temp)
	{
		temp->dist = get_dist(temp->pos, data->player.pos);
		temp->angle = atan2(data->player.pos.y - temp->pos.y, data->player.pos.x - temp->pos.x);
		temp->p[0].x = cosf(temp->angle - PI/2) / 2 + temp->pos.x;
		temp->p[0].y = sinf(temp->angle - PI/2) / 2 + temp->pos.y;
		temp->p[1].x = cosf(temp->angle + PI/2) / 2 + temp->pos.x;
		temp->p[1].y = sinf(temp->angle + PI/2) / 2 + temp->pos.y;
		temp = temp->next;
	}
}