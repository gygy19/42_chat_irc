/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_processor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 08:15:28 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 08:15:29 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

void		authentificate_message(t_socket_client *client)
{
	client->send(client, client->serialize("WB"));
}

void		data_processor(t_socket_client *client, char *message)
{
	char	action;
	char	type;
	char	*sub;

	action = '\0';
	type = '\0';
	if (ft_strlen(message) > 0)
		action = message[0];
	if (ft_strlen(message) > 1)
		type = message[1];
	sub = ft_strsub(message, 2, ft_strlen(message));
	if (action == 'C')
		channel_action(client, type, sub);
	else if (action == 'M')
		mp_action(client, type, sub);
	else if (action == 'N')
		nickname_action(client, type, sub);
	else if (action == 'W' && type == 'M')
		authentificate_message(client);
	ft_putstr("\n\033[s");
	reprint_line(client);
	if (sub != NULL)
		ft_strdel(&sub);
}
