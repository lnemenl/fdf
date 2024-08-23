/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:17:23 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/23 16:22:13 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	rot_z_axis(double *x, double *y, double angle)
{
	double	temp_x;
	double	temp_y;

	temp_x = *x * cos(angle) - *y * sin(angle);
	temp_y = *x * sin(angle) + *y * cos(angle);
	*x = temp_x;
	*y = temp_y;
}
