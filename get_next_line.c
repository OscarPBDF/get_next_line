/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez-d <operez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:52:43 by operez-d          #+#    #+#             */
/*   Updated: 2022/10/24 11:54:00 by operez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_line(char *buffer, char *line)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = 0;
	return (line);
}

static char	*next_buffer(char *buffer)
{
	char	*aux;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	aux = ft_calloc(i + 1, sizeof(char));
	if (buffer[i] == '\n')
		i++;
	if (buffer[i] == '\0')
		return (NULL);
	j = 0;
	while (buffer[i] != '\0')
	{
		aux[j] = buffer[i];
		j++;
		i++;
	}
	return (aux);
}

char	*ft_read(int fd, char *buffer)
{
	char	*aux;
	size_t	bytes;

	aux = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!aux)
		return (NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, aux, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(aux);
			return (NULL);
		}
		aux[bytes] = 0;
		buffer = ft_strjoin(buffer, aux);
	}
	free(aux);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!buffer)
		buffer = ft_calloc(1, 1);
	buffer = ft_read(fd, buffer);
	line = fill_line(buffer, line);
	buffer = next_buffer(buffer);
	return (line);
}

#include <stdio.h>
int	main()
{
	int	fd;

	fd = open("./mifichero.txt", O_RDONLY);
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	close(fd);
}