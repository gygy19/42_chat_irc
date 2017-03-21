/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 20:04:42 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/15 20:04:43 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

t_socket_server	*load_struct_socket_server(int port)
{
	t_socket_server *server;

	if (!(server = malloc(sizeof(t_socket_server))))
		return (NULL);
	server->port = port;
	server->data_processor = data_processor;
	server->socket_accept = socket_accept;
	server->socket_disconnect = socket_disconnect;
	server->send_message_to_all = send_message_to_all;
	server->clients = NULL;
	return (server);
}

int				main(int argc, char **argv)
{
	int				port;
	t_socket_server	*server;

	if (argc != 2)
		return (1);
	port = ft_atoi(argv[1]);
	if (port <= 0)
		return (1);
	if (!(server = load_struct_socket_server(port)))
		return (1);
	load_channels(server);
	return (socket_initialize(server));
}
