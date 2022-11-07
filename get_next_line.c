/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez-d <operez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:52:43 by operez-d          #+#    #+#             */
/*   Updated: 2022/11/07 16:20:32 by operez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*mem_line(char *buffer, char *line, int pre_len)
{
	int	i;

	i = 0;
	while ((buffer[i] != '\0' && buffer[i] != '\n'))
	{
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

static char	*join_line(char *buffer, char *line)
{
	int		pre_len;
	char	*aux;

	pre_len = 0;
	aux = NULL;
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
	line = mem_line(buffer, line, pre_len);
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
	static char		*buffer = NULL;
	char			*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!buffer)
	{
		buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		if (!buffer)
			return (line);
	}
	while (!line || !(ft_strchr(line, '\n')))
	{
		if (!*buffer)
		{
			buffer = ft_read(fd, buffer);
			if (!buffer)
				return (line);
		}
		line = join_line(buffer, line);
	}
	return (line);
}
/*
#include <stdio.h>
int	main()
{
	int		fd;
	char	*line;
	
	//fd = open("./null.txt", O_RDONLY);
	//fd = open("./mobyDick.txt", O_RDONLY);
	fd = open("./numeros.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("====%s",line);
	free(line);
	
	line = get_next_line(fd);
	printf("====%s",line);
	free(line);
	close(fd);
	//system("leaks -q a.out");
}*/