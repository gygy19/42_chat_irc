/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_processor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 07:58:22 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 07:58:24 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

void		data_processor(t_socket_server *server, t_client *client, char *message)
{
	(void)server;
	(void)client;
	printf("Reveived Message :%s\n", message);
}
