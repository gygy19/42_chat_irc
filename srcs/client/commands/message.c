/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 04:16:58 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/23 04:17:00 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

int		check_message_cmd(t_socket_client *client, char *cmd)
{
	if (cmd[0] == '/')
		return (0);
	if (client->host == NULL)
		return (0);
	if (client->channel == NULL)
		return (0);
	client->send(client, client->serialize("CM%s", ft_strdup(cmd)));
	return (1);
}
