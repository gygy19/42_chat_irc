/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 07:12:38 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 07:12:39 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

t_client	*next_client(t_client *current)
{
	if (current == NULL)
		return (NULL);
	return (current->right);
}

t_client	*add_new_client(t_socket_server *server, int fd)
{
	t_client	*c;
	t_client	*s;

	if (!(c = malloc(sizeof(t_client))))
		return (NULL);
	c->fd = fd;
	c->next = next_client;
	c->read = received_message;
	c->send = send_message;
	c->left = NULL;
	c->right = NULL;
	if (server->clients == NULL)
		server->clients = c;
	else
	{
		s = server->clients;
		while (s->right != NULL)
			s = s->next(s);
		s->right = c;
		c->left = s;
	}
	return (c);
}

int			send_message(t_client *client, char *message)
{
	int	r;

	r = send(client->fd, message, ft_strlen(message), 0);
	if (DEBUG_MODE)
		printf("Send Message :%s\n", message);
	return (!(r < 0));
}

int			received_message(t_socket_server *server, t_client *client)
{
	int		ret;
	char	*message;
	char	buffer[1024 + 1];

	message = NULL;
	while ((ret = recv(client->fd, buffer, 1024, 0)) > 0)
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
		return (ret);
	server->data_processor(server, client, message);
	ft_strdel(&message);
	return (ret);
}
