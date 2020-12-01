/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 02:45:17 by magostin          #+#    #+#             */
/*   Updated: 2020/12/01 12:58:47 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "cub3d.h"

/*
** draw_shapes.c
*/

void		draw_pt(int x, int y, t_data *data, t_pixel color);
void		draw_line(t_point a, t_point b, t_data *data, t_pixel color);
void		draw_circle(t_point c, int radius, t_data *data, t_pixel color);
void		draw_square(t_point p, double size, t_pixel color, t_data *data);
void		clear_screen(t_pixel color, t_data *data);

/*
** draw_color.c
*/

t_pixel		average_color(t_pixel first, t_pixel second, double ratio);
t_pixel		pixel(int r, int g, int b, int a);
t_pixel		fog_color(t_pixel color, double dist, t_data *data);

/*
** draw_objs.c
*/

void		draw_screen(t_data *data);
void		draw_height_wall(int x, t_wall obj, t_data *data);
void		draw_sprite(int x, t_sprite *sp, t_data *data);
void		sprite_slice(int x, int y, t_sprite *temp, t_data *data);
void		get_texture(int y, int x, t_data *data, t_wall obj);

/*
** draw_hud.c
*/

void		draw_hud(t_data *data);
void		draw_map(t_data *data);
void		draw_player_map(t_data *data);
void		draw_crosshair(int size, t_data *data);

t_point		point(double x, double y);
t_point		intersect(t_point b, t_point a, t_point c, t_point d);
double		map(double i, t_point range1, t_point range2);

void		draw_wall(int x, t_block wall, t_data *data);
void		draw_floor(int *i, int x, double y, t_data *data);
void		draw_ceilling(int *i, int x, double y, t_data *data);
t_pixel		get_pixel_color(t_point p, double y, t_block wall, t_data *data);

#endif
