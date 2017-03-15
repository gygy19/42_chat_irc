/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 04:47:19 by jguyet            #+#    #+#             */
/*   Updated: 2015/12/13 23:33:59 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*delim(char *s, char c)
{
	if (s)
	{
		if (*s == c)
		{
			s++;
		}
		return (s);
	}
	return (NULL);
}

static int	size_occus(char *s, char c)
{
	int size;

	size = 0;
	if (s)
	{
		while (*s)
		{
			if (*s != c)
				size++;
			s++;
		}
	}
	return (size);
}

static char	**split(char **result, char *s, char c)
{
	int		x;
	int		y;
	char	*tmp;

	x = 0;
	y = 0;
	while (s && c && *s)
	{
		if (*s == c)
		{
			if ((s = delim((char*)s, c)) && !*s)
				break ;
			result[y][x] = '\0';
			y++;
			tmp = ft_memalloc(size_occus((char*)s, c) + 1);
			result[y] = tmp;
			x = 0;
		}
		if (*s != c)
			result[y][x] = *s;
		s++;
		x++;
	}
	return (result);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**result;
	char	*tmp;

	if (!s)
		return (NULL);
	result = NULL;
	if (!(result = malloc(sizeof(char*) *
		(ft_lenbychar((char*)s, c)) + 1)))
		return (NULL);
	s = delim((char*)s, c);
	if (!*s)
		return (result);
	tmp = ft_memalloc(size_occus((char*)s, c) + 1);
	result[0] = tmp;
	result = split(result, (char*)s, c);
	return (result);
}
