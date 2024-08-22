/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:11:56 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/22 17:00:50 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	hook_scroll(double xscale, double yscale, void *param)
{
	t_fdf	*fdf;
	
	(void)xscale;//added this one as it was complaining on macOS
	fdf = (t_fdf *)param;
	if (yscale > 0)
		fdf->map->zoom *= 1.02;
	else if (yscale < 0 && fdf->map->zoom * 0.98 > 0)
		fdf->map->zoom *= 0.98;
	xscale++;
}
static void	refresh_map(t_map *map)
{
	map->iso_angle_x = 0.46373398 / 2;
	map->iso_angle_y = 0.46373398;
	map->rotation_x = 0;
	map->rotation_y = 0;
	map->rotation_z = 0;
	map->center_x = WIDTH / 2;
	map->center_y = HEIGHT / 2;
	map->zoom = 1;
	map->height_scale = 1;
	map->use_height_color = false;
}
void	hook_events(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_R))
		refresh_map(fdf->map);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->map->center_x -= 7;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->map->center_x += 7;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		fdf->map->center_y -= 7;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->map->center_y += 7;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
		hook_scroll(0, 1, param);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS))
		hook_scroll(0, -1, param);
}


void hook_project(void *param)
{
    t_fdf *fdf;
    static int key_pressed = 0;

    fdf = (t_fdf *)param;
    if (mlx_is_key_down(fdf->mlx, MLX_KEY_C))
    {
        if (!key_pressed)
        {
            fdf->map->use_height_color = !(fdf->map->use_height_color);
            key_pressed = 1;
        }
    }
    else
    {
        key_pressed = 0;
    }
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_1)) // Top view
	{
		fdf->map->iso_angle_x = 0;
		fdf->map->iso_angle_y = M_PI / 2;
		fdf->map->rotation_z = 0;
		fdf->map->height_scale = 0; // Flatten the view for top-down perspective
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_2)) // Side view
	{
		fdf->map->iso_angle_x = 0;
		fdf->map->iso_angle_y = 0;
		fdf->map->rotation_z = M_PI / 2; // Rotate 90 degrees around Z-axis
		fdf->map->height_scale = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_3)) // Front view
	{
		fdf->map->iso_angle_x = 0;
		fdf->map->iso_angle_y = 0;
		fdf->map->rotation_z = 0;
		fdf->map->height_scale = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_4)) // Isometric view (original)
	{
		fdf->map->iso_angle_x = 0.46373398 / 2;
		fdf->map->iso_angle_y = 0.46373398;
		fdf->map->rotation_z = 0;
		fdf->map->height_scale = 1;
	}
}
void	hook_rotate(void *param)
{
	t_fdf	*fdf;
	double	sign;
	
	fdf = (t_fdf *)param;
	sign = 0;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_COMMA))
		sign = -1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_PERIOD))
		sign = 1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		fdf->map->height_scale += sign * 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Z))
		fdf->map->rotation_z += sign * 0.02;
}
