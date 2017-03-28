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

void			print_channels(t_socket_client *client)
{
	t_channel	*channel;

	ft_printf("{color189}<Channels_list{reset}");
	channel = client->channels;
	if (channel != NULL)
		ft_printf("{color189}:    {reset}");
	while (channel)
	{
		if (client->channel == channel)
			ft_putstr("\033[47;30;4m");
		ft_printf("%.8s", channel->name);
		if (client->channel == channel)
			ft_putstr("\033[00m");
		if (channel->right != NULL)
			ft_printf("    ");
		channel = channel->next(channel);
	}
	ft_printf("{color189}>{reset}\n");
}

void			print_prompt(t_socket_client *client)
{
	ft_putstr("\n");
	ft_putstr("\033[s\033[1A");
	print_channels(client);
	if (client->host != NULL && client->pseudo != NULL)
	{
		ft_printf("{color32}<\u2170r\u217D %s:%d>{reset} {color34}",\
			client->host, client->port);
		ft_printf("<nickname:%s{color166}*{color34}>{reset} ",\
			client->pseudo);
		ft_printf("{color228}\u2A20{reset}  ");
	}
	else if (client->host == NULL || client->pseudo == NULL)
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
	if (client->host != NULL && client->pseudo != NULL)
	{
		ft_printf("{color32}<\u2170r\u217D %s:%d>{reset} {color34}",\
			client->host, client->port);
		ft_printf("<nickname:%s{color166}*{color34}>{reset} ",\
			client->pseudo);
		ft_printf("{color228}\u2A20{reset}  ");
	}
	else if (client->host == NULL || client->pseudo == NULL)
		ft_printf("{color32}<\u2170r\u217D>{reset} {color228}\u2A20{reset} ");
	if (client->current_cmd->cmd != NULL)
		ft_putstr(client->current_cmd->cmd);
}
