/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/17 05:18:36 by jguyet            #+#    #+#             */
/*   Updated: 2016/07/17 05:19:38 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define PRINTF_PROG

#include "printf.h"

void		modif_colors(t_string *string)
{
	string->new = ft_replace(string->new, "{red}", RED);
	string->new = ft_replace(string->new, "{reset}", NRM);
	string->new = ft_replace(string->new, "{green}", GRN);
	string->new = ft_replace(string->new, "{yellow}", YEL);
	string->new = ft_replace(string->new, "{blue}", BLU);
	string->new = ft_replace(string->new, "{magenta}", MAG);
	string->new = ft_replace(string->new, "{cyan}", CYN);
	string->new = ft_replace(string->new, "{white}", WHT);
	string->new = ft_replace(string->new, "{bold}", BOL);
}
