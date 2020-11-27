/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 03:28:00 by magostin          #+#    #+#             */
/*   Updated: 2020/11/27 19:00:48 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double			get_dist(t_point a, t_point b)
{
	return (hypotf(a.x - b.x, a.y - b.y));
}

double			xtoa(int x, t_data *data)
{
	return ((data->player.angle + (((double)x / data->r.x - 1) *
	(double)data->fov) + (data->fov / 2)));
}

double			rtoa(double rad)
{
	return (rad * 180 / PI);
}

double			ator(double a)
{
	return (a * PI / 180);
}
