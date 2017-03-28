/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 07:13:38 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 07:13:40 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

static void	set_clients_fds(t_socket_server *server, fd_set *rdfs, int *maxfd)
{
	t_client	*client;

	client = server->clients;
	while (client != NULL)
	{
		FD_SET(client->fd, rdfs);
		if (*maxfd < client->fd)
			*maxfd = client->fd;
		client = client->next(client);
	}
}

static void	check_clients_fds(t_socket_server *server, fd_set *rdfs)
{
	t_client	*client;

	client = server->clients;
	while (client != NULL)
	{
		if (client->fd != 0 && FD_ISSET(client->fd, rdfs))
		{
			if (client->read(server, client) == 0)
			{
				client = server->socket_disconnect(server, client);
				continue ;
			}
		}
		client = client->next(client);
	}
}

static void	set_socket_server_fd(t_socket_server *server,\
	fd_set *rdfs, int *maxfd)
{
	if (*maxfd < server->listenfd)
		*maxfd = server->listenfd;
	FD_SET(server->listenfd, rdfs);
}

static void	check_socket_accept(t_socket_server *server, fd_set *rdfs)
{
	if (FD_ISSET(server->listenfd, rdfs))
		server->socket_accept(server,\
			accept(server->listenfd, (struct sockaddr*)NULL, NULL));
}

int			socket_handler(t_socket_server *server)
{
	fd_set		rdfs;
	int			maxfd;

	maxfd = 0;
	while (1)
	{
		FD_ZERO(&rdfs);
		set_clients_fds(server, &rdfs, &maxfd);
		set_socket_server_fd(server, &rdfs, &maxfd);
		if (maxfd != 0 && select(maxfd + 1, &rdfs, NULL, NULL, NULL) == -1)
			return (0);
		check_clients_fds(server, &rdfs);
		check_socket_accept(server, &rdfs);
	}
}
