/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 06:02:01 by magostin          #+#    #+#             */
/*   Updated: 2020/10/10 04:53:42 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

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
#endif