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

static void		move_cursor_right(t_socket_client *client)
{
	if (client->current_cmd->cursor_pos ==\
		ft_strlen(client->current_cmd->cmd))
		return ;
	client->current_cmd->cursor_pos++;
	ft_putstr("\033[1C");
}

static void		move_cursor_left(t_socket_client *client)
{
	if (client->current_cmd->cursor_pos == 0)
		return ;
	client->current_cmd->cursor_pos--;
	ft_putstr("\033[1D");
}

void			move_cursor_to_keycode_dir(t_socket_client *client,\
	int key, char *keys)
{
	if (key == 183 && ft_strlen(keys) == 3 && client->current_cmd->left)
		up_to_next_olded_command(client);
	if (key == 184 && ft_strlen(keys) == 3 && client->current_cmd->right)
		down_to_olded_next_command(client);
	if (key == 185 && ft_strlen(keys) == 3)
		move_cursor_right(client);
	if (key == 186 && ft_strlen(keys) == 3)
		move_cursor_left(client);
	if (key == 12 && ft_strlen(keys) == 1)
	{
		ft_printf("\033[2J\033[%d;0f\033[s", get_size_y());
		reprint_line(client);
	}
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

static void		del_c(t_socket_client *client)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (client->current_cmd->cmd != NULL &&\
		client->current_cmd->cursor_pos != 0)
		tmp = ft_strndup(client->current_cmd->cmd,\
			client->current_cmd->cursor_pos);
	if (client->current_cmd->cmd != NULL &&\
		ft_strlen(client->current_cmd->cmd) > client->current_cmd->cursor_pos)
		tmp2 = ft_strdup(client->current_cmd->cmd +\
			client->current_cmd->cursor_pos);
	if (tmp == NULL || ft_strlen(tmp) == 1)
		tmp = ft_strnew(0);
	else
	{
		tmp = ft_strndup(tmp, ft_strlen(tmp) - 1);
	}
	if (tmp2 == NULL)
		tmp2 = ft_strnew(0);
	client->current_cmd->cmd = ft_sprintf("%s%s", tmp, tmp2);
	print_current_command(client, 0);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
}

void			del_one_entry(t_socket_client *client)
{
	if (ft_strlen(client->current_cmd->cmd) == 0)
		return ;
	client->current_cmd->cursor_pos--;
	ft_printf("\033[1D\033[K");
	del_c(client);
}
