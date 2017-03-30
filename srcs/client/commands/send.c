/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 11:36:15 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/30 11:36:16 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

int		check_send_cmd(t_socket_client *client, char *cmd)
{
	char	**split;

	if (ft_strncmp(cmd, "/send", 5) != 0)
		return (0);
	if (!(split = ft_split_string(cmd, " ")))
		return (1);
	if (array_length(split) != 2 || client->host == NULL)
	{
		ft_printf("/send <packet>\n");
		free_array(split);
		return (1);
	}
	send_message(client, client->serialize("%s", split[1]));
	free_array(split);
	return (1);
}
