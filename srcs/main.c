/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:30:33 by magostin          #+#    #+#             */
/*   Updated: 2020/10/08 16:40:18 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"
#include "cub3D.h"

void					round_angle(double *f)
{
	while (*f >= 360)
		*f -= 360;
	while (*f < 0)
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
			draw_pt(x + i - (size / 2), y + j - (size / 2), data, color);
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
	while (angle >= 360)
		angle -= 360;
	return (angle);
}

void		draw_crossair(t_data *data)
{
	int		i;
	t_point	center;

	i = -1;
	while (++i < 6 + 5)
	{
		draw_square(data->r.x / 2 - (2 * i), data->r.y / 2, 2, WHITE, data);
		draw_square(data->r.x / 2 + (2 * i), data->r.y / 2, 2, WHITE, data);
		draw_square(data->r.x / 2, data->r.y / 2 + (2 * i), 2, WHITE, data);
		draw_square(data->r.x / 2, data->r.y / 2 - (2 * i), 2, WHITE, data);
	}
	center.x = data->r.x / 2;
	center.y = data->r.y / 2;
	
	draw_square(data->r.x / 2, data->r.y / 2, 2, WHITE, data);
	draw_circle(center, 6 + 6, data, WHITE);
}

void		update(t_data *data)
{
	//ft_clear_screen(data);
	draw_screen(data);
	draw_crossair(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	data->update = 1;
}

int			check_nei(int x, int y, t_data *data)
{
	int compteur;

	compteur = 0;
	if (data->game[x][y] == '1')
	{
		if (x - 1 > 0 && data->game[x - 1][y] != '1')
			compteur++;
		if (y - 1 > 0 && data->game[x][y - 1] != '1')
			compteur++;
		if (y + 1 < data->game_size.y && data->game[x][y + 1] != '1')
			compteur++;
		if (x + 1 < data->game_size.x && data->game[x + 1][y] != '1')
			compteur++;
	}
	return (compteur);
}

int			test_pts(t_wall *old_objs, int i, int j)
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
	while (++i < data->game_size.x)
	{
		j = -1;
		while (++j < data->game_size.y)
			if (data->game[i][j] == '2')
				k++;
	}
	return (k);
}

t_wall		*add_sprites(t_wall *old_objs, t_data *data)
{
	t_wall		*objs;
	int				i;
	int				c[2];
	
	data->n_sprite = nbr_sprite(data);
	if (!(objs = malloc(sizeof(t_wall) * (data->n_objs + data->n_sprite))))
		return (0);
	i = -1;
	while (++i < data->n_objs)
		objs[i] = old_objs[i];
	i = 0;
	c[0] = -1;
	while (++c[0] < data->game_size.x)
	{
		c[1] = -1;
		while (++c[1] < data->game_size.y)
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

t_wall		*compact_walls(t_wall *old_walls, int size, t_data *data)
{
	t_wall		*walls;
	int				i;
	int				j;

	if (!(walls = malloc(sizeof(t_wall) * (size))))
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

t_wall		*merge_wall(t_wall *old_walls, t_data *data)
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

t_wall		*fill_wall(t_wall *walls, t_data *data)
{
	int			c[2];
	int			compteur;

	compteur = 0;
	c[0] = -1;
	while (++c[0] < data->game_size.x)
	{
		c[1] = -1;
		while (++c[1] < data->game_size.y)
		{
			if (data->game[c[0]][c[1]] == '1')
			{
				if (c[0] - 1 > 0 && data->game[c[0] - 1][c[1]] != '1')
				{
					walls[compteur].p[1].x = (c[1]);
					walls[compteur].p[1].y = (c[0]);
					walls[compteur].p[0].x = (c[1] + 1);
					walls[compteur].p[0].y = (c[0]);
					walls[compteur].color = WEST;
					walls[compteur].t = &data->we;
					walls[compteur].used = 0;
					walls[compteur].type = 0;
					compteur++;
				}
				if (c[1] - 1 > 0 && data->game[c[0]][c[1] - 1] != '1')
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
				if (c[1] + 1 < data->game_size.y && data->game[c[0]][c[1] + 1] != '1')
				{
					walls[compteur].p[1].x = (c[1] + 1);
					walls[compteur].p[1].y = (c[0]);
					walls[compteur].p[0].x = (c[1] + 1);
					walls[compteur].p[0].y = (c[0] + 1);
					walls[compteur].color = SOUTH;
					walls[compteur].t = &data->so;
					walls[compteur].used = 0;
					walls[compteur].type = 0;
					compteur++;
				}
				if (c[0] + 1 < data->game_size.x && data->game[c[0] + 1][c[1]] != '1')
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
	data->n_objs = compteur;
	return (merge_wall(walls, data));
}

void			ft_init_player(t_data *data, int x, int y)
{
	char		c;

	c = data->game[x][y];
	if (c == 'N')
	{
		data->player.angle = -90;
		data->player.pos.x = y + 0.5;
		data->player.pos.y = x + 0.5;
	}
	if (c == 'S')
	{
		data->player.angle = 90;
		data->player.pos.x = y + 0.5;
		data->player.pos.y = x + 0.5;
	}
	if (c == 'E')
	{
		data->player.angle = 0;
		data->player.pos.x = y + 0.5;
		data->player.pos.y = x + 0.5;
	}
	if (c == 'W')
	{
		data->player.angle = 180;
		data->player.pos.x = y + 0.5;
		data->player.pos.y = x + 0.5;
	}
	return ;
}

t_wall		*create_wall(t_data *data)
{
	int			c[2];
	int			nei[2];
	int			compteur;
	t_wall		*walls;

	c[0] = -1;
	compteur = 0;
	while (++c[0] < data->game_size.x)
	{
		c[1] = -1;
		while (++c[1] < data->game_size.y)
		{
			ft_init_player(data, c[0], c[1]);
			compteur += check_nei(c[0], c[1], data);
		}
	}
	if (!(walls = malloc(sizeof(t_wall) * (compteur + 1))))
		return (NULL);
	return (fill_wall(walls, data));
}

void		create_sprites(t_data *data)
{
	int			i;
	int			j;
	int			k;

	data->sprite_nbr = 0;
	i = -1;
	while (++i < data->game_size.x)
	{
		j = -1;
		while (++j < data->game_size.y)
			if (data->game[i][j] == '2')
				data->sprite_nbr++;
	}
	if (!(data->sprites = malloc(sizeof(t_sprite) * (data->sprite_nbr))))
		return ;
	i = -1;
	k = -1;
	while (++i < data->game_size.x)
	{
		j = -1;
		while (++j < data->game_size.y)
		{
			if (data->game[i][j] == '2')
			{
				data->sprites[++k].pos.x = (double)j + 0.5;
				data->sprites[k].pos.y = (double)i + 0.5;
			}
		}
	}
}

void		init_keys(t_data *data)
{
	int		i;
	
	i = -1;
	while (++i < 12)
		data->key_pressed[i] = 0;
	return ;
}

void		init_sprites(t_data *data);

int			main(void)
{
	t_data			data;
	t_wall			*objs;
	t_point			a;
	t_point			b;
	t_point			c;
	t_point			d;
	t_point			inter;
	int 			trash;
	int				coucou;

	data.fd = open("map1.cub", 'r');
	data.fov = FOV;
	data.player.angle = 0 - 9 * 3;
	data.player.angle = 0;
	data.player.pos.x = -1;
	data.player.pos.y = -1;
	data.mlx = mlx_init();
	if (parsing(&data) == 0)
		exit(0);
	data.win = mlx_new_window(data.mlx, (int)data.r.x, (int)data.r.y, "Cub3D");
	data.img = mlx_new_image(data.mlx, (int)data.r.x, (int)data.r.y);
	data.draw = (unsigned int *)mlx_get_data_addr(data.img, &coucou, &trash, &trash);
	mlx_hook(data.win, 17, 1L << 17, hook_close, &data);
	mlx_hook(data.win, 2, 1L << 0, hook_keydown, &data);
	mlx_hook(data.win, 3, 1L << 1, hook_keyup, &data);
	mlx_loop_hook(data.mlx, hook_loop, &data);
	mlx_do_key_autorepeaton(data.mlx);
	if (!(data.distance = malloc(sizeof(double) * data.r.x)))
		return (0);
	data.average = 0;
	//create_sprites(&data);
	data.objs = create_wall(&data);
	data.sprt.ptr = mlx_xpm_file_to_image(data.mlx, "./texture/shrek.xpm", &(data.sprt.wth), &(data.sprt.lth));
	data.sprt.tab = (unsigned int *)mlx_get_data_addr(data.sprt.ptr, &trash, &trash, &trash);
	init_keys(&data);
	data.player.pos.x = 13.14;
	data.player.pos.y = 5.5;
	update(&data);
	data.update = 0;
	data.tick = 0;
	mlx_loop(data.mlx);
	return (0);
}