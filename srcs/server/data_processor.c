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

static int	autentificate_client(t_socket_server *server, t_client *client)
{
	t_channel *channel;

	channel = server->channels;
	while (channel != NULL)
	{
		client->send(client,\
			client->serialize("CA%d|%s", channel->id, channel->name));
		channel = channel->next(channel);
	}
	client->send(client, client->serialize("NC%s", client->nickname));
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
	if (action == 'M' && type == 'P')
		return (mp_action(server, client, finalmessage));
	if (action == 'W' && type == 'B')
		return (autentificate_client(server, client));
	ft_strdel(&message);
	if (finalmessage != NULL)
		ft_strdel(&finalmessage);
	return (0);
}
