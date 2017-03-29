/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 18:29:26 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/28 18:29:28 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

int		open_socket_connection(t_socket_client *client,\
	char *formated_ip, int port)
{
	if (client->host != NULL)
		ft_strdel(&client->host);
	client->host = ft_strdup(formated_ip);
	client->server = gethostbyname(client->host);
	client->port = port;
	if (aks_initialize_connection(client))
	{
		client->events[1].fd = client->sockfd;
		client->events[1].read = received_message;
		return (1);
	}
	if (client->host != NULL)
		ft_strdel(&client->host);
	client->host = NULL;
	client->events[1].fd = 0;
	client->events[1].read = read_keys;
	clean_channels(client);
	return (0);
}
