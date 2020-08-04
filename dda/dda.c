/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 23:55:08 by magostin          #+#    #+#             */
/*   Updated: 2020/08/04 20:59:37 by magostin         ###   ########.fr       */
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

int			get_walls_270_0(double ray_angle, t_point *dda, t_data *data)
{
	double	angle;
	double	opp;
	double	adj;

	opp = (double)(int)data->player.pos.x + ((int)dda->x - (int)data->player.pos.x + 1) - data->player.pos.x;
	adj = data->player.pos.y - (double)(int)dda->y;
	angle = 270 + get_angle_tan(opp, adj); //top_right

	if ((int)ray_angle >= (int)(angle + 1))
	{
		dda->x++;
		return (0);
		//printf("Player look right\n");
	}
	else
	{
		dda->y--;
		return (3);
		//printf("Player look top\n");
	}
	return (1);
}

int			get_walls_180_270(double ray_angle, t_point *dda, t_data *data)
{
	double	angle;
	double	opp;
	double	adj;

	opp = data->player.pos.y - (double)(int)dda->y;
	adj = data->player.pos.x - (double)(int)dda->x;
	angle = 180 + get_angle_tan(opp, adj); //top_left

	if ((int)ray_angle >= (int)(angle + 1))
	{
		dda->y--;
		return (3);
		//printf("Player look top\n");
	}
	else
	{
		dda->x--;
		return (2);
		//printf("Player look left\n");
	}
	return (1);
}

int			get_walls_90_180(double ray_angle, t_point *dda, t_data *data)
{
	double	angle;
	double	opp;
	double	adj;

	opp = data->player.pos.x - (double)(int)dda->x;
	adj = (double)(int)data->player.pos.y + ((int)dda->y - (int)data->player.pos.y + 1) - data->player.pos.y;
	angle = 90 + get_angle_tan(opp, adj); //bot_left

	if ((int)ray_angle >= (int)(angle + 1))
	{
		dda->x--;
		return (2);
		//printf("Player look left\n");
	}
	else
	{
		dda->y++;
		return (1);
		//printf("Player look bot\n");
	}
	return (1);
}

void			draw_scr_line(double dist, double angle, int text, t_data *data)
{
	int			y;

	angle = angle + (FOV / 2) - data->player.angle;
	y = (int)(1 / dist * 21);
	while (y > -(int)(1 / dist * 21))
	{
		data->screen[10 + y][(int)angle] = text + '0';
		y--;
	}
}

void			get_walls_0_90(double ray_angle, t_point *dda, t_data *data)
{
	double	angle;
	double	opp;
	double	adj;
	t_point	pt;

	opp = (double)(int)data->player.pos.y + ((int)dda->y - (int)data->player.pos.y + 1) - data->player.pos.y;
	adj = (double)(int)data->player.pos.x + ((int)dda->x - (int)data->player.pos.x + 1) - data->player.pos.x;
	angle = get_angle_tan(opp, adj); //bot_right
	if ((int)ray_angle > (int)(angle + 1))
		dda->y++; //printf("Player look bot\n");
	else
		dda->x++; //printf("Player look right\n");
	if (data->game[(int)dda->y][(int)dda->x] == '1')
	{
		if ((int)ray_angle >= (int)(angle + 1))
		{
			pt.x = (((double)(int)data->player.pos.x + ((int)dda->x - (int)data->player.pos.x + 1) - data->player.pos.x) * (ray_angle / angle)) + data->player.pos.x;
			pt.y = (int)dda->y + 1;
			draw_scr_line(get_dist(pt, data->player.pos), ray_angle, 1, data);
			return ;
		}
		pt.x = (int)dda->x + 1;
		pt.y = (((double)(int)data->player.pos.y + ((int)dda->y - (int)data->player.pos.y + 1) - data->player.pos.y) * (ray_angle / angle)) + data->player.pos.y;
		draw_scr_line(get_dist(pt, data->player.pos), ray_angle, 0, data);
		return ;
	}
	else
		return (get_walls_0_90(ray_angle, dda, data));
}

void			get_walls_angle(double ray_angle, t_point *dda, t_data *data)
{
	if ((int)data->player.angle >= 0 && (int)data->player.angle <= 90)
		get_walls_0_90(ray_angle, dda, data);
	else if ((int)data->player.angle >= 90 && (int)data->player.angle <= 180)
		get_walls_90_180(ray_angle, dda, data);
	else if ((int)data->player.angle >= 180 && (int)data->player.angle <= 270)
		get_walls_180_270(ray_angle, dda, data);
	else
		get_walls_270_0(ray_angle, dda, data);
	return ;
}

void		print_map(char *game[11])
{
	int trash;

	trash = -1;
	while (++trash < 11)
		printf("%s\n", game[trash]);
	printf("\n");
}

void		print_screen(char game[21][60])
{
	int y;
	int	x;

	y = 0;
	printf("\n\n\n\n\n\n\n\n\n\n");
	while (y <= 20)
	{
		x = -1;
		while (++x < 60)
			printf("%c", game[y][x]);
		printf("\n");
		y++;
	}
}

int			closest_wall_dda(double angle, t_data *data)
{
	t_point	inter;
	t_point dda;
	double	x_angle;

	dda.x = data->player.pos.x;
	dda.y = data->player.pos.y;
	//printf("Player  = %f %f %f\n", data->player.pos.x, data->player.pos.y, data->player.angle);
	//print_map(data->game);
	//printf("DDA = \n%c", data->game[(int)dda.y][(int)dda.x]);
	get_walls_angle((data->player.angle - (FOV / 2) + angle), &dda, data);
	//printf("%c", data->game[(int)dda.y][(int)dda.x]);
	//data->screen[10][(int)angle] = texture + '0';
	//printf("%d", texture);
	/*printf("Angle 1 = %f %f\n", (double)(int)data->player.pos.x, (double)(int)data->player.pos.y);
	printf("Angle 2 = %f %f\n", (double)(int)data->player.pos.x + 1, (double)(int)data->player.pos.y);
	printf("Angle 3 = %f %f\n", (double)(int)data->player.pos.x + 1, (double)(int)data->player.pos.y + 1);
	printf("Angle 4 = %f %f\n", (double)(int)data->player.pos.x, (double)(int)data->player.pos.y + 1);*/
	//printf("%c %d %d\n", data->game[(int)dda.y][(int)dda.x], (int)dda.x, (int)dda.y);
	return (1);
}
