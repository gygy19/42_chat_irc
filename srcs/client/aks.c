/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aks.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 00:12:10 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 00:12:12 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"
#include <string.h>

int		socket_connection_is_estabilised(int fd)
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
	return (1);
}

int		aks_initialize_connection(t_socket_client *client)
{
	client->sockfd = socket(PROT_INTERNET_IPV4, BINARY_SOCK_FLUX, DEFAULT_PROTOCOL);
	if (!socket_connection_is_estabilised(client->sockfd))
		return (0);
	ft_memset(&client->serv_addr, '0', sizeof(struct sockaddr_in));
	client->serv_addr.sin_family = PROT_INTERNET_IPV4;
	bcopy((char*)client->server->h_addr, (char*)&client->serv_addr.sin_addr.s_addr, client->server->h_length);
	client->serv_addr.sin_port = htons(client->port);
	if (connect(client->sockfd, (struct sockaddr*)&client->serv_addr, sizeof(client->serv_addr)) < 0)
		return (0);
	printf("Connection OK\n");
	return (client->sockfd > 2);
}

int		read_fds(t_socket_client *client)
{
	fd_set	rdfs;
	int		i;

	while (1)
	{
		i = 0;
		FD_ZERO(&rdfs);
		while (i < 2)
		{
			FD_SET(client->events[i].fd, &rdfs);
			i++;
		}
		if (select(client->events[1].fd + 1, &rdfs, NULL, NULL, NULL) == -1)
			return (0);
		i = 0;
		while (i < 2)
		{
			if (FD_ISSET(client->events[i].fd, &rdfs))
				client->events[i].read(client);
			i++;
		}
	}
}

int		send_message(t_socket_client *client, char *message)
{
	int r;

	if (message == NULL || ft_strlen(message) <= 0)
		return (0);
	ft_printf("\nsend MESSAGE : %s\n", message);
	r = send(client->sockfd, message, ft_strlen(message), 0);
	return (!(r < 0));
}


void	received_message(t_socket_client *client)
{
	int		ret;
	char	*message;
	char 	buffer[1024 + 1];

	message = NULL;
	while ((ret = recv(client->sockfd, buffer, 1024, 0)) > 0)
	{
		buffer[ret] = '\0';
		ft_printf("%s\n", buffer);
		/*if (message == NULL)
			message = ft_strdup(buffer);
		else
			message = ft_dstrjoin(message, buffer, 1);*/
		if (ret < 1024)
			break ;
	}
	//ft_printf("Reveived Message :%s\n", message);
	//ft_strdel(&message);
}
