/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 06:02:01 by magostin          #+#    #+#             */
/*   Updated: 2020/11/30 01:30:18 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "cub3D.h"

/*
** parsing.c
*/

int			parsing(t_data *data);
int			aff_err(char *str, t_data *data);
/*
** parsing_utils.c
*/

char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strstr(const char *haystack, const char *needle);


int			ft_whitespace(char c);
int			is_nb(char c);
t_map		*new_map_line(char *line);
void		map_push_back(t_map **first, t_map *new);
int			ft_check_line(char *line);

int			longest_line(t_map *game);
void		check_surround(int i, int j, t_data *data);
void		check_game(t_data *data);
void		create_game(t_map *map, int nbr_line, t_data *data);
int			ft_map(char **line, t_data *data);

int			detect_param(char **line, t_data *data);
void		reso(char *line, t_data *data);
void		fill_texture(char *line, int n, t_data *data);
void		texture(char *line, t_data *data);
void		fill_color(char *line, int n, t_data *data);
#endif
