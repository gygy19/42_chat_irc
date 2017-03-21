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

int			add_client_to_channel(t_channel *channel, t_client *client)
{
	int i;

	i = 0;
	while (client->channels[i] && i < MAX_CHANNELS)
	{
		if (client->channels[i] == channel->id)
			return (0);
		if (client->channels[i] == 0)
		{
			client->channels[i] = channel->id;
			break ;
		}
		i++;
	}
	return (1);
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
