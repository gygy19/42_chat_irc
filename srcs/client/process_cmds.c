/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 08:15:20 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 08:15:21 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

t_cmds			*new_cmds(t_socket_client *client)
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

void			switch_cmds(t_socket_client *client, char *cmd)
{
	if (check_nick_cmd(client, cmd))
		return ;
	if (check_connect_cmd(client, cmd))
		return ;
	if (check_who_cmd(client, cmd))
		return ;
	if (check_leave_cmd(client, cmd))
		return ;
	if (check_mp_cmd(client, cmd))
		return ;
	if (check_join_cmd(client, cmd))
		return ;
	if (check_message_cmd(client, cmd))
		return ;
}

void			del_entry(t_socket_client *client)
{
	char *tmp;

	if (client->current_cmd->cmd == NULL)
		return ;
	if (ft_strlen(client->current_cmd->cmd) == 1)
	{
		ft_strdel(&client->current_cmd->cmd);
		client->current_cmd->cmd = NULL;
		client->current_cmd->cmd = ft_strnew(0);
		reprint_line(client);
		return ;
	}
	tmp = ft_strndup(client->current_cmd->cmd,\
		ft_strlen(client->current_cmd->cmd) - 1);
	ft_strdel(&client->current_cmd->cmd);
	client->current_cmd->cmd = tmp;
	reprint_line(client);
}

int				read_key_code(int fd, char **keys)
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

void			up_history(t_socket_client *client)
{
	if (client->current_cmd->left)
		client->current_cmd = client->current_cmd->left;
	reprint_line(client);
}

void			down_history(t_socket_client *client)
{
	if (client->current_cmd->right)
		client->current_cmd = client->current_cmd->right;
	reprint_line(client);
}

void			nav_cmd(t_socket_client *client, int key, char *keys)
{
	if (key == 183 && ft_strlen(keys) == 3)
		up_history(client);
	if (key == 184 && ft_strlen(keys) == 3)
		down_history(client);
	if (key == 185 && ft_strlen(keys) == 3)
		ft_putstr("\033[1Cright");
	if (key == 186 && ft_strlen(keys) == 3)
		ft_putstr("\033[1Dleft");
}

void			replace_cmd(t_socket_client *client)
{
	t_cmds *cmd;
	t_cmds *current;

	cmd = client->current_cmd;
	current = client->current_cmd;
	while (current->right)
		current = current->right;
	ft_strdel(&current->cmd);
	current->cmd = ft_strdup(cmd->cmd);
	client->current_cmd = current;
}

void			add_string_cmd(t_socket_client *client, char *keys)
{
	client->current_cmd->cmd = ft_dstrjoin(client->current_cmd->cmd, keys, 1);
}

void			modif_cmd(t_socket_client *client, char *keys, int key)
{
	if (client->current_cmd->right != NULL)
		replace_cmd(client);
	if (key == 127)
	{
		del_entry(client);
		return ;
	}
	ft_putstr(keys);
	add_string_cmd(client, keys);
}

void			read_keys(t_socket_client *client)
{
	int		key;
	char	*keys;

	keys = ft_strnew(0);
	key = read_key_code(client->events[0].fd, &keys);
	if (ft_is_string_printable(keys) || key == 127)
	{
		modif_cmd(client, keys, key);
	}
	else if (key == '\n' && client->cmds[0].cmd != NULL)
	{
		if (client->current_cmd->right != NULL)
			replace_cmd(client);
		ft_putstr("\033[u\033[K\033[1A");
		switch_cmds(client, client->current_cmd->cmd);
		client->current_cmd = new_cmds(client);
		ft_putstr("\n\033[s");
		reprint_line(client);
	}
	else
	{
		nav_cmd(client, key, keys);
	}
}
