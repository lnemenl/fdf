/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:10:06 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/23 11:10:09 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/Libft/libft.h"

# define WIDTH			3840
# define HEIGHT			2160
# define TEXT_CLR		0xf3f6f4FF
# define BACKGROUND		0x0E2F4400
# define MENU_BG_CLR	0x1E1E1EFF
# define CLR_LV_1		0xFF00CCFF
# define CLR_LV_2		0xFF00FFFF
# define CLR_LV_3		0x9900FFFF
# define CLR_LV_4		0x6E0DD0F
# define CLR_LV_5		0xCC00FFFF
# define CLR_LV_6		0x9D00FFFF
# define CLR_LV_7		0xF0033FFF
# define CLR_LV_8		0x0062FFFF
# define CLR_LV_9		0x099FFFFF
# define CLR_LV_10		0x00FFFFFF

# define USAGE_FORMAT	"Format:\n\t./fdf maps/filename.fdf"
# define MALLOC_ERR		"Malloc failed"
# define MAP_ERR		"Map is invalid"
# define FILE_OPEN_ERR	"Unable to open file"

typedef struct s_vertex
{
	double	x;
	double	y;
	double	z;
	int		mapcolor;
	int		zcolor;
}				t_vertex;

typedef struct s_pixel
{
	int	x;
	int	y;
	int	z;
	int	rgba;
}				t_pixel;

typedef struct s_map
{
	int			rows;
	int			cols;
	int			max_height;
	int			min_height;
	bool		use_height_color;
	double		center_x;
	double		center_y;
	double		interval;
	double		iso_angle_x;
	double		iso_angle_y;
	double		rotation_x;
	double		rotation_y;
	double		rotation_z;
	double		zoom;
	double		height_scale;
	t_vertex	**original_points;
	t_pixel		**projected_points;
}				t_map;

typedef struct s_fdf
{
	mlx_t		*mlx;
	t_map		*map;
	mlx_image_t	*image;
}				t_fdf;

/* fdf_main.c */
void	map_init(t_map *map);

/* fdf_parse.c */
void	map_parse(int fd, t_map *map);
void	map_size(int fd, t_map *map);

/* fdf_error.c */
void	arr_free(void **ptr, size_t len);
void	map_free(t_map *map);
void	fail_safe(const char *message);
void	map_error(int fd, t_map *map, char *message);

/* fdf_draw.c */
void	map_project(t_map *map, int i, int j);
void	draw_image(void *param);
void	menu(mlx_t *mlx);

/* fdf_hooks.c */
void	hook_events(void *param);
void	hook_scroll(double xscale, double yscale, void *param);
void	hook_rotate(void *param);
void	hook_project(void *param);

/* fdf_utils.c*/
void	to_upper(unsigned int i, char *c);
void	image_reset(mlx_image_t *image);
int		fname_valid(const char *filename);
int		ft_min(int a, int b);
int		ft_max(int a, int b);
int		ft_atoi_base(const char *str, const char *base);
void	refresh_map(t_map *map);

/* fdf_color.c */
int		get_clr(t_pixel current, t_pixel start, t_pixel end);
void	apply_zclr(t_map *map);

void	map_pov(t_map *map, t_pixel *new, double x, double y, double z);
void	set_map_pov(t_map *map, t_vertex *previous,
			t_pixel *new, double x, double y, double z);

#endif