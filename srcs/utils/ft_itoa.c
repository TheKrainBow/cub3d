/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 23:16:30 by magostin          #+#    #+#             */
/*   Updated: 2020/11/19 22:04:46 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	*ft_itoa2(int i, long int n, int neg)
{
	char	*dest;
	int		j;

	j = 0;
	if (!(dest = malloc((i + 1) * sizeof(char))))
		return (0);
	if (neg == -1)
	{
		dest[0] = '-';
		n *= neg;
		j++;
		i--;
	}
	dest[i] = 0;
	i--;
	while (i >= 0)
	{
		dest[j] = ((n / (int)pow(10, i)) % 10) + '0';
		j++;
		i--;
	}
	dest[j] = 0;
	return (&dest[0]);
}

char		*ft_itoa(int n)
{
	int			i;
	long int	temp;
	int			neg;
	long int	numb;

	temp = n;
	i = 0;
	neg = 1;
	numb = n;
	if (temp < 0)
	{
		i++;
		temp *= -1;
		neg = -1;
	}
	while (temp >= 10)
	{
		i++;
		temp /= 10;
	}
	i++;
	return (ft_itoa2(i, numb, neg));
}