/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 00:37:56 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 00:37:57 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

static void	send_private_message(t_socket_server *server,\
	t_client *client, t_client *dest, char *message)
{
	(void)server;
	dest->send(dest, dest->serialize("MP%s|%s", client->nickname, message));
	client->send(client, client->serialize("MS%s|%s", dest->nickname, message));
	ft_strdel(&message);
}

static void	unknow_nickname(t_socket_server *server, t_client *client,\
	char *nickname, char *message)
{
	(void)server;
	client->send(client, client->serialize("MU%s", nickname));
	ft_strdel(&message);
}

int			mp_action(t_socket_server *server, t_client *client, char *message)
{
	char		**split;
	char		*nickname;
	char		*m;
	t_client	*c;

	if (message == NULL)
		return (0);
	if (!(split = ft_split_string(message, "|")))
		return (0);
	nickname = split[0];
	if (ft_strlen(message) == (ft_strlen(nickname) + 1))
		return (0);
	m = ft_strdup(message + ft_strlen(nickname) + 1);
	c = server->clients;
	while (c)
	{
		if (c->nickname != NULL && ft_strcmp(c->nickname, nickname) == 0)
			break ;
		c = c->next(c);
	}
	if (c == NULL)
		unknow_nickname(server, client, nickname, m);
	else
		send_private_message(server, client, c, m);
	return (0);
}
