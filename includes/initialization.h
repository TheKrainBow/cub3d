/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 04:07:22 by magostin          #+#    #+#             */
/*   Updated: 2020/10/09 05:11:18 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALIZATION_H
# define INITIALIZATION_H

# include "cub3D.h"

/*
** fill_walls.c
*/

t_wall			*fill_wall(t_wall *walls, t_data *data);
void			fill_wall_north(t_wall *walls, int *i, t_point c, t_data *data);
void			fill_wall_west(t_wall *walls, int *i, t_point c, t_data *data);
void			fill_wall_south(t_wall *walls, int *i, t_point c, t_data *data);
void			fill_wall_east(t_wall *walls, int *i, t_point c, t_data *data);

/*
** init_walls.c
*/

t_wall			*merge_wall(t_wall *old_walls, t_data *data);
t_wall			*compact_walls(t_wall *old_walls, int size, t_data *data);
t_wall			*create_wall(t_data *data);

/*
** utils_walls.c
*/


int				check_nei(int x, int y, t_data *data);
int				test_pts(t_wall *old_objs, int i, int j);
void			ft_init_player(t_data *data, int x, int y);

/*
** init_mlx.c
*/

void			init_mlx(t_data *data);
void			init_data(t_data *data);

#endif