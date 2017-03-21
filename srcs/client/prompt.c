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

void			put_up(void)
{
	ft_putchar(8);
	ft_putchar(27);
	ft_putchar(1);
	ft_putchar(74);
}

void			print_prompt(t_socket_client *client)
{
	ft_putstr("\n");
	ft_putstr("\033[s\033[1A");
	print_channels(client);
	if (client->host != NULL)
		ft_printf("[SRV IRC %s:%d] ", client->host, client->port);
	if (client->pseudo != NULL)
		ft_printf("[%s] ", client->pseudo);
	else if (client->host == NULL)
		ft_printf("[IRC] ");
	ft_printf("» ");
}

void			restart_line(void)
{
	ft_putstr("\033[u\033[K");
	ft_putstr("\033[s\033[1A");
	ft_putstr("\033[K");
}

void			reprint_line(t_socket_client *client)
{
	restart_line();
	print_channels(client);
	ft_putstr("\033[K");
	if (client->host != NULL)
		ft_printf("[SRV IRC %s:%d] ", client->host, client->port);
	if (client->pseudo != NULL)
		ft_printf("[%s] ", client->pseudo);
	else if (client->host == NULL)
		ft_printf("[IRC] ");
	ft_printf("» ");
	if (client->current_cmd->cmd != NULL)
		ft_putstr(client->current_cmd->cmd);
}
