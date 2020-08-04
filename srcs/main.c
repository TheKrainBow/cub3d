/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:30:33 by magostin          #+#    #+#             */
/*   Updated: 2020/07/26 21:03:26 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"
#include "cub3D.h"

void		ft_clear_screen(t_data *data)
{
	int		i;

	i = -1;
	while (++i < (int)data->r.x * (int)data->r.y / 2)
		data->draw[i] = data->color[0];
	while (++i < (int)data->r.x * (int)data->r.y)
		data->draw[i] = data->color[1];
}

void		update(t_data *data)
{
	t_point	a;
	int		i;
	int		scale = 50;

	data->update = 0;
	ft_clear_screen(data);
	/*data->player.pos.x *= scale;
	data->player.pos.y *= scale;
	a.x = (data->player.pos.x) + (cos((data->player.angle) * (PI / 180)) * 20);
	a.y = (data->player.pos.y) + (sin((data->player.angle) * (PI / 180)) * 20);
	draw_line(data->player.pos, a, data, WHITE);*/
	/*a.x = data->player.pos.x + (cos((data->player.angle - 30) * (PI / 180)) * 200) + 1;
	a.y = data->player.pos.y + (sin((data->player.angle - 30) * (PI / 180)) * 200) + 1;
	draw_line(data->player.pos, a, data, WHITE);
	a.x = data->player.pos.x + (cos((data->player.angle + 30) * (PI / 180)) * 200) + 1;
	a.y = data->player.pos.y + (sin((data->player.angle + 30) * (PI / 180)) * 200) + 1;
	draw_line(data->player.pos, a, data, WHITE);*/
	//draw_pt(data->player.pos.x, data->player.pos.y, data, WHITE);
	/*data->player.pos.x /= scale;
	data->player.pos.y /= scale;*/
	draw_screen(data);
	//draw_walls(data, scale);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	data->update = 1;
}

int			check_nei(char *game[11], int x, int y)
{
	int compteur;

	compteur = 0;
	if (game[x][y] == '1')
	{
		if (x - 1 > 0 && game[x - 1][y] != '1')
			compteur++;
		if (y - 1 > 0 && game[x][y - 1] != '1')
			compteur++;
		if (y + 1 < MAP_L && game[x][y + 1] != '1')
			compteur++;
		if (x + 1 < MAP_H && game[x + 1][y] != '1')
			compteur++;
	}
	return (compteur);
}

int			test_pts(t_wall *old_walls, int i, int j)
{
	if (old_walls[i].color == old_walls[j].color
	&& ((old_walls[i].p[1].x == old_walls[j].p[0].x && old_walls[i].p[1].y == old_walls[j].p[0].y)))
		return (1);
	return (0);
}

t_wall		*compact_wall(t_wall *old_walls, int size)
{
	t_wall		*walls;
	int			i;
	int			j;

	if (!(walls = malloc(sizeof(t_wall) * (size + 1))))
		return (0);
	i = -1;
	j = 0;
	while (old_walls[++i].p[0].x != -42)
		if (old_walls[i].used == 0)
		{
			walls[j].p[0] = old_walls[i].p[0];
			walls[j].p[1] = old_walls[i].p[1];
			walls[j].color = old_walls[i].color;
			walls[j].size = old_walls[i].size;
			walls[j].t = old_walls[i].t;
			walls[j].used = 1;
			j++;
		}
	walls[j].p[0].x = -42;
	free(old_walls);
	return(walls);
}

t_wall		*merge_wall(t_wall *old_walls)
{
	int		i;
	int		j;
	int		k;
	int		compt;

	i = 0;
	compt = 0;
	while (old_walls[i].p[0].x != -42)
	{
		old_walls[i].size = 0;
		if (old_walls[i].used == 0)
		{
			k = i;
			j = i;
			while (old_walls[++j].p[0].x != -42)
				if (test_pts(old_walls, k, j))
				{
					old_walls[j].used = 1;
					k = j;
					old_walls[i].size++;
				}
			old_walls[i].p[1].x = old_walls[k].p[1].x;
			old_walls[i].p[1].y = old_walls[k].p[1].y;
			compt++;
		}
		i++;
	}
	return (compact_wall(old_walls, compt));
}

