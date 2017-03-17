/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_caps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 08:15:02 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 08:15:04 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

int		load_console(void)
{
	struct termios	*term;

	term = (struct termios *)malloc(sizeof(struct termios));
	if (tcgetattr(0, term) == -1)
	{
		ft_printf("[modif_term] Failed request tcgetattr!\n");
		return (0);
	}
	term->c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(0, TCSADRAIN, term) == -1)
		return (0);
	return (1);
}
