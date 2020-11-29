/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 23:45:30 by magostin          #+#    #+#             */
/*   Updated: 2020/11/29 23:45:46 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char		game(t_point p, t_data *data)
{
	return (data->game[(int)p.y][(int)p.x]);
}

t_point		point(double x, double y)
{
	t_point		p;

	p.x = x;
	p.y = y;
	return (p);
}
