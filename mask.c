/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 04:20:29 by magostin          #+#    #+#             */
/*   Updated: 2020/10/03 21:16:33 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#define KEYS 8

int		check(int keys[KEYS], int i)
{
	int		j;
	int		k;
	
	j = -1;
	while (++j < KEYS)
	{
		k = j;
		while (++k < KEYS)
			if (keys[j] % i == keys[k] % i)
				return (1);
	}
	return (0);
}

int		main()
{
	int		i;
	int		j;
	int		keys[KEYS] = {122, 113, 115, 100, 65361, 65363, 65505, 32};

	j = 0;
	while (++j < 100 && check(keys, j));
	printf("%d\n", j);
	i = -1;
	while (++i < KEYS)
		printf("%-5d ", keys[i]);
	printf("\n");
	i = -1;
	while (++i < KEYS)
		printf("%-5d ", keys[i] % j - 1);
}