/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:54:18 by magostin          #+#    #+#             */
/*   Updated: 2020/12/01 12:58:04 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct		s_nxtlne
{
	int				fd;
	char			*line;
}					t_nxtlne;

char				*ft_strjoin(char const *s1, char const *s2);
int					get_next_line(int fd, char **line);
char				*ft_strchr(char *s, int c);
char				*ft_strdup(const char *str);
char				*ft_strndup(const char *s, int n);
char				*ft_strnew(size_t size);
int					ft_strlen(const char *str);
#endif