t_wall		*fill_wall(char *game[11], t_wall *walls, t_data *data)
{
	int			c[2];
	int			compteur;

	compteur = 0;
	c[0] = -1;
	while (++c[0] < MAP_H)
	{
		c[1] = -1;
		while (++c[1] < MAP_L)
		{
			if (game[c[0]][c[1]] == '1')
			{
				if (c[0] - 1 > 0 && game[c[0] - 1][c[1]] != '1')
				{
					walls[compteur].p[0].x = (c[1]);
					walls[compteur].p[0].y = (c[0]);
					walls[compteur].p[1].x = (c[1] + 1);
					walls[compteur].p[1].y = (c[0]);
					walls[compteur].color = WEST;
					walls[compteur].t = &data->we;
					walls[compteur].used = 0;
					compteur++;
				}
				if (c[1] - 1 > 0 && game[c[0]][c[1] - 1] != '1')
				{
					walls[compteur].p[0].x = (c[1]);
					walls[compteur].p[0].y = (c[0]);
					walls[compteur].p[1].x = (c[1]);
					walls[compteur].p[1].y = (c[0] + 1);
					walls[compteur].color = NORTH;
					walls[compteur].t = &data->no;
					walls[compteur].used = 0;
					compteur++;
				}
				if (c[1] + 1 < MAP_L && game[c[0]][c[1] + 1] != '1')
				{
					walls[compteur].p[0].x = (c[1] + 1);
					walls[compteur].p[0].y = (c[0]);
					walls[compteur].p[1].x = (c[1] + 1);
					walls[compteur].p[1].y = (c[0] + 1);
					walls[compteur].color = SOUTH;
					walls[compteur].t = &data->so;
					walls[compteur].used = 0;
					compteur++;
				}
				if (c[0] + 1 < MAP_H && game[c[0] + 1][c[1]] != '1')
				{
					walls[compteur].p[0].x = (c[1]);
					walls[compteur].p[0].y = (c[0] + 1);
					walls[compteur].p[1].x = (c[1] + 1);
					walls[compteur].p[1].y = (c[0] + 1);
					walls[compteur].color = EAST;
					walls[compteur].t = &data->ea;
					walls[compteur].used = 0;
					compteur++;
				}
			}
		}
	}
	walls[compteur].p[0].x = -42;
	return (merge_wall(walls));
}

t_wall		*create_wall(char *game[11], t_data *data)
{
	int			c[2];
	int			nei[2];
	int			compteur;
	t_wall		*walls;

	c[0] = -1;
	compteur = 0;
	while (++c[0] < MAP_H)
	{
		c[1] = -1;
		while (++c[1] < MAP_L)
			compteur += check_nei(game, c[0], c[1]);
	}
	if (!(walls = malloc(sizeof(t_wall) * (compteur + 1))))
		return (NULL);
	return (fill_wall(game, walls, data));
}

int			main(void)
{
	t_data			data;
	t_wall			*walls;
	t_point			a;
	t_point			b;
	t_point			c;
	t_point			d;
	t_point			inter;
	int 			trash;
	char			*game[11] =
	{
		"11111111111111111111",
		"10000001000000010001",
		"10011101000000010001",
		"11110101000000010001",
		"10000000000000010001",
		"10000000000000000001",
		"10000000000000010001",
		"10000000000000010001",
		"10000000000000010001",
		"1N000000000000010001",
		"11111111111111111111"
	};
	trash = -1;
	while (++trash < 11)
		data.game[trash] = game[trash];
	int fd;

	fd = open("map1.cub", 'r');
	data.player.angle = 0;
	data.mlx = mlx_init();
	if (parsing(fd, &data) == 0)
		exit(0);
	data.win = mlx_new_window(data.mlx, (int)data.r.x, (int)data.r.y, "Cub3D");
	data.img = mlx_new_image(data.mlx, (int)data.r.x, (int)data.r.y);
	data.draw = (unsigned int *)mlx_get_data_addr(data.img, &trash, &trash, &trash);
	mlx_hook(data.win, 17, 1L << 17, hook_close, &data);
	mlx_hook(data.win, 2, 1L << 0, hook_keydown, &data);
	mlx_loop_hook(data.mlx, hook_loop, &data);
	mlx_do_key_autorepeaton(data.mlx);
	data.player.pos.x = 3.5;
	data.player.pos.y = 5.5;
	data.walls = create_wall(game, &data);
	update(&data);
	mlx_loop(data.mlx);
	return (0);
}