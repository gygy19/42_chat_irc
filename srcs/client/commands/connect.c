/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 19:10:17 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/18 19:10:19 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

int		check_connect_cmd(t_socket_client *client, char *cmd)
{
	char	**split;

	if (ft_strncmp(cmd, "/connect", 8) != 0)
		return (0);
	split = ft_split_string(cmd, " ");
	if (array_length(split) != 3)
	{
		printf("/connect <machine> [port]\n");
		client->host = ft_strdup("127.0.0.1");
		client->server = gethostbyname(client->host);
		client->port = 5000;
		if (aks_initialize_connection(client))
		{
			client->events[1].fd = client->sockfd;
			client->events[1].read = received_message;
		}
		else
			client->host = NULL;
		return (0);
	}
	client->host = ft_strdup(split[1]);
	client->server = gethostbyname(client->host);
	client->port = ft_atoi(split[2]);
	if (aks_initialize_connection(client))
	{
		client->events[1].fd = client->sockfd;
		client->events[1].read = received_message;
	}
	else
		client->host = NULL;
	return (1);
}
