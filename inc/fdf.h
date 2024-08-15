/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:37:44 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/15 13:50:09 by rkhakimu         ###   ########.fr       */
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

# define WIDTH			1920
# define HEIGHT			1080
# define TEXT_CLR		0xf3f6f4
# define BACKGROUND		0x13333700
# define MENU_BG_CLR	0x1E1E1EFF
# define CLR_LV_1		0x00FFFFFF
# define CLR_LV_2		0x099FFFFF
# define CLR_LV_3		0x0062FFFF
# define CLR_LV_4		0x0033FFFF
# define CLR_LV_5		0x9D00FFFF
# define CLR_LV_6		0xCC00FFFF
# define CLR_LV_7		0x6E0DD0FF
# define CLR_LV_8		0x9900FFFF
# define CLR_LV_9		0xFF00FFFF
# define CLR_LV_10		0xFF00CCFF

# define USAGE_FORMAT	"Format:\n\t./fdf maps/filename.fdf"
# define MALLOC_ERR		"Malloc failed"
# define MAP_ERR		"Map is invalid"
# define FILE_OPEN_ERR	"Unable to open file"

typedef struct	s_vertex
{
	double  x;
	double  y;
	double  z;
	int     mapcolor;
	int     zcolor;
}				t_vertex;

typedef struct	s_pixel
{
	int     x;
	int     y;
	int     z;
	int     rgba;
}				t_pixel;

typedef struct	s_map
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
	double		hight_scale;
	t_vertex	**original_points;
	t_pixel		**projected_points;
}				t_map;

typedef struct s_fdf
{
	mlx_t       *mlx;
	t_map       *map;
	mlx_image_t *image;
}               t_fdf;

/* fdf_main.c */
void	map_init(t_map *map);

/* fdf_parse.c */
void	map_parse(int fd, t_map *map);
void	map_size(int fd, t_map *map);

/* fdf_error.c */
void	arr_free(void **ptr, size_t len);
void	map_free(t_map *map);//free_map
void	failSafe(const char *message);
void	map_error(int fd, t_map *map, char *message);

/* fdf_draw.c */
void	map_project(t_map *map, int i, int j);
void	draw_image(void *param);
void	menu(mlx_t *mlx);

/* fdf_rotate.c */
// void        rot_x_axis(double *y, double *z, double alpha);//rotate_x
// void        rot_y_axis(double *x, double *z, double beta);//rotate_y
void	rot_z_axis(double *x, double *y, double angle);

/* fdf_hooks.c */
void	hook_events(void *param);//ft_hook
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


/* fdf_color.c */
int		get_clr(t_pixel current, t_pixel start, t_pixel end);
void	apply_zclr(t_map *map);


#endif