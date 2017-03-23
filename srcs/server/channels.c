/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channels.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 05:19:00 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/19 05:19:02 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

void		load_channels(t_socket_server *server)
{
	add_channel(server, 1, "test");
	add_channel(server, 2, "accueil");
}

t_channel	*next_channel(t_channel *current)
{
	if (current == NULL)
		return (NULL);
	return (current->right);
}

char		*get_channel_users(t_socket_server *server, t_channel *channel)
{
	t_client	*c;
	char		*users;

	c = server->clients;
	users = NULL;
	while (c)
	{
		if (users != NULL && c->channel != NULL && c->channel->id == channel->id)
			users = ft_dstrjoin(users, ft_strjoin("|", c->nickname), 3);
		else if (c->channel != NULL && c->channel->id == channel->id)
			users = ft_strdup(c->nickname);
		c = c->next(c);
	}
	if (users == NULL)
		users = ft_strnew(0);
	return (users);
}

void		send_channel_users(t_socket_server *server, t_channel *channel, char *data)
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

void		join_channel(t_socket_server *server, t_channel *channel, t_client *client)
{
	client->channel = channel;
	channel->send(server, channel, client->serialize("CJ%s", client->nickname));
	client->send(client, client->serialize("CA%s|%s", channel->id, channel->name));
}

void		add_message(t_socket_server *server, t_channel *channel, t_client *client, char *message)
{
	channel->send(server, channel, client->serialize("CM%s|%s", client->nickname, message));
}

t_channel	*add_channel(t_socket_server *server, int id, char *name)
{
	t_channel	*channel;
	t_channel	*tmp;

	if (!(channel = malloc(sizeof(t_channel))))
		return (NULL);
	channel->id = id;
	channel->name = name;
	channel->next = next_channel;
	channel->right = NULL;
	channel->left = NULL;
	channel->join = join_channel;
	channel->send = send_channel_users;
	channel->add_message = add_message;
	if (server->channels == NULL)
		server->channels = channel;
	else
	{
		tmp = server->channels;
		while (tmp->right != NULL)
			tmp = tmp->next(tmp);
		tmp->right = channel;
		channel->left = tmp;
	}
	return (channel);
}

void		remove_channel(t_socket_server *server, int channelid)
{
	t_channel	*channel;
	t_channel	*left;
	t_channel	*right;

	channel = server->channels;
	while (channel)
	{
		if (channel->id == channelid)
		{
			right = channel->right;
			left = channel->left;
			if (left && right && (right->left = left))
				left->right = right;
			if (left && !right)
				left->right = NULL;
			if (!left && right)
			{
				right->left = NULL;
				server->channels = right;
			}
		}
		channel = channel->next(channel);
	}
}
