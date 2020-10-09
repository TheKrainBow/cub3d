/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 03:00:49 by magostin          #+#    #+#             */
/*   Updated: 2020/10/09 05:48:17 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** convert unsigned int color to R, G and B int
*/
void				INTtoRGB(unsigned int color, int *r, int *g, int *b)
{
	*b = color % 256;
	*g = color / 256 % 256;
	*r = color / 256 / 256 % 256;
}

/*
** convert R, G and B int to unsigned int color
*/
void				RGBtoINT(unsigned int *color, int r, int g, int b)
{
	*color = r;
	*color = (*color << 8) + g;
	*color = (*color << 8) + b;
}

/*
** Sum two colors. ratio is between 0 and 1.
*/
unsigned int		average_color(unsigned int first, unsigned int second, double ratio)
{
	int		r[3];
	int		g[3];
	int		b[3];
	unsigned int	dest;

	INTtoRGB(first, &r[0], &g[0], &b[0]);
	INTtoRGB(second, &r[1], &g[1], &b[1]);
	r[2] = r[0] * (1 - ratio) + r[1] * (ratio);
	g[2] = g[0] * (1 - ratio) + g[1] * (ratio);
	b[2] = b[0] * (1 - ratio) + b[1] * (ratio);
	r[2] = r[2] > 255 ? 255 : r[2];
	g[2] = g[2] > 255 ? 255 : g[2];
	b[2] = b[2] > 255 ? 255 : b[2];
	r[2] = r[2] < 0 ? 5 : r[2];
	g[2] = g[2] < 0 ? 5 : g[2];
	b[2] = b[2] < 0 ? 5 : b[2];
	RGBtoINT(&dest, r[2], g[2], b[2]);
	return (dest);
}

/*
** add fog to the color, depending on distance
*/
unsigned int		fog_color(unsigned int color, double dist, t_data *data)
{
	unsigned int	dest;

	(void)data;
	if (!(FOG))
		return (color);
	if (dist < 1)
		return (color);
	if (dist > 10)
		return (average_color(dest, 0x828282, 0.95));
	dest = color;
	dest = average_color(dest, 0x828282, 0.1 * (dist));
	return (dest);
}