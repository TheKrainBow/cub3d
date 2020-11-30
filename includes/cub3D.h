/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 19:03:58 by magostin          #+#    #+#             */
/*   Updated: 2020/11/30 01:17:38 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define KEY_Z 122
# define KEY_Q 113
# define KEY_S 115
# define KEY_D 100
# define ARR_L 65361
# define ARR_R 65363
# define QUIT 97
# define SPACE 32
# define SHIFT 65505
# define CTRL 65507
# define F 102

# define FOG 1

# define SPEED 1

# define WHITE 0x00FFFFFF
# define PI 3.14159265359
# define FOV 60

# define EAST 0
# define NORTH 1
# define WEST 2
# define SOUTH 3
# define SPRITE 4
# define GUN 5

# define NO_ERR 0
# define ERR_RES 1
# define ERR_NO 2
# define ERR_SO 3
# define ERR_EA 4
# define ERR_WE 5
# define ERR_S 6
# define ERR_C 7
# define ERR_F 8

# define C_F_ERR "C and F line must contain numbers, spaces, and commas only\n"
# define C_F_INV "C and F numbers must be positive, and less than 255.\n"

# define MULT 50

# include "mlx_int.h"
# include "mlx.h"
# include "struct.h"
# include "draw.h"
# include "algo.h"
# include "initialization.h"
# include "utils.h"
# include "get_next_line.h"
# include "parsing.h"

# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

void		update(t_data *data);

#endif