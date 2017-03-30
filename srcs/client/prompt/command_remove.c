/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:01:25 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/30 15:01:30 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

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
		tmp = ft_strndup(tmp, ft_strlen(tmp) - 1);
	if (tmp2 == NULL)
		tmp2 = ft_strnew(0);
	client->current_cmd->cmd = ft_sprintf("%s%s", tmp, tmp2);
	client->current_cmd->cursor_pos--;
	print_current_command(client, 0);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
}

void			del_one_entry(t_socket_client *client)
{
	if (ft_strlen(client->current_cmd->cmd) == 0)
		return ;
	if (client->current_cmd->cursor_pos == 0)
		return ;
	ft_printf("\033[1D\033[K");
	del_c(client);
}
