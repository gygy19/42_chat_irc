/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_session.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 08:13:52 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 08:13:53 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"
#include <string.h>

int		socket_connection_is_estabilised(int fd)
{
	if (fd < 0)
	{
		printf("Erreur : Socket connection has failed.\n");
		return (0);
	}
	return (1);
}

int		connect_connection_is_estabilised(t_socket_client *client, int ret)
{
	if (ret != 0)
	{
		printf("Erreur : Serveur non connecté\n");
		close(client->sockfd);
		return (0);
	}
	return (1);
}

int		aks_initialize_connection(t_socket_client *client)
{
	client->sockfd = socket(PROT_INTERNET_IPV4,\
		BINARY_SOCK_FLUX, DEFAULT_PROTOCOL);
	if (!socket_connection_is_estabilised(client->sockfd))
		return (0);
	ft_memset(&client->serv_addr, '0', sizeof(struct sockaddr_in));
	client->serv_addr.sin_family = PROT_INTERNET_IPV4;
	ft_memcpy((char*)&client->serv_addr.sin_addr.s_addr,\
		(char*)client->server->h_addr, client->server->h_length);
	client->serv_addr.sin_port = htons(client->port);
	if (!connect_connection_is_estabilised(client, connect(client->sockfd,\
		(struct sockaddr*)&client->serv_addr, sizeof(client->serv_addr)) < 0))
		return (0);
	return (1);
}
