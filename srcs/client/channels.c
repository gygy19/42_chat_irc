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

t_channel	*set_channel(t_socket_client *client, char *infos)
{
	t_channel	*channel;
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
	client->channel = channel;
	return (channel);
}

void		remove_channel(t_socket_client *client, int channelid)
{
	if (client->channel != NULL && client->channel->id == channelid)
		client->channel = NULL;
}

void		print_channels(t_socket_client *client)
{
	t_channel	*channel;

	ft_putstr("Channels -> ");
	channel = client->channel;
	if (channel)
	{
		ft_putstr("\033[47;30m");
		ft_printf("%.8s", channel->name);
		ft_putstr("\033[00m\t");
		channel = channel->next(channel);
	}
	ft_printf("\n");
}
