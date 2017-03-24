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

t_channel	*exists_channel(t_socket_client *client, char *name)
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

t_channel	*new_channel(t_socket_client *client, char *infos)
{
	t_channel	*channel;
	t_channel	*tmp;
	char		**split;

	if (!(split = ft_split_string(infos, "|")))
		return (NULL);
	if (array_length(split) != 2)
		return (NULL);
	if (exists_channel(client, split[1]))
		return (exists_channel(client, split[1]));
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
	if (client->channel != NULL && client->channel->id == channelid)
		client->channel = NULL;
}

void		print_channels(t_socket_client *client)
{
	t_channel	*channel;

	ft_printf("{color189}<Channels_list{reset}");
	channel = client->channels;
	if (channel != NULL)
		ft_printf("{color189}:    {reset}");
	while (channel)
	{
		if (client->channel == channel)
			ft_putstr("\033[47;30;4m");
		ft_printf("%.8s", channel->name);
		if (client->channel == channel)
			ft_putstr("\033[00m");
		if (channel->right != NULL)
			ft_printf("    ");
		channel = channel->next(channel);
	}
	ft_printf("{color189}>{reset}\n");
}
