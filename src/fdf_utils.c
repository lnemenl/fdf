/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 08:41:19 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/15 20:11:24 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int 	fname_valid(const char *filename)
{
	int		len;
	
	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	filename += len - 4;
	return (ft_strncmp(filename, ".fdf", 4) == 0);
}

void	to_upper(unsigned int i, char *c)
{
	(void)i;
	*c = ft_toupper(*c);
}

void	image_reset(mlx_image_t *image)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < image->height)
	{
		j = 0;
		while ( j < image->width)
		{
			mlx_put_pixel(image, j, i, BACKGROUND);
			j++;
		}
		i++;
	}
}
int ft_atoi_base(const char *str, const char *base)
{
	int		neg;
	int		res;
	int		nbase;

	while (*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	neg = 1;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			neg = -1;
	nbase = ft_strlen(base);
	res = 0;
	while (str && *str && ft_strchr(base, *str))
	{
		res = res * nbase + (ft_strchr(base, *str) - base);
		str++;
	}
	return (res * neg);
}
