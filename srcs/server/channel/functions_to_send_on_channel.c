/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_to_send_on_channel.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:57:04 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 05:57:06 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

void		send_to_channel_users(t_socket_server *server,\
	t_channel *channel, char *data)
{
	t_client	*c;

	c = server->clients;
	while (c)
	{
		if (c->channel != NULL && c->channel->id == channel->id)
			c->send(c, ft_strdup(data));
		c = c->next(c);
	}
	ft_strdel(&data);
}

void		left_channel(t_socket_server *server,\
	t_channel *channel, t_client *client)
{
	channel->send(server, channel, client->serialize("CL%s", client->nickname));
}

void		join_channel(t_socket_server *server,\
	t_channel *channel, t_client *client)
{
	if (client->channel != NULL)
		left_channel(server, client->channel, client);
	client->channel = channel;
	channel->send(server, channel, client->serialize("CJ%s", client->nickname));
	client->send(client,\
		client->serialize("CO%d|%s", channel->id, channel->name));
}

void		add_message(t_socket_server *server,\
	t_channel *channel, t_client *client, char *message)
{
	channel->send(server, channel,\
		client->serialize("CM%s|%s", client->nickname, message));
}
