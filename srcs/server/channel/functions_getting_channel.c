/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_getting_channel.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:55:12 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 05:55:14 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

t_channel	*get_channel(t_socket_server *server, char *name)
{
	t_channel *channel;

	channel = server->channels;
	while (channel)
	{
		if (ft_strcmp(channel->name, name) == 0)
		{
			return (channel);
		}
		channel = channel->next(channel);
	}
	return (NULL);
}

char		*get_channel_users(t_socket_server *server, t_channel *channel)
{
	t_client	*c;
	char		*users;

	c = server->clients;
	users = NULL;
	while (c)
	{
		if (users != NULL && c->channel != NULL\
			&& c->channel->id == channel->id)
			users = ft_dstrjoin(users, ft_strjoin("|", c->nickname), 3);
		else if (c->channel != NULL && c->channel->id == channel->id)
			users = ft_strdup(c->nickname);
		c = c->next(c);
	}
	if (users == NULL)
		users = ft_strnew(0);
	return (users);
}
