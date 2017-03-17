/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 07:53:45 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 07:53:46 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

static int	socket_connection_is_estabilised(int fd)
{
	if (fd == EAFNOSUPPORT)
	{
		printf("Erreur : L'implémentation ne supporte pas la ");
		printf("famille d'adresses indiquée.\n");
		return (0);
	}
	if (fd == EPROTONOSUPPORT)
	{
		printf("Erreur : Le type de protocole, ou le protocole lui-même ");
		printf("n'est pas disponible dans ce domaine de communication.\n");
		return (0);
	}
	if (fd == 2)
	{
		printf("Erreur : Socket error stderr\n");
		return (0);
	}
	return (1);
}

static int	bind_error(void)
{
	printf("Error : Socket addresse is occuped\n");
	return (0);
}

int			send_message_to_all(t_socket_server *server, char *message)
{
	t_client *client;

	client = server->clients;
	while (client != NULL)
	{
		client->send(message);
		client = client->next(client);
	}
	return (1);
}

int			socket_initialize(t_socket_server *server)
{
	char		sendbuff[1024 + 1];
	socklen_t	sa_len;

	server->listenfd = socket(PROT_INTERNET_IPV4,\
		BINARY_SOCK_FLUX, DEFAULT_PROTOCOL);
	if (!socket_connection_is_estabilised(server->listenfd))
		return (0);
	ft_memset(&server->serv_addr, '0', sizeof(struct sockaddr_in));
	ft_memset(sendbuff, '0', sizeof(sendbuff));
	server->serv_addr.sin_family = PROT_INTERNET_IPV4;
	server->serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);//INADDR_ANY == 0.0.0.0
	server->serv_addr.sin_port = htons(server->port);
	if (bind(server->listenfd, (struct sockaddr*)&server->serv_addr,\
		sizeof(server->serv_addr)) < 0)
		return (bind_error());
	listen(server->listenfd, 10);
	sa_len = sizeof(server->serv_addr);
	getsockname(0, (struct sockaddr*)&server->serv_addr, &sa_len);
	printf("Waiting connection --- %s:%d\n",\
		inet_ntoa(server->serv_addr.sin_addr), server->port);
	return (socket_handler(server));
}
