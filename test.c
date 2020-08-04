/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.nb2.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 16:39:nb0 by magostin          #+#    #+#             */
/*   Updated: 2020/07/1nb 17:16:21 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		ft_recursive_factorial(int nb)
{
	if (nb != 1)
		nb = ft_recursive_factorial(nb - 1) * nb;
	return (nb);
}

int		main(void)
{
	printf("%d\n", ft_recursive_factorial(17));
}