/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:58:05 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/22 20:58:07 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	check_input_gnl(int fd, char *buf)
{
	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (fd >= 0)
			buf[0] = '\0';
		return (0);
	}
	return (1);
}

static char	*ft_abort_gnl(char *line, char *buffer, int err)
{
	if (err)
	{
		buffer[0] = '\0';
		if (line && *line)
			return (line);
	}
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
		return (ft_abort_gnl(line, buf, 0));
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[MAX_FD][BUFFER_SIZE + 1];
	char		*line;
	char		*next_line;
	ssize_t		bytes;

	line = NULL;
	if (!check_input_gnl(fd, buffer[fd]))
		return (NULL);
	while (1)
	{
		if (buffer[fd][0] == '\0')
		{
			bytes = read(fd, buffer[fd], BUFFER_SIZE);
			if (bytes <= 0)
				return (ft_abort_gnl(line, buffer[fd], 1));
			buffer[fd][bytes] = '\0';
		}
		next_line = ft_strchr_gnl(buffer[fd], '\n');
		if (next_line)
			return (new_str_gnl(line, buffer[fd], next_line));
		line = new_str_gnl(line, buffer[fd], ft_strchr_gnl(buffer[fd], '\0'));
	}
}
