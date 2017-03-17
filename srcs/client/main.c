/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 20:04:26 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/15 20:04:28 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

#include <stdlib.h>
#include <termios.h>

int		load_console(void)
{
	struct termios	*term;

	term = (struct termios *)malloc(sizeof(struct termios));
	if (tcgetattr(0, term) == -1)
		ft_printf("[modif_term] Failed request tcgetattr!\n");
	term->c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(0, TCSADRAIN, term) == -1)
		return (0);
	return (1);
}

void			print_prompt(int start, t_socket_client *client)
{
	if (start == 0)
		ft_printf("\033[u\033[K");
	ft_printf("\033[s");
	if (client->host != NULL)
		ft_printf("[%s:%d] ", client->host, client->port);
	ft_printf("<%s> » ", client->pseudo);
}

void			switch_cmds(t_socket_client *client, char *cmd)
{
	if (ft_strncmp(cmd, "/nick", 5) == 0 &&\
		ft_strlen(cmd) > 6 && ft_strlen(cmd) < 15)
	{
		ft_strdel(&client->pseudo);
		client->pseudo = ft_strdup(cmd + 6);
	}
	if (ft_strncmp(cmd, "/connect", 8) == 0)
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
	else if (client->host != NULL)
	{
		send_message(client, cmd);
	}
}

void			read_keys(t_socket_client *client)
{
	char	buffer[1];
	int		ret;

	buffer[0] = '\0';
	ret = read(client->events[0].fd, buffer, 1);
	if (!ft_isascii(buffer[0]))
		return ;
	if (ret == 1 && buffer[0] != '\n' && buffer[0] != '\0')
	{
		ft_printf("%s", buffer);
		if (client->cmds[0].cmd == NULL)
			client->cmds[0].cmd = ft_strdup(buffer);
		else
			client->cmds[0].cmd = ft_dstrjoin(client->cmds[0].cmd, buffer, 1);
	}	
	else if (ret == 1 && buffer[0] != '\0' && client->cmds[0].cmd != NULL)
	{
		switch_cmds(client, client->cmds[0].cmd);
		print_prompt(0, client);
		ft_strdel(&client->cmds[0].cmd);
		client->cmds[0].cmd = NULL;
	}
}

t_socket_client *load_struct_socket_client(void)
{
	int				i;
	t_socket_client	*client;

	if (!(client = malloc(sizeof(t_socket_client))))
		return (NULL);
	client->server = NULL;
	client->host = NULL;
	client->port = 0;
	client->pseudo = ft_strdup("unknow");
	i = -1;
	while (i++ < 100)
		client->cmds[i].cmd = NULL;
	return (client);
}

int		main(int argc, char **argv)
{
	t_socket_client *client;

	(void)argc;
	(void)argv;
	client = load_struct_socket_client();
	client->events[0].fd = 0;
	client->events[0].read = read_keys;
	client->events[1].fd = 0;
	client->events[1].read = read_keys;
	load_console();
	print_prompt(1, client);
	read_fds(client);
	//aks_initialize_connection(client);
	//send_message(client, "test");
	return (0);
}
