/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:51:24 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 05:51:26 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

t_client	*next_client(t_client *current)
{
	if (current == NULL)
		return (NULL);
	return (current->right);
}

static void	add_client_to_server(t_socket_server *server, t_client *c)
{
	t_client	*s;

	if (server->clients == NULL)
		server->clients = c;
	else
	{
		s = server->clients;
		while (s->right != NULL)
			s = s->next(s);
		s->right = c;
		c->left = s;
	}
}

t_client	*add_new_client(t_socket_server *server, int fd)
{
	t_client	*c;

	if (!(c = malloc(sizeof(t_client))))
		return (NULL);
	c->fd = fd;
	c->next = next_client;
	c->read = received_message;
	c->send = send_message;
	c->left = NULL;
	c->right = NULL;
	c->message = NULL;
	c->serialize = ft_sprintf;
	c->channel = NULL;
	c->nickname = NULL;
	add_client_to_server(server, c);
	return (c);
}
