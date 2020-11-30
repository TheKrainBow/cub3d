/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 03:29:49 by magostin          #+#    #+#             */
/*   Updated: 2020/11/29 23:35:38 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

# include "cub3D.h"

/*
** math.c
*/

double			get_dist(t_point a, t_point b);
t_point			get_intersect(t_point b, t_point a, t_wall obj);
t_point			get_inter(t_point b, t_point a, t_sprite *obj);
int				check_point(t_point p, t_data *data);

/*
** raycasting.c
*/

void			closest_wall(int x, t_data *data);

/*
** sprite.c
*/

t_sprite		*new_sprite(t_point pos, t_data *data);
void			sprite_push_front(t_sprite **first, t_sprite *new);

/*
** raycasting_angle.c
*/

void			detect_dir(double f, t_data *data);
double			xtoa(int x, t_data *data);
double			rtoa(double rad);
double			ator(double a);
t_block			closest_wall_a(double f, t_point p, t_block wall, t_data *data);

/*
** wall.c
*/

char			wall_dir(double f, t_point p_pos, t_point wall, t_data *data);
double			wall_dir_return(int y, int x, t_point wall, t_point p_pos);
t_point			change_wall_pos(t_block wall);
t_point			wall_inter(t_block wall, t_point p, t_point a);
#endif
