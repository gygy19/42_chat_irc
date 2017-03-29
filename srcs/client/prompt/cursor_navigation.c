/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_navigation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:15:24 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 05:15:26 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

void			move_cursor_to_keycode_dir(t_socket_client *client,\
	int key, char *keys)
{
	if (key == 183 && ft_strlen(keys) == 3)
		up_to_next_olded_command(client);
	if (key == 184 && ft_strlen(keys) == 3)
		down_to_olded_next_command(client);
	if (key == 185 && ft_strlen(keys) == 3)
		ft_putstr("\033[1Cright");
	if (key == 186 && ft_strlen(keys) == 3)
		ft_putstr("\033[1Dleft");
}

void			escape_line(t_socket_client *client)
{
	size_t	cmd_len;
	int		lines;

	cmd_len = 0;
	cmd_len += ft_strlen(client->current_cmd->cmd);
	if (client->host)
		cmd_len += ft_strlen(client->host);
	if (client->nickname)
		cmd_len += ft_strlen(client->nickname);
	if (client->host != NULL && client->nickname != NULL)
		cmd_len += 22;
	else
		cmd_len += 8;
	if (get_size_x() < cmd_len)
	{
		lines = cmd_len / get_size_x();
		while (lines-- > 0)
			ft_printf("\033[1A\033[K");
	}
}

void			del_one_entry(t_socket_client *client)
{
	char *tmp;

	if (ft_strlen(client->current_cmd->cmd) == 0)
		return ;
	if (ft_strlen(client->current_cmd->cmd) == 1)
	{
		ft_strdel(&client->current_cmd->cmd);
		client->current_cmd->cmd = ft_strnew(0);
		ft_printf("\033[1D\033[K");
		return ;
	}
	tmp = ft_strndup(client->current_cmd->cmd,\
		ft_strlen(client->current_cmd->cmd) - 1);
	ft_strdel(&client->current_cmd->cmd);
	client->current_cmd->cmd = tmp;
	ft_printf("\033[1D\033[K");
}
