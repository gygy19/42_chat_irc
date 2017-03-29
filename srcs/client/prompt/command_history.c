/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:15:44 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 05:15:45 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

void			up_to_next_olded_command(t_socket_client *client)
{
	if (client->current_cmd->left)
		client->current_cmd = client->current_cmd->left;
	client->current_cmd->cursor_pos = ft_strlen(client->current_cmd->cmd);
	reprint_line(client);
}

void			down_to_olded_next_command(t_socket_client *client)
{
	if (client->current_cmd->right)
		client->current_cmd = client->current_cmd->right;
	client->current_cmd->cursor_pos = ft_strlen(client->current_cmd->cmd);
	reprint_line(client);
}

void			use_history_command(t_socket_client *client)
{
	t_cmds	*cmd;
	t_cmds	*current;
	size_t	pos;

	pos = client->current_cmd->cursor_pos;
	cmd = client->current_cmd;
	current = client->current_cmd;
	while (current->right)
		current = current->right;
	ft_strdel(&current->cmd);
	current->cmd = ft_strdup(cmd->cmd);
	client->current_cmd = current;
	client->current_cmd->cursor_pos = pos;
}
