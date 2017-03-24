/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_processor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 07:58:22 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 07:58:24 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

int			autentificate_client(t_socket_server *server, t_client *client)
{
	t_channel *channel;

	channel = server->channels;
	while (channel != NULL)
	{
		client->send(client, client->serialize("CA%d|%s", channel->id, channel->name));
		channel = channel->next(channel);
	}
	client->send(client, client->serialize("NC%s", client->nickname));
	return (0);
}

int			nickname_action(t_socket_server *server, t_client *client,\
	char type, char *nick)
{
	(void)server;
	if (nick == NULL)
		return (1);
	if (type == 'C')
	{
		if (ft_strlen(nick) > 9 || ft_strlen(nick) < 2)
		{
			client->send(client, client->serialize("NL%s", nick));
			return (1);
		}
		client->send(client, client->serialize("NC%s", nick));
		if (client->channel != NULL)
			client->channel->send(server, client->channel, client->serialize("CN%s|%s", client->nickname, nick));
		if (client->nickname != NULL)
			ft_strdel(&client->nickname);
		client->nickname = ft_strdup(nick);
	}
	return (0);
}

int			channel_join(t_socket_server *server, t_client *client,\
	char *channel_name)
{
	t_channel	*channel;

	channel = get_channel(server, channel_name);
	
	if (channel == NULL)
	{
		channel = add_channel(server, (int)channel_name, channel_name);
		server->send_message_to_all(server, client->serialize("CA%d|%s", channel->id, channel->name));
	}
	if (client->channel != NULL && client->channel->id == channel->id)
		return (1);
	channel->join(server, channel, client);
	return (0);
}

int			channel_message(t_socket_server *server, t_client *client,\
	char *message)
{
	if (message == NULL || ft_strlen(message) == 0)
		return (1);
	if (client->nickname == NULL || client->channel == NULL)
		return (1);
	client->channel->add_message(server, client->channel, client, message);
	return (0);
}

int			channel_action(t_socket_server *server, t_client *client,\
	char type, char *message)
{
	(void)server;
	(void)client;
	if (message == NULL)
		return (1);
	if (type == 'J')
		return (channel_join(server, client, message));
	if (type == 'M')
		return (channel_message(server, client, message));
	return (0);
}

int			data_processor(t_socket_server *server, t_client *client,\
	char *message)
{
	char	*finalmessage;
	char	action;
	char	type;

	action = '\0';
	type = '\0';
	if (ft_strlen(message) > 0)
		action = message[0];
	if (ft_strlen(message) > 1)
		type = message[1];
	finalmessage = ft_strsub(message, 2, ft_strlen(message));
	if (action == 'C')
		return (channel_action(server, client, type, finalmessage));
	if (action == 'N')
		return (nickname_action(server, client, type, finalmessage));
	if (action == 'W' && type == 'B')
		return (autentificate_client(server, client));
	return (0);
}
