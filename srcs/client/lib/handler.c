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
#include "xor.h"

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

int		send_message(t_socket_client *client, char *message)
{
	int		r;
	char	*crypted;
	char	*print;

	if (message == NULL || ft_strlen(message) <= 0)
		return (0);
	message = ft_dstrjoin_char(message, '\n', 1);
	crypted = crypt_string_to_xor(message);
	print = print_crypted(crypted);
	message[ft_strlen(message) - 1] = '\0';
	//ft_printf("{yellow}Send Message Crypted     : %s{reset}\n", print);
	//ft_printf("{blue}Send Message             : Action[%c] Type[%c]{reset}\n", message[0], message[1]);
	r = send(client->sockfd, crypted, ft_strlen(crypted), 0);
	ft_strdel(&message);
	ft_strdel(&print);
	ft_strdel(&crypted);
	return (!(r < 0));
}

void	received_message(t_socket_client *client)
{
	size_t	ret;
	char	*uncrypted;
	char	*print;
	char	buffer[1 + 1];

	ret = recv(client->sockfd, buffer, 1, 0);
	buffer[ret] = '\0';
	if (client->message == NULL)
		client->message = ft_strdup(buffer);
	else
		client->message = ft_dstrjoin(client->message, buffer, 1);
	if (ft_strlen(client->message) == 0)
	{
		client->host = NULL;
		client->events[1].fd = 0;
		client->events[1].read = read_keys;
		reprint_line(client);
		return ;
	}
	uncrypted = uncrypt_xor_to_string(client->message);
	if (uncrypted[ft_strlen(uncrypted) - 1] != '\n')
		return ;
	uncrypted[ft_strlen(uncrypted) - 1] = '\0';
	print = print_crypted(client->message);
	ft_putstr("\033[u\033[K\033[1A\033[K");
	//ft_printf("{yellow}Received Message Crypted : %s{reset}\n", print);
	//ft_printf("{blue}Received Message         : Action[%c] Type[%c]{reset}\n", uncrypted[0], uncrypted[1]);
	data_processor(client, uncrypted);
	ft_strdel(&print);
	ft_strdel(&uncrypted);
	ft_strdel(&client->message);
	client->message = NULL;
	ft_strdel(&client->message);
}
