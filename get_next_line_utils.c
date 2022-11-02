/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez-d <operez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:14:18 by operez-d          #+#    #+#             */
/*   Updated: 2022/11/02 11:48:23 by operez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	int		n;
	int		i;

	n = count * size;
	if (n == 1 && count != 1)
		return (NULL);
	str = malloc(n);
	if (!(str))
		return (0);
	i = 0;
	while (n > 0)
	{
		str[i] = 0;
		i++;
		n--;
	}
	return ((void *)str);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char			*str;
	unsigned int	i;

	i = 0;
	str = (char *)s;
	while (str[i] != (unsigned char)c)
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (&str[i]);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*str;
	size_t	i;

	lens1 = 0;
	lens2 = 0;
	if (s1)
		lens1 = ft_strlen(s1);
	if (s2)
		lens2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (lens1 + lens2 + 1)); //#########
	if (!str)
		return (0);
	i = -1;
	while (++i < lens1)
		str[i] = s1[i];
	i = -1;
	while (++i < lens2)
		str[lens1++] = s2[i];
	return (str);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (!src && !dest)
		return (0);
	d = dest;
	s = (unsigned char *)src;
	i = 0;
	while (n > 0)
	{
		d[i] = s[i];
		i++;
		n--;
	}
	return (dest);
}
