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

t_client	*socket_accept(t_socket_server *server, int fd)
{
	t_client *client;

	if (!(client = add_new_client(server, fd)))
		return (NULL);
	printf("New TCP connexion\n");
	client->send(client, "coucou");
	return (client);
}
