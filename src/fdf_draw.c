/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:09:39 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/23 16:27:12 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	bresenham(mlx_image_t *image, t_pixel p1, t_pixel p2)
{
	int		error[2];
	t_pixel	crrnt;

	crrnt.x = p1.x;
	crrnt.y = p1.y;
	error[0] = abs(p2.x - p1.x) - abs(p2.y - p1.y);
	while (crrnt.x != p2.x || crrnt.y != p2.y)
	{
		if ((uint32_t)crrnt.x < image->width
			&& (uint32_t)crrnt.y < image->height)
			mlx_put_pixel(image, crrnt.x, crrnt.y, get_clr(crrnt, p1, p2));
		error[1] = error[0] * 2;
		if (error[1] > -abs(p2.y - p1.y))
		{
			error[0] -= abs(p2.y - p1.y);
			crrnt.x += (p1.x < p2.x);
			crrnt.x -= (p2.x < p1.x);
		}
		if (error[1] < abs(p2.x - p1.x))
		{
			error[0] += abs(p2.x - p1.x);
			crrnt.y += (p1.y < p2.y);
			crrnt.y -= (p2.y < p1.y);
		}
	}
}

void	map_project(t_map *map, int i, int j)
{
	t_vertex	*previous;
	t_pixel		*new;
	t_coord		coord;

	previous = &(map->original_points[i][j]);
	new = &(map->projected_points[i][j]);
	coord.x = previous->x;
	coord.y = previous->y;
	coord.z = previous->z * map->height_scale;
	rot_z_axis(&coord.x, &coord.y, map->rotation_z);
	set_map_pov(map, previous, new, coord);
}

static void	draw_line(t_fdf *fdf, int x, int y)
{
	if (y == 0 && x == 0)
		map_project(fdf->map, y, x);
	if (y + 1 < fdf->map->rows)
	{
		map_project(fdf->map, y + 1, x);
		bresenham(fdf->image, fdf->map->projected_points[y][x],
			fdf->map->projected_points[y + 1][x]);
	}
	if (x + 1 < fdf->map->cols)
	{
		if (y == 0)
			map_project(fdf->map, y, x + 1);
		bresenham(fdf->image, fdf->map->projected_points[y][x],
			fdf->map->projected_points[y][x + 1]);
	}
}

void	draw_image(void *param)
{
	int		i;
	int		j;
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	image_reset(fdf->image);
	i = -1;
	while (++i < fdf->map->rows)
	{
		j = -1;
		while (++j < fdf->map->cols)
		{
			draw_line(fdf, j, i);
		}
	}
}
