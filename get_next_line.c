/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez-d <operez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:52:43 by operez-d          #+#    #+#             */
/*   Updated: 2022/10/27 18:01:26 by operez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*append_line(char *buffer, char *line)
{
	int		i;
	int		pre_len;
	char	*aux;
	
	i = 0;
	pre_len = 0;
	aux = NULL;
	while ((buffer[i] != '\0' && buffer[i] != '\n'))//
		i++;
	if(line)
	{
		pre_len = ft_strlen(line);
		aux = line;
	}
	//printf("############%s\n",line);
	line = ft_strjoin(line, buffer);
	//printf("############%s\n",line);
	if (!line)
	{
		if(aux)
			free(aux);
		return (NULL);
	}
	i = 0;
	while ((buffer[i] != '\0' && buffer[i] != '\n'))
	{
		line[pre_len] = buffer[i];
		i++;
		pre_len++;
	}
	if (buffer[i] == '\n')
		line[pre_len++] = '\n';
	line[pre_len] = 0;
	if(aux)
		free(aux);
	printf("---%s\n",line);
	return (line);
}
/*
static char	*next_buffer(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	while ((buffer[i] != '\0' && buffer[i] != '\n') || j <= BUFFER_SIZE)
		i++;
	new_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!new_buffer)
		return (NULL);
	if (buffer[i] == '\n')
		i++;
	if (buffer[i] == '\0')
		return (NULL);
	j = 0;
	while (buffer[i] != '\0' || j <= BUFFER_SIZE)
	{
		new_buffer[j] = buffer[i];
		j++;
		i++;
	}
	free(buffer);
	return (new_buffer);
}
*/
static char	*ft_read(int fd, char *buffer)
{
	int	bytes;
	
	if(!buffer)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buffer)
			return (NULL);
	}
	bytes = read(fd, buffer, BUFFER_SIZE);
	if(bytes < 1)
	{
		free(buffer);
		return (NULL);
	}
	if(bytes < BUFFER_SIZE)
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
		//Error al no encontrar end file
	while (!line || !(ft_strchr(line, '\n')))
	{
		if(buffer)//##################
			if(ft_strchr(buffer, '\n'))
				buffer = ft_strchr(buffer, '\n') + 1;
		if (!buffer || !*buffer || ft_strlen(buffer) == BUFFER_SIZE)
		{
			buffer = ft_read(fd, buffer);
			if (!buffer)
				return (NULL);
		}
		line = append_line(buffer, line);
	}
	//buffer = next_buffer(buffer);
	return (line);
}


int	main()
{
	int		fd;
	char	*line;

	fd = open("./pruebas.txt", O_RDONLY);
	//fd = open("./mifichero.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s",line);
	free(line);
	
	/*line = get_next_line(fd);
	printf("%s",line);
	free(line);
	close(fd);*/
	//system("leaks -q a.out");
}