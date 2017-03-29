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
	char	**split;
	char	*m;
	char	*nickname;

	(void)client;
	split = ft_split_string(message, "|");
	if (array_length(split) < 1\
		|| (ft_strlen(message) == ft_strlen(split[0]) + 1))
	{
		free_array(split);
		return ;
	}
	nickname = split[0];
	m = ft_strdup(message + ft_strlen(nickname) + 1);
	m = ft_replace(m, ":)", ":D");
	m = ft_replace(m, ":vrai", "\u2713");
	m = ft_replace(m, ":faux", "\u2717");
	m = ft_replace(m, ":star", "\u272D");
	ft_printf("%s: %s{reset}\n", nickname, m);
	free_array(split);
	ft_strdel(&m);
}

static void	change_nickname(t_socket_client *client, char *message)
{
	char **split;

	(void)client;
	split = ft_split_string(message, "|");
	ft_printf("%s change nickname to %s\n", split[0], split[1]);
	free_array(split);
}

static void	leave_channel(t_socket_client *client, char *message)
{
	if (client->channel == NULL)
		return ;
	if (ft_strcmp(message, client->nickname) == 0)
		client->channel = NULL;
	ft_printf("%s has left the channel\n", message);
}

void		channel_action(t_socket_client *client, char type, char *message)
{
	if (message == NULL)
		return ;
	if (type == 'A')
		new_channel(client, message);
	else if (type == 'L')
		leave_channel(client, message);
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
	else if (type == 'W')
		who_action(client, message);
}
