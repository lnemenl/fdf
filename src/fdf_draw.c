/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:54:19 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/22 22:22:30 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void 	bresenham(mlx_image_t *image, t_pixel p1, t_pixel p2)
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

static void map_pov(t_map *map, t_pixel *new, double x, double y, double z)
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
        new->x = (int)((x - y) * cos(map->iso_angle_x) * 
			map->zoom + map->center_x);
        new->y = (int)((x + y) * sin(map->iso_angle_y) - z);
        new->y = (int)(new->y * map->zoom + map->center_y);
    }
}

static void set_map_pov(t_map *map, t_vertex *previous,
    t_pixel *new, double x, double y, double z)
{
    map_pov(map, new, x, y, z);
    if (map->use_height_color)
        new->rgba = previous->zcolor;
    else
        new->rgba = previous->mapcolor;
}


void    map_project(t_map *map, int i, int j)
{
    t_vertex    *previous;
    t_pixel     *new;
    double      x;
    double      y;
    double      z;
    double      temp_x;
    double      temp_y;

    previous = &(map->original_points[i][j]);
    new = &(map->projected_points[i][j]);
    x = previous->x;
    y = previous->y;
    z = previous->z * map->height_scale;
    temp_x = x * cos(map->rotation_z) - y * sin(map->rotation_z);
    temp_y = x * sin(map->rotation_z) + y * cos(map->rotation_z);
    x = temp_x;
    y = temp_y;
    set_map_pov(map, previous, new, x, y, z);
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



/*void	map_project(t_map *map, int i, int j)
{
	t_vertex	*previous;
	t_vertex	temp;
	t_pixel		*new;
	
	previous = &(map->original_points[i][j]);
	new = &(map->projected_points[i][j]);
	temp.x = previous->x;
	temp.y = previous->y;
	temp.z = previous->z * map->height_scale;
	rot_z_axis(&temp.x, &temp.y, map->rotation_z);
	new->x = (int)((temp.x * map->zoom - temp.y * map->zoom)
		* cos(map->iso_angle_x) + map->center_x);
	new->y = (int)(-temp.z * map->zoom
			+ (temp.x * map->zoom + temp.y * map->zoom)
			* sin(map->iso_angle_y) + map->center_y);
	if (map->use_height_color)
		new->rgba = previous->zcolor;
		else
			new->rgba = previous->mapcolor;
}*/
