/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 04:07:22 by magostin          #+#    #+#             */
/*   Updated: 2020/12/01 12:56:32 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALIZATION_H
# define INITIALIZATION_H

# include "cub3D.h"

/*
** init_mlx.c
*/

void			init_keys(t_data *data);
void			init_mlx(t_data *data);
void			init_data(t_data *data);
void			init_parsing(t_data *data);
void			init_gun(t_data *data);

#endif
