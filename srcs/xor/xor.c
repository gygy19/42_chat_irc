/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 19:56:58 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/22 19:56:59 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define XOR_PROG

#include "xor.h"

static char	*xor_char(int i, char c)
{
	char	*ret;

	ret = int_to_hexastring(c ^ XOR_KEY[i % ft_strlen(XOR_KEY)]);
	return (ret);
}

static char	*unxor_char(int i, char c)
{
	char	*ret;

	ret = ft_strnew(1);
	ret[0] = c ^ XOR_KEY[i % ft_strlen(XOR_KEY)];
	return (ret);
}

char		*crypt_string_to_xor(char *msg)
{
	int		i;
	char	*crypted;

	i = 0;
	crypted = ft_strnew(0);
	while (msg[i])
	{
		crypted = ft_dstrjoin(crypted, xor_char(i, msg[i]), 3);
		i++;
	}
	return (crypted);
}

char		*uncrypt_xor_to_string(char *crypted)
{
	int		i;
	int		n;
	char	*msg;

	i = 0;
	n = 0;
	msg = ft_strnew(0);
	while (crypted[n + 1])
	{
		msg = ft_dstrjoin(msg, unxor_char(i,\
			hexastring_to_int(ft_strsub(crypted, n, 2))), 3);
		i++;
		n += 2;
	}
	return (msg);
}

char		*print_crypted(char *crypted)
{
	int		n;
	char	*print;
	char	*res;

	n = 0;
	res = ft_strnew(0);
	while (crypted[n] && crypted[n + 1])
	{
		if (!crypted[n + 2] || !crypted[n + 3])
			ft_asprintf(&print, "[%c%c]", crypted[n], crypted[n + 1]);
		else
			ft_asprintf(&print, "[%c%c] ", crypted[n], crypted[n + 1]);
		res = ft_dstrjoin(res, print, 3);
		n += 2;
	}
	return (res);
}
