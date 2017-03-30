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
	printf("Error : Socket address is busy\n");
	return (0);
}

int			send_message_to_all(t_socket_server *server, char *message)
{
	t_client *client;

	client = server->clients;
	while (client != NULL)
	{
		client->send(client, client->serialize(message));
		client = client->next(client);
	}
	ft_strdel(&message);
	return (1);
}

in_addr_t	string_ip_to_inaddr_t(char *ip)
{
	int			final_ip;
	char		**points;
	int			i;

	final_ip = 0x00000000;
	i = 0;
	points = ft_split_string(ip, ".");
	if (array_length(points) != 4)
		return (final_ip);
	final_ip += ft_atoi(points[0]);
	final_ip = final_ip << 8;
	final_ip += ft_atoi(points[1]);
	final_ip = final_ip << 8;
	final_ip += ft_atoi(points[2]);
	final_ip = final_ip << 8;
	final_ip += ft_atoi(points[3]);
	ft_printf("%s->%08x\n", ip, final_ip);
	return ((in_addr_t)final_ip);
}

int			socket_initialize(t_socket_server *server)
{
	socklen_t	sa_len;

	server->listenfd = socket(PROT_INTERNET_IPV4,\
		BINARY_SOCK_FLUX, DEFAULT_PROTOCOL);
	if (!socket_connection_is_estabilised(server->listenfd))
		return (0);
	ft_memset(&server->serv_addr, '0', sizeof(struct sockaddr_in));
	server->serv_addr.sin_family = PROT_INTERNET_IPV4;
	server->serv_addr.sin_addr.s_addr = INADDR_ANY;
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
