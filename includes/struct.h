/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 02:52:16 by magostin          #+#    #+#             */
/*   Updated: 2020/12/02 20:58:05 by magostin         ###   ########.fr       */
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

typedef struct		s_map
{
	char			*line;
	struct s_map	*next;
}					t_map;

typedef struct		s_parsing
{
	int				f;
	int				c;
	int				t[5];
	int				r;
	int				player;
	int				nbr_line;
	t_map			**game;
}					t_parsing;

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
	t_pixel			*tab;
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
	int				shoot;
}					t_key;

typedef struct		s_wall
{
	t_texture		*t;
	t_point			inter;
	unsigned int	color;
}					t_wall;

typedef struct		s_sprite
{
	t_point			p[2];
	t_texture		*t;
	t_point			pos;
	t_point			inter;
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
	double			gun;
}					t_player;

typedef struct		s_data
{
	t_point			r;
	int				max_x;
	int				max_y;
	t_texture		t[6];
	t_texture		gun[8];
	t_texture		health;
	t_player		player;
	t_sprite		*sprites;
	void			*mlx;
	void			*win;
	void			*img;
	void			*img2;
	t_pixel			*draw;
	t_pixel			*draw2;
	t_pixel			color[2];
	double			*distance;
	t_point			*ray_inter;
	t_point			*ray_bounced;
	char			**game;
	t_point			game_size;
	int				fov;
	t_key			keys;
	int				fd;
	int				average;
	t_parsing		pars;
	int				mirrored;
	int				bounced;
	int				y;
	int				show_map;
	int				save;
	int				mult;
}					t_data;

#endif
