/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_switcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:18:00 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 05:18:01 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

void			switch_command(t_socket_client *client, char *cmd)
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
	if (check_help_cmd(client, cmd))
		return ;
	if (check_history_cmd(client, cmd))
		return ;
	if (check_send_cmd(client, cmd))
		return ;
	if (check_disconnect_cmd(client, cmd))
		return ;
	if (check_message_cmd(client, cmd))
		return ;
}
