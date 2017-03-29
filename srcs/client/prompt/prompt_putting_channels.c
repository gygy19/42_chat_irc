/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_putting_channels.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:40:11 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 05:40:12 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

void			print_current_channel(t_socket_client *client, size_t *len_max)
{
	t_channel	*channel;

	channel = client->channels;
	while (channel)
	{
		if (client->channel != channel)
		{
			channel = channel->next(channel);
			continue ;
		}
		if (*len_max < 4 || *len_max < (ft_strlen(channel->name) + 4))
		{
			ft_printf("...");
			break ;
		}
		ft_printf("\033[47;30;4m%s\033[00m", channel->name);
		if (client->channels->right != NULL)
			ft_printf("    ");
		*len_max -= (4 + ft_strlen(channel->name));
		channel = channel->next(channel);
	}
}

void			print_next_channels(t_socket_client *client, size_t *len_max)
{
	t_channel	*channel;

	channel = client->channels;
	while (channel)
	{
		if (client->channel == channel)
		{
			channel = channel->next(channel);
			continue ;
		}
		if (*len_max < 4 || *len_max < (ft_strlen(channel->name) + 4))
		{
			ft_printf("...");
			break ;
		}
		ft_printf("%s", channel->name);
		if (channel->right != NULL)
			ft_printf("    ");
		*len_max -= (4 + ft_strlen(channel->name));
		channel = channel->next(channel);
	}
}

void			print_channels(t_socket_client *client)
{
	size_t		len_max;

	len_max = get_size_x() - 20;
	ft_printf("{color189}<Channels_list{reset}");
	if (client->channels != NULL)
		ft_printf("{color189}:    {reset}");
	print_current_channel(client, &len_max);
	print_next_channels(client, &len_max);
	ft_printf("{color189}>{reset}\n");
}
