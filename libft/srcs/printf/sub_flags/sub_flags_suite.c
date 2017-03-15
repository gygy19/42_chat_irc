/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_flags_suite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:57:37 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/27 16:57:40 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define PRINTF_PROG

#include "printf.h"

int				add_wildcard(char **n, int i, t_string *t, short point)
{
	int nbr;

	nbr = get_int(t);
	if (nbr < 0)
	{
		nbr = -nbr;
		if (point == 0 && !(t->sub_flags & SUB_INF))
			t->sub_flags += SUB_INF;
		else
			nbr = -nbr;
	}
	if (point == 0 && *n[0] != '\0')
		*n = ft_strdelandnew(n, 0);
	if (point > 0 || sub(t, -1, *n, 1) == -1)
		*n = ft_dstrjoin(*n, ft_litoa(nbr), 3);
	else
		*n = ft_dstrjoin(*n, ft_litoa(nbr), 3);
	return (i);
}
