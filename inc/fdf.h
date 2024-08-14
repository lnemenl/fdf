/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:37:44 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/14 13:58:04 by rkhakimu         ###   ########.fr       */
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
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/Libft/libft.h"

# define WIDTH              1920
# define HEIGHT             1080
# define TEXT_CLR         0xEAEAEAFF //TEXT_COLOR
# define BG_CLR         0x22222200 //BACKGROUND
# define MENU_BG_CLR    0x1E1E1EFF //MENU_BACKGROUND
# define CLR_LV_10          0x9e0142ff //COLOR_TEN
# define CLR_LV_9        0xd53e4fff // COLOR_NINE
# define CLR_LV_8        0xf46d43ff //COLOR_EIGHT
# define CLR_LV_7        0xfdae61ff //COLOR_SEVEN
# define CLR_LV_6          0xfee08bff //COLOR_SIX
# define CLR_LV_5         0xe6f598ff //COLOR_FIVE
# define CLR_LV_4         0xabdda4ff //COLOR_FOUR
# define CLR_LV_3        0x66c2a5ff //COLOR_THREE
# define CLR_LV_2          0x3288bdff //COLOR_TWO
# define CLR_LV_1          0x5e4fa2ff //COLOR_ONE
# define USAGE_FORMAT             "Format:\n\t./fdf maps/filename.fdf"//FORMAT
# define MALLOC_ERR             "Malloc failed"//MALLOC
# define MAP_ERR        "Map is invalid"//INVALID_MAP
# define FILE_OPEN_ERR         "Unable to open file"//FILE_ERROR

typedef struct s_vertex // Old: s_point3d
{
    double  x;
    double  y;
    double  z;
    int     mapcolor;
    int     zcolor;
}               t_vertex; // Old: t_point3d

typedef struct s_pixel // Old: s_point2d
{
    int     x;
    int     y;
    int     z;
    int     rgba;
}           t_pixel; // Old: t_point2d

typedef struct s_map
{
    int             rows;
    int             cols;
    int             max_height;      // Old: high
    int             min_height;      // Old: low
    bool            use_height_color; // Old: use_zcolor
    double          center_x;        // Old: x_offset
    double          center_y;        // Old: y_offset
    double          interval;
    double          iso_angle_x;     // Old: alpha
    double          iso_angle_y;     // Old: beta
    double          rotation_x;      // Old: xrotate
    double          rotation_y;      // Old: yrotate
    double          rotation_z;      // Old: zrotate
    double          zoom;
    double          height_scale;    // Old: zscale
    t_vertex        **original_points; // Old: grid3d
    t_pixel         **projected_points; // Old: grid2d
}                   t_map;

typedef struct s_fdf
{
    mlx_t       *mlx;
    t_map       *map;
    mlx_image_t *image;
}               t_fdf;

/* fdf_main.c */
void        map_init(t_map *map);//init_map

/* fdf_parse.c */
void        map_parse(int fd, t_map *map);//parse_map
void        map_size(int fd, t_map *map); //get_dimensions

/* fdf_error.c */
void        arr_free(void **ptr, size_t len);//ft_free_tab
void        map_free(t_map *map);//free_map
void        failSafe(const char *message);//prev. handle error
void        map_error(int fd, t_map *map, char *message);//error_map

/* fdf_draw.c */
void        map_project(t_map *map, int i, int j);//project
void        draw_image(void *param);//draw_image
void        menu(mlx_t *mlx);//display_menu

/* fdf_rotate.c */
void        rot_x_axis(double *y, double *z, double alpha);//rotate_x
void        rot_y_axis(double *x, double *z, double beta);//rotate_y
void        rot_z_axis(double *x, double *y, double gamma);//rotate_z

/* fdf_hooks.c */
void        hook_events(void *param);//ft_hook
void        hook_scroll(double xdelta, double ydelta, void *param);//fdf_scrollhook
void        hook_rotate(void *param);//ft_hook_rotate
void        hook_project(void *param);//ft_hook_project

/* fdf_utils.c*/
void        ft_upper(unsigned int i, char *c);//make_upper
void        image_reset(mlx_image_t *image);//draw_reset
int         fname_valid(const char *filename);//valid_filename

/* fdf_color.c */
int         get_clr(t_pixel current, t_pixel a, t_pixel b);//get_color
void        apply_zclr(t_map *map);//set_zcolor

#endif