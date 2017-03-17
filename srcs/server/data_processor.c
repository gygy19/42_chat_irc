/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_processor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 07:58:22 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 07:58:24 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

void		nickname_action(t_socket_server *server, t_client *client, char type, char *nick)
{
	(void)server;
	if (nick == NULL)
		return ;
	if (type == 'C')
	{
		if (ft_strlen(nick) > 9 || ft_strlen(nick) < 2)
			client->send(client, ft_dstrjoin("NL", nick, 2));
		else
			client->send(client, ft_dstrjoin("NC", nick, 2));
	}
}

void		data_processor(t_socket_server *server, t_client *client, char *message)
{
	char	action;
	char	type;

	action = '\0';
	type = '\0';
	printf("Reveived Message :%s\n", message);
	if (ft_strlen(message) > 0)
		action = message[0];
	if (ft_strlen(message) > 1)
		type = message[1];
	if (action == 'N')
		nickname_action(server, client, type, ft_strsub(message, 2, ft_strlen(message)));
}
