/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_putting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:15:02 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 05:15:03 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

void			print_current_command(t_socket_client *client, int start)
{
	int end_line;

	end_line = ft_strlen(client->current_cmd->cmd +\
		client->current_cmd->cursor_pos);
	if (start && ft_strlen(client->current_cmd->cmd) > 0)
	{
		ft_putstr("\033[K");
		ft_putstr(client->current_cmd->cmd);
		ft_printf("\033[%dD", end_line - 1);
	}
	else if (!start && client->current_cmd->cursor_pos <\
		ft_strlen(client->current_cmd->cmd))
	{
		ft_putstr("\033[K");
		ft_putstr(client->current_cmd->cmd +\
			client->current_cmd->cursor_pos);
		ft_printf("\033[%dD", end_line);
	}
}

void			print_prompt(t_socket_client *client)
{
	ft_putstr("\n");
	ft_putstr("\033[s\033[1A");
	print_channels(client);
	if (client->host != NULL && client->nickname != NULL)
	{
		ft_printf("{color32}<\u2170r\u217D %s:%d>{reset} ",\
			client->host, client->port);
		ft_printf("{color34}<{reset}nickname:%s{color166}*{color34}>{reset} ",\
			client->nickname);
		ft_printf("{color228}\u2A20{reset}  ");
	}
	else if (client->host == NULL || client->nickname == NULL)
		ft_printf("{color32}<\u2170r\u217D>{reset} {color228}\u2A20{reset} ");
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
	if (client->host != NULL && client->nickname != NULL)
	{
		ft_printf("{color32}<\u2170r\u217D %s:%d>{reset} {color34}",\
			client->host, client->port);
		ft_printf("{color34}<{reset}nickname:%s{color166}*{color34}>{reset} ",\
			client->nickname);
		ft_printf("{color228}\u2A20{reset}  ");
	}
	else if (client->host == NULL || client->nickname == NULL)
		ft_printf("{color32}<\u2170r\u217D>{reset} {color228}\u2A20{reset} ");
	if (client->current_cmd->cmd != NULL)
		print_current_command(client, 1);
}
