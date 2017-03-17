/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 08:17:04 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 08:17:06 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

void			print_prompt(int start, t_socket_client *client)
{
	if (start == 0)
		ft_putstr("\033[u\033[K");
	ft_putstr("\033[s");
	if (client->host != NULL)
		ft_printf("[SRV IRC %s:%d] ", client->host, client->port);
	if (client->pseudo != NULL)
		ft_printf("[%s] ", client->pseudo);
	else if (client->host == NULL)
		ft_printf("[IRC] ");
	ft_printf("» ");
}

void			reprint_line(t_socket_client *client)
{
	ft_putstr("\033[u\033[K");
	ft_putstr("\033[s");
	if (client->host != NULL)
		ft_printf("[SRV IRC %s:%d] ", client->host, client->port);
	if (client->pseudo != NULL)
		ft_printf("[%s] ", client->pseudo);
	else if (client->host == NULL)
		ft_printf("[IRC] ");
	ft_printf("» ");
	if (client->cmds[0].cmd != NULL)
		ft_putstr(client->cmds[0].cmd);
}
