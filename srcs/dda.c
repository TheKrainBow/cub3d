/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 23:55:08 by magostin          #+#    #+#             */
/*   Updated: 2020/07/26 21:32:49 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_point			get_intersect_dda(t_point b, t_point a, t_point c, t_point d)
{
	double		t;
	double		u;
	double		denum;
	t_point		inter;

	denum = ((a.x - b.x) * (c.y - d.y)) - ((a.y - b.y) * (c.x - d.x));
	t = (((a.x - c.x) * (c.y - d.y)) - ((a.y - c.y) * (c.x - d.x)));
	u = -(((a.x - b.x) * (a.y - c.y)) - ((a.y - b.y) * (a.x - c.x)));
	inter.x = 0;
	inter.y = 0;
	if (denum != 0)
	{
		t /= denum;
		u /= denum;
		if ((t <= 1) && (0 <= u && u <= 1))
		{
			inter.x = a.x + (t * (b.x - a.x));
			inter.y = a.y + (t * (b.y - a.y));
			return (inter);
		}
	}
	return (inter);
}

double			get_angle_tan(double opp, double adj)
{
	return (atan(opp/adj) * (180 / PI));
}

int			get_walls_angle(double ray_angle, t_point dda, t_data *data)
{
	double	angle[4];
	double	opp;
	double	adj;

	printf("%f %f\n", data->player.pos.x, data->player.pos.y);
	opp = (double)(int)data->player.pos.y + 1 - data->player.pos.y;
	adj = (double)(int)data->player.pos.x + 1 - data->player.pos.x;
	angle[0] = get_angle_tan(opp, adj); //bot_right

	opp = data->player.pos.x - (double)(int)data->player.pos.x;
	adj = (double)(int)data->player.pos.y + 1 - data->player.pos.y;
	angle[1] = 90 + get_angle_tan(opp, adj); //bot_left

	opp = data->player.pos.y - (double)(int)data->player.pos.y;
	adj = data->player.pos.x - (double)(int)data->player.pos.x;
	angle[2] = 180 + get_angle_tan(opp, adj); //top_left

	opp = (double)(int)data->player.pos.x + 1 - data->player.pos.x;
	adj = data->player.pos.y - (double)(int)data->player.pos.y;
	angle[3] = 270 + get_angle_tan(opp, adj); //top_right

	if ((int)ray_angle >= (int)angle[0] && (int)ray_angle <= (int)angle[1])
		printf("Player look bot\n");
	if ((int)ray_angle >= (int)angle[1] && (int)ray_angle <= (int)angle[2])
		printf("Player look left\n");
	if ((int)ray_angle >= (int)angle[2] && (int)ray_angle <= (int)angle[3])
		printf("Player look top\n");
	if (((int)ray_angle >= (int)angle[3] && (int)ray_angle <= 360) || ((int)ray_angle >= 0 && (int)ray_angle <= (int)angle[0]))
		printf("Player look right\n");
	return (1);
}

int			closest_wall_dda(t_point x, t_data *data)
{
	t_point	inter;
	t_point dda;
	double	x_angle;

	dda.x = data->player.pos.x;
	dda.y = data->player.pos.y;
	get_walls_angle(data->player.angle, dda, data);
	//printf("\nPlayer  = %f %f\n", data->player.pos.x, data->player.pos.y);
	/*printf("Angle 1 = %f %f\n", (double)(int)data->player.pos.x, (double)(int)data->player.pos.y);
	printf("Angle 2 = %f %f\n", (double)(int)data->player.pos.x + 1, (double)(int)data->player.pos.y);
	printf("Angle 3 = %f %f\n", (double)(int)data->player.pos.x + 1, (double)(int)data->player.pos.y + 1);
	printf("Angle 4 = %f %f\n", (double)(int)data->player.pos.x, (double)(int)data->player.pos.y + 1);*/
	//printf("%c %d %d\n", data->game[(int)dda.y][(int)dda.x], (int)dda.x, (int)dda.y);
	return (1);
}
