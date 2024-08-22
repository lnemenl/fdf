/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A1.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:59:56 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/22 21:07:02 by rkhakimu         ###   ########.fr       */
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
	double		height_scale;
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
void	map_free(t_map *map);
void	failSafe(const char *message);
void	map_error(int fd, t_map *map, char *message);

/* fdf_draw.c */
void	map_project(t_map *map, int i, int j);
void	draw_image(void *param);
void	menu(mlx_t *mlx);

/* fdf_rotate.c */
void	rot_z_axis(double *x, double *y, double angle);

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


/* fdf_color.c */
int		get_clr(t_pixel current, t_pixel start, t_pixel end);
void	apply_zclr(t_map *map);

#endif/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:59:56 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/22 20:59:58 by rkhakimu         ###   ########.fr       */
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
	double		height_scale;
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
void	map_free(t_map *map);
void	failSafe(const char *message);
void	map_error(int fd, t_map *map, char *message);

/* fdf_draw.c */
void	map_project(t_map *map, int i, int j);
void	draw_image(void *param);
void	menu(mlx_t *mlx);

/* fdf_rotate.c */
void	rot_z_axis(double *x, double *y, double angle);

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


/* fdf_color.c */
int		get_clr(t_pixel current, t_pixel start, t_pixel end);
void	apply_zclr(t_map *map);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:54:01 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/22 20:54:06 by rkhakimu         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:54:19 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/22 20:54:23 by rkhakimu         ###   ########.fr       */
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

void	map_project(t_map *map, int i, int j)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:54:29 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/22 20:54:32 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void    arr_free(void **tab, size_t len)
{
    size_t  i;
    
    i = 0;
    while (i < len && tab[i] != NULL)
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}
void    map_free(t_map *map)
{
    if (!map)
        return ;
    if (map->projected_points)
        arr_free((void **)map->projected_points, map->rows);
    if (map->original_points)
        arr_free((void **)map->original_points, map->rows);
    free(map);
}

void    failSafe(const char *message)
{
    if (errno == 0)
    {
        ft_putstr_fd("fdf: ", 2);
        ft_putendl_fd((char *)message, 2);
    }
    else
        perror("fdf");
    exit (1);
}

void    map_error(int fd, t_map *map, char *message)
{
    close(fd);
    map_free(map);
    failSafe(message);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:54:42 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/22 20:54:47 by rkhakimu         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:54:53 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/22 20:54:55 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	table_memalloc(t_map *map)
{
	int i;
	
	map->original_points = malloc(sizeof(t_vertex *) * map->rows);
	map->projected_points = malloc(sizeof(t_pixel *) * map->rows);
	if (!(map->projected_points) ||!(map->original_points))
	{
		map_free(map);
		failSafe(MALLOC_ERR);
	}
	i = -1;
	while (++i < map->rows)
	{
		map->original_points[i] = malloc(sizeof(t_vertex) * map->cols);
		map->projected_points[i] = malloc(sizeof(t_pixel) * map->cols);
		if (!(map->projected_points[i]) || !(map->original_points))
		{
			if (i + 1 < map->rows)
			{
				map->original_points[i + 1] = NULL;
				map->projected_points[i + 1] =  NULL;
			}
			map_free(map);
			failSafe(MALLOC_ERR);
		}
	}
}

void	map_init(t_map *map)
{
	map->iso_angle_x = 0.46373398 / 2;
	map->iso_angle_y = 0.46373398;
	map->rotation_x = 0;
	map->rotation_x = 0;
	map->rotation_z = 0;
	map->center_x = WIDTH / 2;
	map->center_y = HEIGHT / 2;
	map->zoom = 1;
	map-> height_scale = 1;
	map->use_height_color = false;
	map->max_height = INT_MIN;
	map->min_height = INT_MAX;
	map->rows = 0;
	map->cols = 0;
	map->projected_points = NULL;
	map->original_points = NULL;
}

static t_map	*input_parse(char *filename)
{
	int		fd;
	t_map	*map;
	
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		failSafe(FILE_OPEN_ERR);
	map = malloc(sizeof(t_map));
	if (!map)
	{
		close(fd);
		failSafe(MALLOC_ERR);
	}
	map_init(map);
	map_size(fd, map);
	close(fd);
	table_memalloc(map);
	map->interval = ft_min(WIDTH / map->cols, HEIGHT / map->rows) / 4;
	map->interval = ft_max(2, map->interval);
	fd = open(filename, O_RDONLY);
	map_parse(fd, map);
	close(fd);
	apply_zclr(map);
	return(map);
}

static t_fdf	*fdf_init(char *filename)
{
	static t_fdf	fdf;
	
	fdf.map = input_parse(filename);
	fdf.mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!fdf.mlx)
	{
		map_free(fdf.map);
		failSafe(mlx_strerror(mlx_errno));
	}
	fdf.image = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	if (!fdf.image)
	{
		map_free(fdf.map);
		mlx_close_window(fdf.mlx);
		failSafe(mlx_strerror(mlx_errno));
	}
	return (&fdf);
}

