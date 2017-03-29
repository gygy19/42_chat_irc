/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 20:04:26 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/15 20:04:28 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

t_socket_client	*load_struct_socket_client(void)
{
	t_socket_client	*client;

	if (!(client = malloc(sizeof(t_socket_client))))
		return (NULL);
	client->server = NULL;
	client->host = NULL;
	client->port = 0;
	client->nickname = NULL;
	client->channel = NULL;
	client->channels = NULL;
	client->send = send_message;
	client->message = NULL;
	client->cmds = NULL;
	client->serialize = ft_sprintf;
	client->current_cmd = new_command(client);
	return (client);
}

int				main(int argc, char **argv)
{
	t_socket_client *client;

	(void)argc;
	(void)argv;
	client = load_struct_socket_client();
	client->events[0].fd = 0;
	client->events[0].read = read_keys;
	client->events[1].fd = 0;
	client->events[1].read = read_keys;
	load_termios_console();
	print_prompt(client);
	client_handler(client);
	return (0);
}
