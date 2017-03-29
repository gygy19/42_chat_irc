/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_accept.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 07:12:11 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 07:12:13 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

t_client	*socket_accept(t_socket_server *server, int fd,\
	struct sockaddr_in *addr)
{
	t_client *client;

	if (!(client = add_new_client(server, fd)))
		return (NULL);
	client->in = *addr;
	ft_printf("New TCP connexion from %s:%d\n",\
		inet_ntoa(client->in.sin_addr), ntohs(client->in.sin_port));
	client->nickname = ft_sprintf("guest%d", client->fd);
	client->send(client, client->serialize("WM"));
	return (client);
}
