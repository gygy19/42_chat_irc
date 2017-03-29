/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:14:39 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 05:14:41 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

t_cmds			*new_command(t_socket_client *client)
{
	t_cmds *new;
	t_cmds *tmp;

	new = malloc(sizeof(t_cmds));
	new->cmd = ft_strnew(0);
	new->right = NULL;
	new->left = NULL;
	if (client->cmds == NULL)
		client->cmds = new;
	else
	{
		tmp = client->cmds;
		while (tmp->right)
			tmp = tmp->right;
		tmp->right = new;
		new->left = tmp;
	}
	return (new);
}

static int		hook_entry_keys_codes(int fd, char **keys)
{
	char	buffer[4 + 1];
	int		ret;
	int		key;
	int		i;

	key = 0;
	i = 0;
	while ((ret = read(fd, buffer, 4)) > 0)
	{
		buffer[ret] = '\0';
		*keys = ft_dstrjoin(*keys, buffer, 1);
		break ;
	}
	while ((*keys)[i])
	{
		key += (*keys)[i];
		i++;
	}
	return (key);
}

static void		add_string_hooked_keys_to_current_command(\
	t_socket_client *client, char *keys)
{
	client->current_cmd->cmd = ft_dstrjoin(client->current_cmd->cmd, keys, 1);
}

static void		valide_entry_key_to_current_command(t_socket_client *client,\
	char *keys, int key)
{
	if (client->current_cmd->right != NULL)
		use_history_command(client);
	if (key == 127)
	{
		del_one_entry(client);
		return ;
	}
	ft_putstr(keys);
	add_string_hooked_keys_to_current_command(client, keys);
}

void			read_keys(t_socket_client *client)
{
	int		key;
	char	*keys;

	keys = ft_strnew(0);
	key = hook_entry_keys_codes(client->events[0].fd, &keys);
	if (ft_is_string_printable(keys) || key == 127)
	{
		valide_entry_key_to_current_command(client, keys, key);
	}
	else if (key == '\n' && client->current_cmd->cmd != NULL)
	{
		if (client->current_cmd->right != NULL)
			use_history_command(client);
		ft_putstr("\033[u\033[K\033[1A\033[K");
		escape_line(client);
		switch_command(client, client->current_cmd->cmd);
		client->current_cmd = new_command(client);
		ft_putstr("\n\033[s");
		reprint_line(client);
	}
	else
	{
		move_cursor_to_keycode_dir(client, key, keys);
	}
	ft_strdel(&keys);
}
