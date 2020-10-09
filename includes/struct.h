/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 02:52:16 by magostin          #+#    #+#             */
/*   Updated: 2020/10/09 03:27:07 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef STRUCT_H
# define STRUCT_H

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
}					t_player;

typedef struct		s_data
{
	t_point			r;
	t_texture		ea;
	t_texture		so;
	t_texture		no;
	t_texture		we;
	t_player		player;
	t_texture		sprt;
	t_wall			*objs;
	int				n_objs;
	int				n_sprite;
	t_sprite		*sprites;
	int				sprite_nbr;
	void			*mlx;
	void			*win;
	void			*img;
	unsigned int	*draw;
	unsigned int	color[2];
	double			*distance;
	int				update;
	char			**game;
	t_point			game_size;
	int				fov;
	int				key_pressed[13];
	int				tick;
	int				fd;
	int				average;
}					t_data;

#endif