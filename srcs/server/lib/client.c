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
#include "xor.h"

t_client	*next_client(t_client *current)
{
	if (current == NULL)
		return (NULL);
	return (current->right);
}

static void	add_client_to_server(t_socket_server *server, t_client *c)
{
	t_client	*s;

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
}

t_client	*add_new_client(t_socket_server *server, int fd)
{
	t_client	*c;

	if (!(c = malloc(sizeof(t_client))))
		return (NULL);
	c->fd = fd;
	c->next = next_client;
	c->read = received_message;
	c->send = send_message;
	c->left = NULL;
	c->right = NULL;
	c->message = NULL;
	c->serialize = ft_sprintf;
	c->channel = NULL;
	c->nickname = NULL;
	add_client_to_server(server, c);
	return (c);
}

int			send_message(t_client *client, char *message)
{
	int		r;
	char	*crypted;
	char	*print;

	message = ft_dstrjoin_char(message, '\n', 1);
	crypted = crypt_string_to_xor(message);
	print = print_crypted(crypted);
	message[ft_strlen(message) - 1] = '\0';
	r = 0;
	if (ft_strlen(message) < 400)
	{
		ft_printf("{yellow}Send Message Crypted     : %s{reset}\n", print);
		ft_printf("{blue}%s: Action[%c] Type[%c]{reset}\n", \
			"Send Message             ", message[0], message[1]);
		r = send(client->fd, crypted, ft_strlen(crypted), 0);
	}
	ft_strdel(&message);
	ft_strdel(&print);
	ft_strdel(&crypted);
	return (!(r < 0));
}

static void	read_new_message(t_client *client)
{
	size_t	ret;
	char	buffer[1 + 1];

	ret = recv(client->fd, buffer, 1, 0);
	buffer[ret] = '\0';
	if (client->message == NULL)
		client->message = ft_strdup(buffer);
	else
		client->message = ft_dstrjoin(client->message, buffer, 1);
}

int			received_message(t_socket_server *server, t_client *client)
{
	char	*uncrypted;
	char	*print;

	read_new_message(client);
	if (client->message == NULL)
		return (0);
	uncrypted = uncrypt_xor_to_string(client->message);
	if (uncrypted[ft_strlen(uncrypted) - 1] != '\n')
		return (0);
	uncrypted[ft_strlen(uncrypted) - 1] = '\0';
	print = print_crypted(client->message);
	if (ft_strlen(uncrypted) < 400)
	{
		ft_printf("{yellow}Received Message Crypted : %s{reset}\n", print);
		ft_printf("{blue}%s: Action[%c] Type[%c]{reset}\n",\
			"Received Message         ", uncrypted[0], uncrypted[1]);
		server->data_processor(server, client, uncrypted);
	}
	ft_strdel(&print);
	ft_strdel(&uncrypted);
	ft_strdel(&client->message);
	client->message = NULL;
	return (1);
}
