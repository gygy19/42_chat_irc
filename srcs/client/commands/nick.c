/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 08:37:53 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 08:37:54 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

int		check_nick_cmd(t_socket_client *client, char *cmd)
{
	char	**split;

	if (ft_strncmp(cmd, "/nick", 5) != 0)
		return (0);
	if (!(split = ft_split_string(cmd, " ")))
		return (0);
	if (array_length(split) != 2 || client->host == NULL)
	{
		ft_printf("/nick [nickname]\n");
		free_array(split);
		return (0);
	}
	send_message(client, "NC", ft_strdup(split[1]));
	free_array(split);
	return (1);
}
