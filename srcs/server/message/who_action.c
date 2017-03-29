/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 00:37:41 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 00:37:42 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

int			who_action(t_socket_server *server, t_client *client)
{
	int			nbr;
	char		*message;
	t_client	*c;

	message = NULL;
	nbr = 0;
	if (client->channel == NULL)
		return (1);
	c = server->clients;
	while (c)
	{
		if (c->channel == client->channel)
		{
			message = ft_dstrjoin(message, ft_sprintf("%s%s",\
				"|", client->nickname), 3);
			nbr++;
		}
		c = c->next(c);
	}
	message = ft_dstrjoin(ft_sprintf("%d", nbr), message, 3);
	client->send(client, client->serialize("CW%s", message));
	ft_strdel(&message);
	return (0);
}
