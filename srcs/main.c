/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:30:33 by magostin          #+#    #+#             */
/*   Updated: 2020/09/29 23:08:05 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"
#include "cub3D.h"

void					round_angle(double *f)
{
	while (*f > 360)
		*f -= 360;
	while (*f <= 0)
		*f += 360;
	//return (f);
}

void					draw_square(int x, int y, double size, unsigned int color, t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			draw_pt(x + i, y + j, data, color);
	}
}

void					draw_texture(int x, int y, t_texture texture, double mult, t_data *data)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (++i < texture.wth * texture.lth)
	{
		if (!(i % texture.wth))
			j++;
		draw_square(x + ((i % texture.wth) * mult), y + (j * mult), mult, texture.tab[i], data);
	}
}

double		ft_sub_abs(double a, double b)
{
	return (a - b < 0 ? b - a : a - b);
}

void		ft_clear_screen(t_data *data)
{
	int		i;

	i = -1;
	while (++i < (int)data->r.x * (int)data->r.y)
		data->draw[i] = 0;
}

t_point		to_point(double x, double y, double dist)
{
	t_point	a;

	a.x = x;
	a.y = y;
	a.dist = dist;
	return (a);
}

double		fix_angle(double angle)
{
	while (angle < 0)
		angle += 360;
	while (angle > 360)
		angle -= 360;
	return (angle);
}

void		update(t_data *data)
{
	ft_clear_screen(data);
	draw_screen(data);
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

int			test_pts(t_object *old_objs, int i, int j)
{
	if (old_objs[i].color == old_objs[j].color
	&& ((old_objs[i].p[1].x == old_objs[j].p[0].x && old_objs[i].p[1].y == old_objs[j].p[0].y)))
		return (1);
	return (0);
}

int				nbr_sprite(t_data *data)
{
	int			i;
	int			j;
	int			k;

	k = 0;
	i = -1;
	while (++i < MAP_H)
	{
		j = -1;
		while (++j < MAP_L)
			if (data->game[i][j] == '2')
				k++;
	}
	return (k);
}

t_object		*add_sprites(t_object *old_objs, t_data *data)
{
	t_object		*objs;
	int				i;
	int				c[2];
	
	data->n_sprite = nbr_sprite(data);
	if (!(objs = malloc(sizeof(t_object) * (data->n_objs + data->n_sprite))))
		return (0);
	i = -1;
	while (++i < data->n_objs)
		objs[i] = old_objs[i];
	i = 0;
	c[0] = -1;
	while (++c[0] < MAP_H)
	{
		c[1] = -1;
		while (++c[1] < MAP_L)
			if (data->game[c[0]][c[1]] == '2')
			{
				objs[data->n_objs + i].p[0].x = c[1];
				objs[data->n_objs + i].p[1].x = c[1] + 1;
				objs[data->n_objs + i].p[0].y = c[0];
				objs[data->n_objs + i].p[1].y = c[0] + 1;
				objs[data->n_objs + i].t = &data->sprt;
				objs[data->n_objs + i].type = 1;
				i++;
			}
	}
	free(old_objs);
	return (objs);
}

t_object		*compact_walls(t_object *old_walls, int size, t_data *data)
{
	t_object		*walls;
	int				i;
	int				j;

	if (!(walls = malloc(sizeof(t_object) * (size))))
		return (0);
	i = -1;
	j = 0;
	while (++i < data->n_objs)
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
	data->n_objs = j;
	free(old_walls);
	return (add_sprites(walls, data));
}

t_object		*merge_wall(t_object *old_walls, t_data *data)
{
	int		i;
	int		j;
	int		k;
	int		compt;

	i = -1;
	compt = 0;
	while (++i < data->n_objs)
	{
		old_walls[i].size = 0;
		if (old_walls[i].used == 0)
		{
			k = i;
			j = i;
			while (++j < data->n_objs)
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
	}
	return (compact_walls(old_walls, compt, data));
}

t_object		*fill_wall(char *game[11], t_object *walls, t_data *data)
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
					walls[compteur].type = 0;
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
					walls[compteur].type = 0;
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
					walls[compteur].type = 0;
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
					walls[compteur].type = 0;
					compteur++;
				}
			}
		}
	}
	//walls[compteur].p[0].x = -42;
	data->n_objs = compteur;
	return (merge_wall(walls, data));
}

t_object		*create_wall(char *game[11], t_data *data)
{
	int			c[2];
	int			nei[2];
	int			compteur;
	t_object		*walls;

	c[0] = -1;
	compteur = 0;
	while (++c[0] < MAP_H)
	{
		c[1] = -1;
		while (++c[1] < MAP_L)
			compteur += check_nei(game, c[0], c[1]);
	}
	if (!(walls = malloc(sizeof(t_object) * (compteur + 1))))
		return (NULL);
	return (fill_wall(game, walls, data));
}

void		create_sprites(t_data *data, char *game[11])
{
	int			i;
	int			j;
	int			k;

	data->sprite_nbr = 0;
	i = -1;
	while (++i < MAP_H)
	{
		j = -1;
		while (++j < MAP_L)
			if (game[i][j] == '2')
				data->sprite_nbr++;
	}
	if (!(data->sprites = malloc(sizeof(t_sprite) * (data->sprite_nbr))))
		return ;
	i = -1;
	k = -1;
	while (++i < MAP_H)
	{
		j = -1;
		while (++j < MAP_L)
		{
			if (game[i][j] == '2')
			{
				data->sprites[++k].pos.x = (double)j + 0.5;
				data->sprites[k].pos.y = (double)i + 0.5;
			}
		}
	}
}

int			main(void)
{
	t_data			data;
	t_object			*objs;
	t_point			a;
	t_point			b;
	t_point			c;
	t_point			d;
	t_point			inter;
	int 			trash;
	char			*game[11] =
	{
		"11111111111111111111",
		"10000000000010000001",
		"10000000000010000001",
		"10000200000010000001",
		"10000000200010000001",
		"10000002010010000001",
		"10002000011110000001",
		"10000000000000000001",
		"10000000200000000001",
		"10000000000000000001",
		"11111111111111111111"
	};

	trash = -1;
	while (++trash < 11)
		data.game[trash] = game[trash];
	int fd;

	fd = open("map1.cub", 'r');
	data.fov = FOV;
	data.player.angle = 0 - 9 * 3;
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
	data.player.pos.y = 5.2;
	create_sprites(&data, game);
	data.objs = create_wall(game, &data);
	t_texture texture_sprite;
	texture_sprite.ptr = mlx_xpm_file_to_image(data.mlx, "./texture/sprite.xpm", &(texture_sprite.wth), &(texture_sprite.lth));
	texture_sprite.tab = (unsigned int *)mlx_get_data_addr(texture_sprite.ptr, &trash, &trash, &trash);
	data.sprt = texture_sprite;
	data.sprites->t = &texture_sprite;

	update(&data);
	mlx_loop(data.mlx);
	return (0);
}