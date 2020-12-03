/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 19:03:58 by magostin          #+#    #+#             */
/*   Updated: 2020/12/03 16:56:42 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define FORWARD 119
# define LEFT 97
# define BACKWARD 115
# define RIGHT 100
# define ARR_L 65361
# define ARR_R 65363
# define QUIT 65307
# define JUMP 32
# define RUN 65505
# define CROUCH 65507
# define FIRE 102
# define MAP 109

# define FOG 1

# define PI 3.14159265359
# define FOV 60

# define EAST 0
# define NORTH 1
# define WEST 2
# define SOUTH 3
# define SPRITE 4

# define C_F_ERR "C and F line must contain numbers, spaces, and commas only\n"
# define C_F_INV "C and F numbers must be positive, and less than 255.\n"

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

#endif
