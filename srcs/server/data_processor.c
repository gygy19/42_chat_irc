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
	char		*message;

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
		client->send(client, ft_dstrjoin("CE", channel_name, 2));
		return (1);
	}
	if (!add_client_to_channel(channel, client))
	{
		ft_asprintf(&message, "CC%d|%s", channel->id, channel->name);
		client->send(client, message);
		return (1);
	}
	ft_asprintf(&message, "CJ%d|%s", channel->id, channel->name);
	client->send(client, message);
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
	{
		return (channel_join(server, client, message));
	}
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
	printf("Reveived Message :%s\n", message);
	if (ft_strlen(message) > 0)
		action = message[0];
	if (ft_strlen(message) > 1)
		type = message[1];
	finalmessage = ft_strsub(message, 2, ft_strlen(message));
	if (action == 'C')
		return (channel_action(server, client, type, finalmessage));
	if (action == 'N')
		return (nickname_action(server, client, type, finalmessage));
	return (0);
}
