/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez-d <operez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:52:43 by operez-d          #+#    #+#             */
/*   Updated: 2022/11/08 10:24:58 by operez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_mem_line(char *buffer, char *line, int pre_len)
{
	int	i;

	i = 0;
	while ((buffer[i] != '\0' && buffer[i] != '\n'))
	{
		line[pre_len] = buffer[i];
		i++;
		pre_len++;
	}
	if (buffer[i] == '\n')
	{
		line[pre_len++] = '\n';
		buffer = (char *)ft_memcpy(buffer, &buffer[i + 1], BUFFER_SIZE - i);
	}
	else
		buffer[0] = 0;
	line[pre_len] = 0;
	return (line);
}

static char	*ft_join_line(char *buffer, char *line)
{
	int		i;
	int		pre_len;
	char	*aux;

	i = 0;
	pre_len = 0;
	aux = NULL;
	while ((buffer[i] != '\0' && buffer[i] != '\n'))
		i++;
	if (line)
	{
		pre_len = ft_strlen(line);
		aux = line;
	}
	line = ft_strjoin(line, buffer);
	if (!line)
	{
		if (aux)
			free(aux);
		return (NULL);
	}
	line = ft_mem_line(buffer, line, pre_len);
	if (aux)
		free(aux);
	return (line);
}

static char	*ft_read(int fd, char *buffer)
{
	int	bytes;

	if (!buffer)
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (NULL);
	}
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes < 1)
	{
		if (buffer)
			free(buffer);
		return (NULL);
	}
	if (bytes < BUFFER_SIZE)
		buffer[bytes] = 0;
	else
		buffer[BUFFER_SIZE] = 0;
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char		*buffer[OPEN_MAX];
	char			*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1 || fd > OPEN_MAX)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		if (!buffer[fd])
			return (line);
	}
	while (!line || !(ft_strchr(line, '\n')))
	{
		if (!*buffer[fd])
		{
			buffer[fd] = ft_read(fd, buffer[fd]);
			if (!buffer[fd])
				return (line);
		}
		line = ft_join_line(buffer[fd], line);
	}
	return (line);
}
