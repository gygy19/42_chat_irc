/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 01:20:00 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 01:20:02 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

int		nickname_action(t_socket_server *server, t_client *client,\
	char type, char *nick)
{
	(void)server;
	if (nick == NULL)
		return (1);
	if (type == 'C')
	{
		if (ft_strlen(nick) > 9 || ft_strlen(nick) < 2)
		{
			client->send(client, client->serialize("NL%s", nick));
			return (1);
		}
		client->send(client, client->serialize("NC%s", nick));
		if (client->channel != NULL)
			client->channel->send(server, client->channel,\
				client->serialize("CN%s|%s", client->nickname, nick));
		if (client->nickname != NULL)
			ft_strdel(&client->nickname);
		client->nickname = ft_strdup(nick);
	}
	return (0);
}
