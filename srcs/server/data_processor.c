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
			client->send(client, ft_dstrjoin("NL", nick, 2));
		else
			client->send(client, ft_dstrjoin("NC", nick, 2));
	}
	return (0);
}

int			channel_join(t_socket_server *server, t_client *client,\
	char *channel_name)
{
	t_channel	*channel;
	int			exists;

	exists = 0;
	channel = server->channels;
	while (channel)
	{
		if (ft_strcmp(channel->name, channel_name) == 0)
		{
			exists = 1;
			break ;
		}
		channel = channel->next(channel);
	}
	if (exists == 0)
	{
		client->send(client, client->serialize("CE%s", channel_name));
		return (1);
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
	//printf("Reveived Message :%s\n", message);
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
