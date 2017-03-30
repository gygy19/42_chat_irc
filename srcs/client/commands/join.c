/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 19:09:37 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/18 19:09:40 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

int		check_join_cmd(t_socket_client *client, char *cmd)
{
	char	**split;

	if (ft_strncmp(cmd, "/join", 5) != 0)
		return (0);
	if (!(split = ft_split_string(cmd, " ")))
		return (1);
	if (array_length(split) != 2 || client->host == NULL)
	{
		ft_printf("Channel doesn't exist\n");
		free_array(split);
		return (1);
	}
	client->send(client, client->serialize("CJ%s", split[1]));
	free_array(split);
	return (1);
}
