/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 08:14:06 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 08:14:07 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

int		client_handler(t_socket_client *client)
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
			return (1);
		i = 0;
		while (i < 2)
		{
			if (FD_ISSET(client->events[i].fd, &rdfs))
				client->events[i].read(client);
			i++;
		}
	}
	return (0);
}


int		send_message(t_socket_client *client, char *suffix, char *message)
{
	int r;
	
	if (message == NULL || ft_strlen(message) <= 0)
		return (0);
	message = ft_dstrjoin(suffix, message, 2);
	ft_printf("send MESSAGE : %s\n", message);
	r = send(client->sockfd, message, ft_strlen(message), 0);
	ft_strdel(&message);
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
		if (message == NULL)
			message = ft_strdup(buffer);
		else
			message = ft_dstrjoin(message, buffer, 1);
		if (ret < 1024)
			break ;
	}
	if (message == NULL)
	{
		client->host = NULL;
		client->events[1].fd = 0;
		client->events[1].read = read_keys;
		reprint_line(client);
		return ;
	}
	data_processor(client, message);
	ft_strdel(&message);
}