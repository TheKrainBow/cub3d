/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 06:02:01 by magostin          #+#    #+#             */
/*   Updated: 2020/12/02 23:09:36 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "cub3d.h"

/*
** parsing.c
*/

void		parsing(t_data *data);
void		aff_err(char *str, t_data *data);

/*
** parsing_utils.c
*/

char		*ft_strtrim(char *s1, char const *set);
char		*ft_strstr(const char *haystack, const char *needle);

int			ft_whitespace(char c);
int			is_nb(char c);
t_map		*new_map_line(char *line);
void		map_push_back(t_map **first, t_map *new_map);
int			ft_check_line(char *line);

int			longest_line(t_map *game);
void		check_surround(int i, int j, t_data *data);
void		check_game(t_data *data);
void		create_game(t_data *data);
void		ft_map(char *line, t_data *data);

int			detect_param(char **line);
void		reso(char *line, t_data *data);
void		fill_texture(char *line, int n, t_data *data);
void		texture(char *line, t_data *data);
void		fill_color(char *line, int n, t_data *data);

void		ft_create_player(t_data *data, int x, int y, char c);
void		ft_init_player(t_data *data);
void		free_map(t_data *data);
void		check_parsing(t_data *data);

#endif
