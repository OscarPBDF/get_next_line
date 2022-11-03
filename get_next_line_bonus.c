/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez-d <operez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:52:43 by operez-d          #+#    #+#             */
/*   Updated: 2022/11/03 16:36:57 by operez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char *append_line(char *buffer, char *line, int pre_len)
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

static char	*join_line(char *buffer, char *line)
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
	line = append_line(buffer, line, pre_len);
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
	if (fd < 0 || BUFFER_SIZE < 1)
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
		line = join_line(buffer[fd], line);
	}
	return (line);
}

#include <stdio.h>
int	main()
{
	char	*temp;
	int	fd1, fd2, fd3;
	int i;

	fd1 = open("./mobyDick.txt", O_RDONLY);
	fd2 = open("./numeros.txt", O_RDONLY);
	fd3 = open("./null.txt", O_RDONLY);
	i = 0;
	while(i < 5)
	{
		i++;
		printf("%d\n",i);
		temp = get_next_line(fd1);
		if (!temp)
		break ;
		printf("%s", temp);
		free(temp);
		
		temp = get_next_line(fd2);
		if (!temp)
		break ;
		printf("%s", temp);
		free(temp);
		
		temp = get_next_line(fd3);
		printf("%s\n", temp);
		free(temp);
	}
	return (0);
}