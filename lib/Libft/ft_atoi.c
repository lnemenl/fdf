/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:55:58 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/22 20:56:01 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			sign;
	long long	n;
	long long	long_max;

	long_max = ((unsigned long long)(-1)) / 2;
	sign = 1;
	n = 0;
	while ((8 < *str && *str < 14) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while ('0' <= *str && *str <= '9')
	{
		if (n > long_max / 10)
			return ((sign > 0) * (-1));
		n = n * 10;
		if (n > long_max - (*str - '0'))
			return ((sign > 0) * (-1));
		n = n + ((*str++) - '0');
	}
	return ((int)(sign * n));
}
