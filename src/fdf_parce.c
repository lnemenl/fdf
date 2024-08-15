/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:38:16 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/15 09:19:17 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	clr_parse(int fd, t_map *map, char *arr2)
{
	while (*arr2 == '-')
		arr2++;
	while (ft_isdigit(*arr))
		arr2++;
	if (*arr2 == ',')
		arr2++;
	else
		return (0xFFFFFFFF);
	if ((ft_strncmp(arr2, "0X", 2) && ft_strncmp(arr2, "0x", 2)))
		map_error(fd, map, MAP_ERR);
	arr += 2;
	ft_striteri(arr, &to_upper);
	return ((ft_atoi_base(arr, "0123456789ABCDEF") << 8) | 0xFF);		
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
		if(!fd_isdigit(*arr[j]) && *arr[j] != '-')
			map_error(fd, map, MAP_ERR);
		point = &(map->original_points[i][j]);
		center_x = (map->cols - 1) * map->interval / 2;
		center_y = (map->rows - 1) * map->interval / 2;
		point->x = (double)j * (map->interval) - center_x;
		point->y = (double)i * (map->interval) - center_y;
		point->z = (double)ft_atoi(arr[i]) * (map->interval);
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
		map_error(fd, map, MALLOC_ERR)
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
