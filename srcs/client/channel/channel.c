/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:10:23 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 05:10:27 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

t_channel			*next_channel(t_channel *current)
{
	if (current == NULL)
		return (NULL);
	return (current->right);
}

t_channel			*exists_channel(t_socket_client *client, char *name)
{
	t_channel	*tmp;

	tmp = client->channels;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp);
		tmp = tmp->next(tmp);
	}
	return (NULL);
}

void				clean_channels(t_socket_client *client)
{
	t_channel	*channel;
	t_channel	*tmp;

	channel = client->channels;
	while (channel)
	{
		tmp = channel->next(channel);
		ft_strdel(&channel->name);
		free(channel);
		channel = tmp;
	}
	client->channels = NULL;
}

void				remove_channel(t_socket_client *client, int channelid)
{
	if (client->channel != NULL && client->channel->id == channelid)
		client->channel = NULL;
}