int32_t	main(int ac, char **av)
{
	t_fdf	*fdf;
	
	if (ac != 2 || !fname_valid(av[1]))
		failSafe(USAGE_FORMAT);
	fdf = fdf_init(av[1]);
	menu(fdf->mlx);
	draw_image(fdf);
	if (mlx_image_to_window(fdf->mlx, fdf->image, 0, 0) == -1)
	{
		map_free(fdf->map);
		mlx_close_window(fdf->mlx);
		failSafe(mlx_strerror(mlx_errno));
	}
	mlx_loop_hook(fdf->mlx, &hook_events, fdf);
	mlx_loop_hook(fdf->mlx, &hook_rotate, fdf);
	mlx_loop_hook(fdf->mlx, &hook_project, fdf);
	mlx_scroll_hook(fdf->mlx, &hook_scroll, fdf);
	mlx_loop_hook(fdf->mlx, &draw_image, fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	map_free(fdf->map);
	return (0);		
}


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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_minmax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:55:10 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/22 20:55:13 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	ft_min(int a, int b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}

int	ft_max(int a, int b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:55:18 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/22 20:55:20 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	clr_parse(int fd, t_map *map, char *arr2)
{
	while (*arr2 == '-')
		arr2++;
	while (ft_isdigit(*arr2))
		arr2++;
	if (*arr2 == ',')
		arr2++;
	else
		return (0xFFFFFFFF);
	if ((ft_strncmp(arr2, "0X", 2) && ft_strncmp(arr2, "0x", 2)))
		map_error(fd, map, MAP_ERR);
	arr2 += 2;
	ft_striteri(arr2, &to_upper);
	return ((ft_atoi_base(arr2, "0123456789ABCDEF") << 8) | 0xFF);		
}

static void column_parse(int fd, t_map *map, char **arr, int i)
{
	t_vertex	*point;
	int			center_x;
	int			center_y;
	int			j;
	
	j = -1;
	while (++j < map->cols)
	{
		if(!ft_isdigit(*arr[j]) && *arr[j] != '-')
			map_error(fd, map, MAP_ERR);
		point = &(map->original_points[i][j]);
		center_x = (map->cols - 1) * map->interval / 2;
		center_y = (map->rows - 1) * map->interval / 2;
		point->x = (double)j * (map->interval) - center_x;
		point->y = (double)i * (map->interval) - center_y;
		point->z = (double)ft_atoi(arr[j]) * (map->interval);//changed from i to j, mindblowing
		map->max_height = ft_max(map->max_height, point->z);
		map->min_height = ft_min(map->min_height, point->z);
		point->mapcolor = clr_parse(fd, map, arr[j]);
	}
}

void	map_parse(int fd, t_map * map)
{
	char	**arr;
	char	*line;
	char	*temp;
	int		i;
	
	i = -1;
	while (++i < map->rows)
	{
		temp = get_next_line(fd);
		if (!temp)
			map_error(fd, map, MALLOC_ERR);
		line = ft_strtrim(temp, "\n");
		free(temp);
		if (!line)
			map_error(fd, map, MALLOC_ERR);
		arr = ft_split(line, ' ');
		free(line);
		if(!arr)
			map_error(fd, map, MALLOC_ERR);
		column_parse(fd, map, arr, i);
		arr_free((void **)arr, map->cols);
	}
}

static int	get_columns(int fd, t_map *map, char *line)
{
	char	**arr;
	char	*temp;
	int		i;
	
	temp = ft_strtrim(line, "\n");
	free(line);
	if(!temp)
		map_error(fd, map, MALLOC_ERR);
	arr = ft_split(temp, ' ');
	free(temp);
	if(!arr)
		map_error(fd, map, MALLOC_ERR);
	i = 0;
	while (arr[i])
	{
		map->max_height = ft_max(map->max_height, ft_atoi(arr[i]));
		map->min_height = ft_min(map->min_height, ft_atoi(arr[i]));
		i++;
	}
	arr_free((void **)arr, i);
	return (i);
}

void	map_size(int fd, t_map *map)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		map_error(fd, map, MALLOC_ERR);
	map->cols = get_columns(fd, map, line);
	if (map->cols == 0)
		map_error(fd, map, MAP_ERR);
	map->rows = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map->rows++;
		if (map->cols != get_columns(fd, map, line))
			map_error(fd, map, MAP_ERR);
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:55:26 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/22 20:55:29 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	rot_z_axis(double *x, double *y, double angle)
{
	double	previous_x;
	double	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(angle) - previous_y * sin(angle);
	*y = previous_x * sin(angle) + previous_y * cos(angle);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:55:33 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/22 20:55:35 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int 	fname_valid(const char *filename)
{
	int		len;
	
	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	filename += len - 4;
	return (ft_strncmp(filename, ".fdf", 4) == 0);
}

void	to_upper(unsigned int i, char *c)
{
	(void)i;
	*c = ft_toupper(*c);
}

void	image_reset(mlx_image_t *image)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < image->height)
	{
		j = 0;
		while ( j < image->width)
		{
			mlx_put_pixel(image, j, i, BACKGROUND);
			j++;
		}
		i++;
	}
}
int ft_atoi_base(const char *str, const char *base)
{
	int		neg;
	int		res;
	int		nbase;

	while (*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	neg = 1;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			neg = -1;
	nbase = ft_strlen(base);
	res = 0;
	while (str && *str && ft_strchr(base, *str))
	{
		res = res * nbase + (ft_strchr(base, *str) - base);
		str++;
	}
	return (res * neg);
}


# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/22 20:55:42 by rkhakimu          #+#    #+#              #
#    Updated: 2024/08/22 20:55:45 by rkhakimu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -Wunreachable-code -Ofast
MLX_DIR		:= ./lib/MLX42
MLX		:= $(MLX_DIR)/build/libmlx42.a
LIBFT_DIR	:= ./lib/Libft
LIBFT 	:= $(LIBFT_DIR)/libft.a
HEADERS	:= -I ./inc -I $(MLX_DIR)/include/MLX42 -I $(LIBFT_DIR)/inc
UNAME_S	:= $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS	:= -L$(LIBFT_DIR) -lft $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
endif
ifeq ($(UNAME_S),Darwin)
	LIBS	:= -L$(LIBFT_DIR) -lft $(MLX_DIR)/build/libmlx42.a \
	-Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.4/lib/" -pthread -lm
endif
SRC_DIR	:= src
SRC		:= fdf_main.c \
			fdf_draw.c \
			fdf_error.c \
			fdf_hooks.c \
			fdf_menu.c \
			fdf_minmax.c \
			fdf_parse.c \
			fdf_rotate.c \
			fdf_utils.c \
			fdf_color.c
			
SRCS	:= $(addprefix $(SRC_DIR)/, $(SRC))
OBJ_DIR	:= obj
OBJ		:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
NAME	:= fdf

all: $(NAME)

$(MLX): $(MLX_DIR)
	cmake $(MLX_DIR) -B $(MLX_DIR)/build;
	make -C$(MLX_DIR)/build -j4;

$(LIBFT): $(LIBFT_DIR)
	make -C$(LIBFT_DIR);

$(MLX_DIR):
	git clone https://github.com/codam-coding-college/MLX42.git $@;

$(OBJ_DIR):
	mkdir obj

$(NAME): $(MLX) $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) $(OBJ) $(LIBS) $(HEADERS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c inc/fdf.h
	$(CC) -c $(CFLAGS) $< -o $@ $(HEADERS)

clean:
	rm -rf $(OBJ)
	make clean -C$(LIBFT_DIR)

fclean: clean
	rm $(NAME)
	rmdir $(OBJ_DIR)
	rm -rf $(MLX_DIR)

re: fclean all

.PHONY: all, clean, fclean, re




/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:42:47 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/07/23 09:57:31 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			sign;
	long long	n;
	long long	long_max;

	long_max = ((unsigned long long)(-1)) / 2;
	sign = 1;
	n = 0;
	while ((8 < *str && *str < 14) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while ('0' <= *str && *str <= '9')
	{
		if (n > long_max / 10)
			return ((sign > 0) * (-1));
		n = n * 10;
		if (n > long_max - (*str - '0'))
			return ((sign > 0) * (-1));
		n = n + ((*str++) - '0');
	}
	return ((int)(sign * n));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:21:58 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/06/11 18:50:22 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_input_gnl(int fd, char *buf)
{
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		buf[0] = '\0';
		return (0);
	}
	return (1);
}

static char	*ft_abort_gnl(char *line)
{
	if (line && *line)
		return (line);
	if (line)
		free(line);
	return (NULL);
}

static char	*ft_genandallf_gnl(char *buf, size_t len, char *str)
{
	char	*new_str;
	int		i;

	new_str = malloc((len + ft_strlen_gnl(str) + 1));
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	while (*buf && len--)
	{
		new_str[i] = *buf;
		i++;
		buf++;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

static char	*new_str_gnl(char *line, char *buf, char *next_line)
{
	int	bytes;

	bytes = 0;
	if (!*next_line)
	{
		line = ft_genandallf_gnl(buf, next_line - buf, line);
		buf[0] = '\0';
	}
	else
	{
		line = ft_genandallf_gnl(buf, next_line - buf + 1, line);
		bytes = ft_strlen_gnl(next_line + 1) + 1;
	}
	ft_memmove_gnl(buf, next_line + 1, bytes);
	if (!line)
		return (ft_abort_gnl(line));
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*next_line;
	ssize_t		bytes;

	line = NULL;
	if (!check_input_gnl(fd, buffer))
		return (NULL);
	while (1)
	{
		if (buffer[0] == '\0')
		{
			bytes = read(fd, buffer, BUFFER_SIZE);
			if (bytes <= 0)
				return (ft_abort_gnl(line));
			buffer[bytes] = '\0';
		}
		next_line = ft_strchr_gnl(buffer, '\n');
		if (next_line)
			return (new_str_gnl(line, buffer, next_line));
		line = new_str_gnl(line, buffer, ft_strchr_gnl(buffer, '\0'));
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:08:30 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/05/23 13:16:37 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char const *s)
{
	int	size;

	if (!s)
		return (0);
	size = 0;
	while (s[size] != '\0')
		size++;
	return (size);
}

char	*ft_strchr_gnl(char const *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	else
		return (NULL);
}

void	*ft_memmove_gnl(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dst && !src)
		return (dst);
	d = dst;
	s = src;
	if (d > s)
	{
		while (len--)
			d[len] = s[len];
	}
	else
	{
		while (len--)
			*d++ = *s++;
	}
	return (dst);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:11:50 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/05/03 00:29:48 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:05:23 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/05/03 00:13:59 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:27:14 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/05/03 00:34:01 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:56:11 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/05/03 02:44:18 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isin_set(char c, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i1;
	size_t	i2;
	char	*pnt;

	if (!s1 || !set)
		return (NULL);
	i1 = 0;
	len = ft_strlen(s1);
	i2 = len - 1;
	while (s1[i1] && isin_set(s1[i1], set))
		i1++;
	if (i1 == len)
		return (ft_strdup(""));
	while (i2 && isin_set(s1[i2], set))
		i2--;
	pnt = ft_substr(s1, (unsigned int)i1, (size_t)(i2 - i1 + 1));
	return (pnt);
}

static int	isin_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:34:38 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/07/29 11:37:52 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (*(s + i))
	{
		if (*(s + i) != c)
		{
			count++;
			while (*(s + i) && *(s + i) != c)
				i++;
		}
		else if (*(s + i) == c)
			i++;
	}
	return (count);
}

static size_t	word_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*(s + i) && *(s + i) != c)
		i++;
	return (i);
}

static void	free_array(size_t i, char **array)
{
	while (i > 0)
	{
		i--;
		free(*(array + i));
	}
	free(array);
}

static char	**split(char const *s, char c, char **array, size_t words_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < words_count)
	{
		while (*(s + j) && *(s + j) == c)
			j++;
		*(array + i) = ft_substr(s, j, word_len(&*(s + j), c));
		if (!*(array + i))
		{
			free_array(i, array);
			return (NULL);
		}
		while (*(s + j) && *(s + j) != c)
			j++;
		i++;
	}
	*(array + i) = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	array = split(s, c, array, words);
	return (array);
}
