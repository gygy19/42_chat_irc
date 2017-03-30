/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 11:13:20 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/30 11:13:22 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

int		check_help_cmd(t_socket_client *client, char *cmd)
{
	(void)client;
	if (ft_strcmp(cmd, "/help") != 0 && ft_strcmp(cmd, "/commands") != 0)
		return (0);
	ft_printf("Command list :\n");
	ft_printf("/connect <machine> [port]  (join server irc)\n");
	ft_printf("/join <channel>            (join or create a new channel)\n");
	ft_printf("/leave                     (leave current channel)\n");
	ft_printf("/who                       (for watch online channel users)\n");
	ft_printf("/nick <nickname>           (change your nickname)\n");
	ft_printf("/msg <nickname> <message>  (send a private message)\n");
	ft_printf("/disconnect                (disconnect of server)\n");
	ft_printf("/history                   (print history commands)\n");
	ft_printf("/send <packet>             (crypt and send packet to server)\n");
	return (1);
}
