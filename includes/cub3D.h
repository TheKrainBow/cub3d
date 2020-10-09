/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 19:03:58 by magostin          #+#    #+#             */
/*   Updated: 2020/10/09 04:58:58 by magostin         ###   ########.fr       */
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
# define SPACE 32
# define SHIFT 65505
# define FOG 0

# define SPEED 1

# define WHITE 0x00FFFFFF
# define PI 3.14159265359
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
# include "struct.h"
# include "draw.h"
# include "algo.h"
# include "initialization.h"
# include "utils.h"
# include "get_next_line.h"

# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

int			parsing(t_data *data);
/*void		ft_init_player(t_data *data, int x, int y);

int			hook_keydown(int key_code, t_data *data);
int			hook_keyup(int key_code, t_data *data);
int			hook_close(t_data *data);
int			hook_loop(t_data *data);


double		get_dist(t_point a, t_point b);
double		ft_atan2(t_point a, t_point player);

void		find_sprite(int f, t_point a, t_data *data);


int			check_nei(int x, int y, t_data *data);
int			test_pts(t_wall *old_objs, int i, int j);


int			valid_key(int key_code);
void		move_player(t_data *data);
int			check_keypressed(t_data *data);*/

void		update(t_data *data);
#endif