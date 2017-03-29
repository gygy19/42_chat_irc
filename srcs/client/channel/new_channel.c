/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_channel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:10:48 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 05:10:49 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

static t_channel	*generate_new_channel(t_socket_client *client, char **split)
{
	t_channel	*channel;
	t_channel	*tmp;

	if (!(channel = malloc(sizeof(t_channel))))
		return (NULL);
	channel->id = ft_atoi(split[0]);
	channel->name = ft_strdup(split[1]);
	channel->users = NULL;
	channel->next = next_channel;
	channel->right = NULL;
	channel->left = NULL;
	if (client->channels == NULL)
		client->channels = channel;
	else
	{
		tmp = client->channels;
		while (tmp->right != NULL)
			tmp = tmp->next(tmp);
		tmp->right = channel;
		channel->left = tmp;
	}
	return (channel);
}

t_channel			*new_channel(t_socket_client *client, char *infos)
{
	t_channel	*channel;
	char		**split;

	if (!(split = ft_split_string(infos, "|")))
		return (NULL);
	if (array_length(split) != 2)
	{
		free_array(split);
		return (NULL);
	}
	if ((channel = exists_channel(client, split[1])) != NULL)
	{
		free_array(split);
		return (channel);
	}
	channel = generate_new_channel(client, split);
	free_array(split);
	return (channel);
}
