/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 19:03:58 by magostin          #+#    #+#             */
/*   Updated: 2020/10/01 17:11:19 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CUB3D_H__
# define __CUB3D_H__
# define KEY_Z 122
# define KEY_Q 113
# define KEY_S 115
# define KEY_D 100
# define ARR_L 65361
# define ARR_R 65363
# define HEIGHT 1080
# define LENGHT 1920
# define SPEED 1
# define WHITE 0x00FFFFFF
# define PI 3.14159265359
# define MAP_H 11
# define MAP_L 20
# define FOV 60
# define NORTH 0x2e86c1
# define EAST 0xb03a2e
# define WEST 0x28b463
# define SOUTH 0x6c3483

# define NO_ERR 0
# define ERR_RES 1
# define ERR_NO 2
# define ERR_SO 3
# define ERR_EA 4
# define ERR_WE 5
# define ERR_S 6
# define ERR_C 7
# define ERR_F 8

# define MULT 50

# include "mlx_int.h"
# include "mlx.h"
# include <math.h>

# include "get_next_line.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct			s_point
{
	double				x;
	double				y;
	double				dist;
}						t_point;

typedef struct			s_texture
{
	void				*ptr;
	int					wth;
	int					lth;
	unsigned int		*tab;
}						t_texture;

typedef struct			s_object
{
	t_point				p[2];
	t_texture			*t;
	t_point				inter;
	int					type;
	unsigned int 		color;
	int					size;
	int					used;
}						t_object;

typedef struct			s_sprite
{
	t_point				pos;
	t_texture			*t;
	struct s_sprite		*next;
}						t_sprite;

typedef struct			s_player
{
	t_point				pos;
	double				angle;
}						t_player;

typedef struct			s_data
{
	t_player			player;
	t_object			*objs;
	int					n_objs;
	int					n_sprite;
	t_texture			no;
	t_texture			so;
	t_texture			ea;
	t_texture			we;
	t_texture			sprt;
	t_sprite			*sprites;
	int					sprite_nbr;
	t_point				r;
	void				*mlx;
	void				*win;
	void				*img;
	unsigned int		*draw;
	unsigned int		color[2];
	int					update;
	char				*game[11];
	int					fov;
}						t_data;

void					draw_pt(int x, int y, t_data *data, unsigned int color);
void					draw_line(t_point a, t_point b, t_data *data, unsigned int color);
void					draw_circle(t_point center, int radius, t_data *data, unsigned int color);
void					draw_walls(t_data *data, int mult);
void					draw_screen(t_data *data);

int						hook_keydown(int key_code, t_data *data);
int						hook_close(t_data *data);
int						hook_loop (t_data *data);

t_point					get_intersect(t_point a, t_point b, t_object obj);
double					get_angle(t_point a, t_point player);

void					update(t_data *data);

int						parsing(int fd, t_data *data);
int						ft_atoi(const char *str);
double					get_dist(t_point a, t_point b);
double					ft_sub_abs(double a, double b);

int						closest_object_dda(double angle, t_data *data);
void					round_angle(double *f);
void					draw_square(int x, int y, double size, unsigned int color, t_data *data);


void					travel_algo(double f, t_point steps, t_data *data);

void					dda_test(double f, t_data *data);

#endif