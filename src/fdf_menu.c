/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 08:17:58 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/15 11:12:17 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	menu(mlx_t *mlx)
{
	int		x;
	int		y;
	
	x = 20;
	y = 20;
	mlx_put_string(mlx, "CONTROLS", x, y);
	mlx_put_string(mlx, "COLORS\t\t\t\t\t\t\t\tc", x, y += 35);
	mlx_put_string(mlx, "ZOOM\t\t\t\t\t\t\t\t\t\tuse mouse scroll or +-", x, y += 20);
	mlx_put_string(mlx, "MOVE\t\t\t\t\tarrows", x, y += 20);
	mlx_put_string(mlx, "SCALE HIGHT\t\t\t\t\t\t\t\ts + </>", x, y += 20);
	mlx_put_string(mlx, "ROTATE Z\t\t\t\t\t\tz + </>", x, y += 20);
	mlx_put_string(mlx, "RESET\t\t\t\t\t\t\t\t\tr", x, y += 30);	
}