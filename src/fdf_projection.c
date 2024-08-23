/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:29:36 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/23 11:29:13 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	map_pov(t_map *map, t_pixel *new, double x, double y, double z)
{
	if (map->iso_angle_x == 0 && map->iso_angle_y == -M_PI / 2)
	{
		new->x = (int)(x * map->zoom + map->center_x);
		new->y = (int)(y * map->zoom + map->center_y);
	}
	else if (map->iso_angle_x == 0 && map->iso_angle_y == 0)
	{
		new->x = (int)(x * map->zoom + map->center_x);
		new->y = (int)(-z * map->zoom + map->center_y);
	}
	else if (map->iso_angle_x == M_PI / 2 && map->iso_angle_y == 0)
	{
		new->x = (int)(y * map->zoom + map->center_x);
		new->y = (int)(-z * map->zoom + map->center_y);
	}
	else
	{
		new->x = (int)((x - y) * cos(map->iso_angle_x)
				* map->zoom + map->center_x);
		new->y = (int)((x + y) * sin(map->iso_angle_y) - z);
		new->y = (int)(new->y * map->zoom + map->center_y);
	}
}

void	set_map_pov(t_map *map, t_vertex *previous,
		t_pixel *new, double x, double y, double z)
{
	map_pov(map, new, x, y, z);
	if (map->use_height_color)
		new->rgba = previous->zcolor;
	else
		new->rgba = previous->mapcolor;
}
