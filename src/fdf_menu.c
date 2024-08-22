/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:55:00 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/22 20:55:02 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	menu(mlx_t *mlx)
{
	int		x;
	int		y;
	
	x = 40;
	y = 40;
	mlx_put_string(mlx, "CONTROLS:", x, y);
	mlx_put_string(mlx, "COLORS\t\t\t\t\t\t\t\tc", x, y += 55);
	mlx_put_string(mlx, "ZOOM\t\t\t\t\t\t\t\t\t\tuse mouse scroll or +-", x, y += 30);
	mlx_put_string(mlx, "MOVE\t\t\t\t\t\t\t\t\t\tarrows", x, y += 30);
	mlx_put_string(mlx, "SCALE HIGHT\t\t\ts + </>", x, y += 30);
	mlx_put_string(mlx, "ROTATE Z\t\t\t\t\t\tz + </>", x, y += 30);
	mlx_put_string(mlx, "RESET\t\t\t\t\t\t\t\t\tr", x, y += 30);
	mlx_put_string(mlx, "TOP VIEW\t\t\t\t\t\t1", x, y += 30);
	mlx_put_string(mlx, "FRONT VIEW\t\t\t\t2", x, y += 30);
	mlx_put_string(mlx, "SIDE VIEW\t\t\t\t\t3", x, y += 30);
	mlx_put_string(mlx, "ISO VIEW\t\t\t\t\t\t4", x, y += 30);
}
