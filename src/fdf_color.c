/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 10:27:45 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/15 13:27:16 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	radiant(int start, int end, double prcntg)
{
	return ((int)((1 - prcntg) * start + prcntg * end));
}

static double	percent(int start, int end, int current)
{
	double	position;
	double	distance;

	position = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	return (position / distance);
}

int 	get_clr(t_pixel current, t_pixel start, t_pixel end)
{
	int 	r;
	int 	g;
	int 	b;
	double	prcntg;

	if (start.rgba == end.rgba)
		return (start.rgba);
	if (abs(end.x -start.x) > abs(end.y - start.y))
		prcntg = percent(start.x, end.x, current.x);
	else
		prcntg = percent(start.y, end.y, current.y);
	r = radiant((start.rgba >> 24) & 0xFF, (end.rgba >> 24) & 0xFF, prcntg);
	g = radiant((start.rgba >> 16) & 0xFF, (end.rgba >> 16) & 0xFF, prcntg);
	b = radiant((start.rgba >> 8) & 0xFF, (end.rgba >> 8) & 0xFF, prcntg);
	return ((r << 24) | (g << 16) | b << 8 | 0xFF);
}

static int	zclr(double prcnt)
{
	if (prcnt < 0.1)
		return (CLR_LV_1);
	else if (prcnt < 0.2)
		return (CLR_LV_2);
	else if (prcnt < 0.3)
		return (CLR_LV_3);
	else if (prcnt < 0.4)
		return (CLR_LV_4);
	else if (prcnt < 0.5)
		return (CLR_LV_5);
	else if (prcnt < 0.6)
		return (CLR_LV_6);
	else if (prcnt < 0.7)
		return (CLR_LV_7);
	else if (prcnt < 0.8)
		return (CLR_LV_8);
	else if (prcnt < 0.9)
		return (CLR_LV_9);
	else
		return (CLR_LV_10);
}

void	apply_zclr(t_map *map)
{
	int		i;
	int		j;
	double	prcnt;
	
	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			prcnt = percent(map->min_height, map->max_height,
				map->original_points[i][j].z);
			map->original_points[i][j].zcolor = zclr(prcnt);
		}
	}
}
