/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 12:52:54 by jguyet            #+#    #+#             */
/*   Updated: 2016/05/22 12:52:56 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define PRINTF_PROG

#include "printf.h"

void		add_string(t_string *string, char *s, int del)
{
	int		i;
	int		o;
	char	*tmp;

	i = 0;
	if (string->res != 0 && !(string->res % BUFFER))
	{
		tmp = ft_strnew(string->res + BUFFER);
		ft_memcpy(tmp, string->new, string->res);
		ft_strdel(&string->new);
		string->new = tmp;
	}
	o = ft_strlen(s);
	while (i < o)
		string->new[string->res++] = s[i++];
	if (del == 2 || del == 3)
		ft_strdel(&s);
}
