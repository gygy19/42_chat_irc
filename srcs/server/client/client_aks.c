/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_aks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:51:45 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 05:51:47 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"
#include "xor.h"

static void	print_action(char *message, char *s)
{
	char	action;
	char	type;

	action = ' ';
	type = ' ';
	if (ft_strlen(message) > 0 && message[0] != '\0')
		action = message[0];
	if (ft_strlen(message) > 1 && message[1] != '\0')
		type = message[1];
	ft_printf("{blue}%s%s: Action[%c] Type[%c]{reset}\n",\
		s, " Message             ", action, type);
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
		ft_printf("Send message to %s %s:%d\n",\
		client->nickname, inet_ntoa(client->in.sin_addr),\
		ntohs(client->in.sin_port));
		ft_printf("{yellow}Send crypted message     : %s{reset}\n", print);
		print_action(message, "Send");
		r = send(client->fd, crypted, ft_strlen(crypted), 0);
	}
	ft_strdel(&message);
	ft_strdel(&print);
	ft_strdel(&crypted);
	return (!(r < 0));
}

static int	read_new_message(t_client *client)
{
	size_t	ret;
	char	buffer[1 + 1];

	ret = recv(client->fd, buffer, 1, 0);
	buffer[ret] = '\0';
	if (client->message == NULL)
		client->message = ft_strdup(buffer);
	else
		client->message = ft_dstrjoin(client->message, buffer, 1);
	return (buffer[0] != '\0');
}

int			received_message(t_socket_server *server, t_client *client)
{
	char	*uncrypted;
	char	*print;

	if (!read_new_message(client))
		return (0);
	uncrypted = uncrypt_xor_to_string(client->message);
	if (uncrypted[ft_strlen(uncrypted) - 1] != '\n')
		return (1);
	uncrypted[ft_strlen(uncrypted) - 1] = '\0';
	print = print_crypted(client->message);
	if (ft_strlen(uncrypted) < 400)
	{
		ft_printf("{yellow}New message of %s from [%s:%d] {reset}\n",\
			client->nickname, inet_ntoa(client->in.sin_addr),\
			ntohs(client->in.sin_port));
		ft_printf("{yellow}Received crypted message : %s{reset}\n", print);
		print_action(uncrypted, "Received");
		server->data_processor(server, client, uncrypted);
	}
	ft_strdel(&print);
	ft_strdel(&uncrypted);
	ft_strdel(&client->message);
	client->message = NULL;
	return (1);
}
