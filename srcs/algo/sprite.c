/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 03:54:13 by magostin          #+#    #+#             */
/*   Updated: 2020/11/27 19:05:48 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** Create a new sprite node
*/
t_sprite	*new_sprite(t_point pos, t_data *data)
{
	t_sprite	*sp;

	if (!(sp = (t_sprite *)malloc(sizeof(t_sprite))))
		return (0);
	sp->pos.x = (int)pos.x + 0.5;
	sp->pos.y = (int)pos.y + 0.5;
	sp->dist = get_dist(sp->pos, data->player.pos);
	sp->p[1].x = cosf(ator(data->player.angle) - PI / 2) / 2 + sp->pos.x;
	sp->p[1].y = sinf(ator(data->player.angle) - PI / 2) / 2 + sp->pos.y;
	sp->p[0].x = cosf(ator(data->player.angle) + PI / 2) / 2 + sp->pos.x;
	sp->p[0].y = sinf(ator(data->player.angle) + PI / 2) / 2 + sp->pos.y;
	sp->dist = get_dist(data->player.pos, sp->pos);
	sp->next = NULL;
	return (sp);
}

void		sprite_push_front(t_sprite **first, t_sprite *new)
{
	if (!first || !new)
		return ;
	new->next = *first;
	*first = new;
}
