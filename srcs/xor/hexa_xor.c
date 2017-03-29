/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_xor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 06:41:42 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 06:41:43 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define XOR_PROG

#include "xor.h"

char	*int_to_hexastring(char c)
{
	char	*hex;

	ft_asprintf(&hex, "%02x", c);
	return (hex);
}

char	hexastring_to_int(char *s)
{
	char	xor;

	xor = ft_atoi_base(s, 16);
	ft_strdel(&s);
	return (xor);
}
