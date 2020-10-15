/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 02:52:16 by magostin          #+#    #+#             */
/*   Updated: 2020/10/15 23:21:28 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef STRUCT_H
# define STRUCT_H

typedef struct		s_pixel
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}					t_pixel;

typedef struct		s_parsing
{
	int				f;
	int				c;
	int				t[5];
	int				r;
	int				player;
}					t_parsing;

typedef struct		s_map
{
	char			*line;
	struct s_map	*next;
}					t_map;

typedef struct		s_point
{
	double			x;
	double			y;
	double			dist;
}					t_point;

typedef struct		s_texture
{
	void			*ptr;
	int				wth;
	int				lth;
	unsigned int	*tab;
}					t_texture;

typedef struct		s_block
{
	t_point			inter;
	t_point			pos;
	int				texture;
	double			dist;
}					t_block;

typedef struct		s_key
{
	int				forward;
	int				backward;
	int				move_left;
	int				move_right;
	int				look_left;
	int				look_right;
	int				open_map;
	int				run;
	int				crouch;
	int				jump;
}					t_key;

typedef struct		s_wall
{
	t_point			p[2];
	t_texture		*t;
	t_point			inter;
	int				type;
	unsigned int 	color;
	int				size;
	int				used;
}					t_wall;

typedef struct		s_sprite
{
	t_point			p[2];
	t_texture		*t;
	t_point			pos;
	t_point			inter;
	int				x_slice;
	double			angle;
	double			dist;
	struct s_sprite	*next;
}					t_sprite;

typedef struct		s_player
{
	t_point			pos;
	double			angle;
	char			dir;
	double			h;
	double			jump;
}					t_player;

typedef struct		s_data
{
	t_point			r;
	int				max_x;
	int				max_y;
	t_texture		t[6];
	t_texture		gun[7];
	t_player		player;
	t_wall			*objs;
	int				n_objs;
	int				n_sprite;
	t_sprite		*sprites;
	int				sprite_nbr;
	void			*mlx;
	void			*win;
	void			*img;
	void			*img2;
	unsigned int	*draw;
	unsigned int	*draw2;
	unsigned int	color[2];
	double			*distance;
	t_point			*ray_inter;
	t_point			*ray_bounced;
	int				update;
	char			**game;
	t_point			game_size;
	int				fov;
	t_key			keys;
	int				tick;
	int				fd;
	int				average;
	t_parsing		pars;
	int				mirrored;
	int				bounced;
	int				y;
	int				show_map;
	int				test;
}					t_data;

#endif