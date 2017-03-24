/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_processor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 08:15:28 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 08:15:29 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

void		authentificate_message(t_socket_client *client)
{
	client->send(client, client->serialize("WB"));
}

void		nickname_action(t_socket_client *client, char type, char *nick)
{
	if (nick == NULL)
		return ;
	if (type == 'C')
	{
		client->pseudo = nick;
	}
	else if (type == 'L')
	{
		ft_printf("Votre pseudonyme %s doit avoir une longueur ", nick);
		ft_printf("comprise entre 2 et 10 characters\n");
	}
}

void		channel_action(t_socket_client *client, char type, char *message)
{
	if (message == NULL)
		return ;
	if (type == 'A')
	{
		new_channel(client, message);
	}
	else if (type == 'O')
	{
		client->channel = new_channel(client, message);
	}
	else if (type == 'J')
	{
		ft_printf("%s has joined the channel\n", message);
	}
	else if (type == 'E')
	{
		ft_printf("{red}Votre pseudonyme %s doit avoir une longueur", message);
		ft_printf(" maximum de 9 characters{reset}\n");
	}
	else if (type == 'N')
	{
		char **split;

		split = ft_split_string(message, "|");
		ft_printf("%s change nickname to %s\n", split[0], split[1]);
	}
	else if (type == 'M' && client->channel != NULL)
	{
		char **split;

		split = ft_split_string(message, "|");
		split[1] = ft_replace(split[1], ":)", "\u263B");
		split[1] = ft_replace(split[1], ":(", "\u263A");
		split[1] = ft_replace(split[1], ":vrai", "\u2713");
		split[1] = ft_replace(split[1], ":faux", "\u2717");
		split[1] = ft_replace(split[1], ":star", "\u272D");
		ft_printf("%s: %s\n", split[0], split[1]);
	}
}

void		data_processor(t_socket_client *client, char *message)
{
	char	action;
	char	type;

	action = '\0';
	type = '\0';
	if (ft_strlen(message) > 0)
		action = message[0];
	if (ft_strlen(message) > 1)
		type = message[1];
	if (action == 'C')
		channel_action(client, type,\
			ft_strsub(message, 2, ft_strlen(message)));
	else if (action == 'N')
		nickname_action(client, type,\
			ft_strsub(message, 2, ft_strlen(message)));
	else if (action == 'W' && type == 'M')
		authentificate_message(client);
	ft_putstr("\n\033[s");
	reprint_line(client);
}
