/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 19:14:40 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/18 19:14:41 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

int		check_leave_cmd(t_socket_client *client, char *cmd)
{
	if (ft_strcmp(cmd, "/leave") != 0)
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
	client->send(client, client->serialize("CL"));
	return (1);
}
