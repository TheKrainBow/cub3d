/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 04:53:01 by magostin          #+#    #+#             */
/*   Updated: 2020/10/09 05:01:03 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** convert a string to an int
*/
int		ft_atoi(const char *str)
{
	int i;
	int neg;
	int res;

	i = 0;
	res = 0;
	neg = 1;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
	|| str[i] == '\v' || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * neg);
}

/*
** Check if anykey is pressed
*/
int			check_keypressed(t_data *data)
{
	int		i;

	i = -1;
	while (++i < 12)
		if (data->key_pressed[i])
			return (1);
	return (0);
}

/*
** Check if the key is valid
*/
int			valid_key(int key_code)
{
	return (key_code == KEY_Z
	|| key_code == KEY_Q
	|| key_code == KEY_S
	|| key_code == KEY_D
	|| key_code == ARR_L
	|| key_code == ARR_R
	|| key_code == SPACE
	|| key_code == SHIFT);
}

/*
** Change the player position and angle depending on the keys pressed
*/
void		move_player(t_data *data)
{
	t_point		check;

	if (data->key_pressed[ARR_R % 14 - 1] || data->key_pressed[ARR_L % 14 - 1])
		data->player.angle = data->key_pressed[ARR_L % 14 - 1] ? data->player.angle - 0.00025 : data->player.angle + 0.00025;
	check.x = (cos(data->player.angle * (PI / 180)) / 7) * data->key_pressed[KEY_Z % 14 - 1] +
			(-cos(data->player.angle * (PI / 180)) / 7) * data->key_pressed[KEY_S % 14 - 1] +
			(cos((data->player.angle + 90) * (PI / 180)) / 7) * data->key_pressed[KEY_D % 14 - 1] + 
			(-cos((data->player.angle + 90) * (PI / 180)) / 7) * data->key_pressed[KEY_Q % 14 - 1];
	check.y = (sin(data->player.angle * (PI / 180)) / 7) * data->key_pressed[KEY_Z % 14 - 1] +
			(-sin(data->player.angle * (PI / 180)) / 7) * data->key_pressed[KEY_S % 14 - 1] +
			(sin((data->player.angle + 90) * (PI / 180)) / 7) * data->key_pressed[KEY_D % 14 - 1] + 
			(-sin((data->player.angle + 90) * (PI / 180)) / 7) * data->key_pressed[KEY_Q % 14 - 1];
	if (data->game[(int)data->player.pos.y][(int)(data->player.pos.x + check.x)] != '1')
		data->player.pos.x +=
			(cos(data->player.angle * (PI / 180)) / (100000 - 70000 * data->key_pressed[SHIFT % 14 - 1])) * data->key_pressed[KEY_Z % 14 - 1] +
			(-cos(data->player.angle * (PI / 180)) / (100000)) * data->key_pressed[KEY_S % 14 - 1] +
			(cos((data->player.angle + 90) * (PI / 180)) / (100000)) * data->key_pressed[KEY_D % 14 - 1] + 
			(-cos((data->player.angle + 90) * (PI / 180)) / (100000)) * data->key_pressed[KEY_Q % 14 - 1];
	if (data->game[(int)(data->player.pos.y + check.y)][(int)data->player.pos.x] != '1')
		data->player.pos.y +=
			(sin(data->player.angle * (PI / 180)) / (100000 - 70000 * data->key_pressed[SHIFT % 14 - 1])) * data->key_pressed[KEY_Z % 14 - 1] +
			(-sin(data->player.angle * (PI / 180)) / (100000)) * data->key_pressed[KEY_S % 14 - 1] +
			(sin((data->player.angle + 90) * (PI / 180)) / (100000)) * data->key_pressed[KEY_D % 14 - 1] + 
			(-sin((data->player.angle + 90) * (PI / 180)) / (100000)) * data->key_pressed[KEY_Q % 14 - 1];
}