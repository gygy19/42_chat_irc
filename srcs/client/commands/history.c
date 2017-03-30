/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 11:26:36 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/30 11:26:37 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

int		check_history_cmd(t_socket_client *client, char *cmd)
{
	t_cmds	*command;
	int		id;

	if (ft_strcmp(cmd, "/history") != 0)
		return (0);
	id = 1;
	command = client->cmds;
	while (command)
	{
		ft_printf("[%d]:%s\n", id, command->cmd);
		id++;
		command = command->right;
	}
	return (1);
}
