/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:54:31 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 05:54:33 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

void		load_channels(t_socket_server *server)
{
	add_channel(server, 1, "Accueil");
}

t_channel	*next_channel(t_channel *current)
{
	if (current == NULL)
		return (NULL);
	return (current->right);
}

t_channel	*add_channel(t_socket_server *server, int id, char *name)
{
	t_channel	*channel;
	t_channel	*tmp;

	if (!(channel = malloc(sizeof(t_channel))))
		return (NULL);
	channel->id = id;
	channel->name = ft_strdup(name);
	channel->next = next_channel;
	channel->right = NULL;
	channel->left = NULL;
	channel->join = join_channel;
	channel->send = send_to_channel_users;
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
