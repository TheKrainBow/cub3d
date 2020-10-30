/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 03:00:49 by magostin          #+#    #+#             */
/*   Updated: 2020/10/15 23:40:34 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** convert t_pixel color to R, G and B int
*/
/*void				INTtoRGB(t_pixel color, int *r, int *g, int *b)
{
	*b = color % 256;
	*g = color / 256 % 256;
	*r = color / 256 / 256 % 256;
}*/

/*
** convert R, G and B int to t_pixel color
*/
/*void				RGBtoINT(t_pixel *color, int r, int g, int b)
{
	*color = r;
	*color = (*color << 8) + g;
	*color = (*color << 8) + b;
}*/

t_pixel				pixel(int r, int g, int b, int a)
{
	t_pixel		dest;

	dest.r = r;
	dest.g = g;
	dest.b = b;
	dest.a = a;
	return (dest);
}
/*
** Sum two colors. ratio is between 0 and 1.
*/
t_pixel		average_color(t_pixel first, t_pixel second, double ratio)
{
	first.r = first.r * (1 - ratio) + second.r * (ratio);
	first.g = first.g * (1 - ratio) + second.g * (ratio);
	first.b = first.b * (1 - ratio) + second.b * (ratio);
	first.r = first.r > 255 ? 255 : first.r;
	first.g = first.g > 255 ? 255 : first.g;
	first.b = first.b > 255 ? 255 : first.b;
	first.r = first.r < 0 ? 5 : first.r;
	first.g = first.g < 0 ? 5 : first.g;
	first.b = first.b < 0 ? 5 : first.b;
	return (first);
}

/*
** add fog to the color, depending on distance
*/
t_pixel			fog_color(t_pixel color, double dist, t_data *data)
{
	t_pixel	dest;
	t_pixel	grey;

	grey.r = 20;
	grey.g = 20;
	grey.b = 20;
	(void)data;
	if (!(FOG))
		return (color);
	if (dist < 1)
		return (color);
	if (dist > 10)
		return (average_color(dest, grey, 0.95));
	dest = color;
	dest = average_color(dest, grey, 0.1 * (dist));
	return (dest);
}