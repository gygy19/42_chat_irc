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

void			switch_cmds(t_socket_client *client, char *cmd)
{
	if (check_nick_cmd(client, cmd))
		;
	else if (ft_strncmp(cmd, "/connect", 8) == 0)
	{
		client->host = ft_strdup("127.0.0.1");
		client->server =  gethostbyname(client->host);
		client->port = 5000;
		if (aks_initialize_connection(client))
		{
			client->events[1].fd = client->sockfd;
			client->events[1].read = received_message;
		}
		else
			client->host = NULL;
	}
}

void			del_entry(t_socket_client *client)
{
	char *tmp;

	if (client->cmds[0].cmd == NULL)
		return ;
	if (ft_strlen(client->cmds[0].cmd) == 1)
	{
		ft_strdel(&client->cmds[0].cmd);
		client->cmds[0].cmd = NULL;
		reprint_line(client);
		return ;
	}
	tmp = ft_strndup(client->cmds[0].cmd, ft_strlen(client->cmds[0].cmd) - 1);
	ft_strdel(&client->cmds[0].cmd);
	client->cmds[0].cmd = tmp;
	reprint_line(client);
}

int				read_key_code(int fd)
{
	char	buffer[5];
	int		ret;
	int		key;
	int		i;

	key = 0;
	i = 0;
	ret = read(fd, buffer, 5);
	buffer[ret] = '\0';
	while (i < ret)
	{
		key += buffer[i];
		i++;
	}
	return (key);
}

void			read_keys(t_socket_client *client)
{
	int key;

	key = read_key_code(client->events[0].fd);
	if (ft_isprint(key) || key == 127)
	{
		if (key == 127)
		{
			del_entry(client);
			return ;
		}
		ft_putchar(key);
		client->cmds[0].cmd = ft_dstrjoin_char(client->cmds[0].cmd, key, 1);
	}	
	else if (key == '\n' && client->cmds[0].cmd != NULL)
	{
		ft_putstr("\033[u\033[K");
		switch_cmds(client, client->cmds[0].cmd);
		print_prompt(0, client);
		ft_strdel(&client->cmds[0].cmd);
		client->cmds[0].cmd = NULL;
	}
	else
	{
		if (key == 183)//up
			;
		if (key == 184)//down
			;
		if (key == 185)//right
			;
		if (key == 186)//left
			;
		//ft_printf("%d\n", key);
	}
}
