/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 00:37:32 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 00:37:33 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

static int	channel_join(t_socket_server *server, t_client *client,\
	char *channel_name)
{
	t_channel	*channel;

	channel = get_channel(server, channel_name);
	if (channel == NULL)
	{
		channel = add_channel(server, (int)channel_name, channel_name);
		server->send_message_to_all(server,\
			client->serialize("CA%d|%s", channel->id, channel->name));
	}
	if (client->channel != NULL && client->channel->id == channel->id)
		return (1);
	channel->join(server, channel, client);
	return (0);
}

static int	channel_message(t_socket_server *server, t_client *client,\
	char *message)
{
	if (message == NULL || ft_strlen(message) == 0)
		return (1);
	if (client->nickname == NULL || client->channel == NULL)
		return (1);
	client->channel->add_message(server, client->channel, client, message);
	return (0);
}

static int	channel_leave(t_socket_server *server, t_client *client)
{
	char	*message;

	if (client->nickname == NULL || client->channel == NULL)
		return (1);
	if (!(message = ft_sprintf("CL%s", client->nickname)))
		return (0);
	client->channel->send(server, client->channel, client->serialize(message));
	client->channel = NULL;
	ft_strdel(&message);
	return (0);
}

int			channel_action(t_socket_server *server, t_client *client,\
	char type, char *message)
{
	(void)server;
	(void)client;
	if (message == NULL)
		return (1);
	if (type == 'L')
		return (channel_leave(server, client));
	if (type == 'J')
		return (channel_join(server, client, message));
	if (type == 'M')
		return (channel_message(server, client, message));
	if (type == 'W')
		return (who_action(server, client));
	return (0);
}
