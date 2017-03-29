/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 19:09:48 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/18 19:09:50 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

int		check_who_cmd(t_socket_client *client, char *cmd)
{
	if (ft_strcmp(cmd, "/who") != 0)
		return (0);
	if (client->channel == NULL)
	{
		ft_printf("You is not on a channel\n");
		return (0);
	}
	if (client->host == NULL)
	{
		ft_printf("Yo is not not connected on server\n");
		return (0);
	}
	client->send(client, client->serialize("CW"));
	return (1);
}
