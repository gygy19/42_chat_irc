/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 18:43:26 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/28 18:43:27 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

static void	print_new_message(t_socket_client *client, char *message)
{
	char **split;

	(void)client;
	split = ft_split_string(message, "|");
	split[1] = ft_replace(split[1], ":)", ":D");
	split[1] = ft_replace(split[1], ":vrai", "\u2713");
	split[1] = ft_replace(split[1], ":faux", "\u2717");
	split[1] = ft_replace(split[1], ":star", "\u272D");
	ft_printf("%s: %s\n", split[0], split[1]);
	free_array(split);
}

static void	change_nickname(t_socket_client *client, char *message)
{
	char **split;

	(void)client;
	split = ft_split_string(message, "|");
	ft_printf("%s change nickname to %s\n", split[0], split[1]);
	free_array(split);
}

void		channel_action(t_socket_client *client, char type, char *message)
{
	if (message == NULL)
		return ;
	if (type == 'A')
		new_channel(client, message);
	else if (type == 'O')
		client->channel = new_channel(client, message);
	else if (type == 'J')
		ft_printf("%s has joined the channel\n", message);
	else if (type == 'E')
	{
		ft_printf("{red}Votre pseudonyme %s doit avoir une longueur", message);
		ft_printf(" maximum de 9 characters{reset}\n");
	}
	else if (type == 'N')
		change_nickname(client, message);
	else if (type == 'M' && client->channel != NULL)
		print_new_message(client, message);
}
