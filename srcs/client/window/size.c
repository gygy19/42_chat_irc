/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 03:15:41 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/24 03:15:44 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>

size_t			get_size_x(void)
{
	size_t			size;
	struct winsize	*w;

	if (!(w = malloc(sizeof(struct winsize))))
		return (0);
	ioctl(0, TIOCGWINSZ, w);
	size = (size_t)w->ws_col;
	free(w);
	return (size);
}

size_t			get_size_y(void)
{
	size_t			size;
	struct winsize	*w;

	if (!(w = malloc(sizeof(struct winsize))))
		return (0);
	ioctl(0, TIOCGWINSZ, w);
	size = (size_t)w->ws_row;
	free(w);
	return (size);
}
