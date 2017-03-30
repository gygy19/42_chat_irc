/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disconnect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:20:02 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/30 15:20:04 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

int		check_disconnect_cmd(t_socket_client *client, char *cmd)
{
	if (ft_strcmp(cmd, "/disconnect") != 0)
		return (0);
	if (client->host == NULL)
		return (1);
	ft_printf("Server disconnection %s:%d\n", client->host, client->port);
	close(client->sockfd);
	ft_strdel(&client->host);
	client->host = NULL;
	client->events[1].fd = 0;
	client->events[1].read = read_keys;
	clean_channels(client);
	return (1);
}
