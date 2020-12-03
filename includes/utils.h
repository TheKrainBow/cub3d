/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 04:35:22 by magostin          #+#    #+#             */
/*   Updated: 2020/12/03 16:56:17 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

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
double		fix_angle(double ang);

/*
** utils_walls.c
*/

int			check_nei(int x, int y, t_data *data);
int			test_pts(t_wall *old_objs, int i, int j);

void		ft_save(t_data *data);

char		*ft_itoa(int n);

t_point		point(double x, double y);
char		game(t_point p, t_data *data);
void		my_free(void *ptr);
char		*ft_strchr(char *s, int c);
void		exit_game(t_data *data);
int			ft_strlen(char *str);
void		ft_putstr(char *str);
void		update(t_data *data);

#endif
