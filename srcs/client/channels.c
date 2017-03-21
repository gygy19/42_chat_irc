/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channels.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 03:24:19 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/19 03:24:20 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

t_channel	*next_channel(t_channel *current)
{
	if (current == NULL)
		return (NULL);
	return (current->right);
}

t_channel	*add_channel(t_socket_client *client, char *infos)
{
	t_channel	*channel;
	t_channel	*tmp;
	char		**split;

	if (!(split = ft_split_string(infos, "|")))
		return (NULL);
	if (array_length(split) != 2)
		return (NULL);
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

void		remove_channel(t_socket_client *client, int channelid)
{
	t_channel	*channel;
	t_channel	*left;
	t_channel	*right;

	channel = client->channels;
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
				client->channels = right;
			}
		}
		channel = channel->next(channel);
	}
}

void		print_channels(t_socket_client *client)
{
	t_channel	*channel;

	ft_putstr("Channels -> ");
	channel = client->channels;
	while (channel)
	{
		ft_putstr("\033[47;30m");
		ft_printf("%.8s", channel->name);
		ft_putstr("\033[00m\t");
		channel = channel->next(channel);
	}
	ft_printf("\n");
}
