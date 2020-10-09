/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 04:35:22 by magostin          #+#    #+#             */
/*   Updated: 2020/10/09 05:01:17 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3D.h"

/*
** hook.c
*/

int			hook_loop(t_data *data);
int			hook_close(t_data *data);
int			hook_keyup(int key_code, t_data *data);
int			hook_keydown(int key_code, t_data *data);

/*
** utils.c
*/

int			ft_atoi(const char *str);
int			check_keypressed(t_data *data);
int			valid_key(int key_code);
void		move_player(t_data *data);

#endif