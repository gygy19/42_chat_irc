/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 15:38:30 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/21 15:38:32 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
#include "irc_server.h"

void	ctrlc(int i)
{
	t_socket_server *server;

	if (i == SIGINT)
	{
		server = singleton_socket_server(-1);
		if (server->port > 0 && server->listenfd > 2)
		{
			close(server->listenfd);
			printf("\nFermeture du serveur !\n");
			exit(0);
		}
	}
}

void	ctrlz(int i)
{
	t_socket_server *server;

	if (i == SIGTSTP)
	{
		server = singleton_socket_server(-1);
		if (server->port > 0 && server->listenfd > 2)
		{
			close(server->listenfd);
			printf("\nFermeture du serveur !\n");
			exit(0);
		}
	}
}

void	ctrlq(int i)
{
	t_socket_server *server;
	
	if (i == SIGQUIT)
	{
		server = singleton_socket_server(-1);
		if (server->port > 0 && server->listenfd > 2)
		{
			close(server->listenfd);
			printf("\nFermeture du serveur !\n");
			exit(0);
		}
	}
}
