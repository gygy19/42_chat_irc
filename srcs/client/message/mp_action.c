/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 20:15:36 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/28 20:15:38 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

static void	error_to_send_private_message(t_socket_client *client,\
	char *message)
{
	(void)client;
	ft_printf("%s doesn't exist or is not connected\n", message);
}

static void	new_private_message(t_socket_client *client, char *message)
{
	char	*nickname;
	char	*m;
	char	**split;

	(void)client;
	if (!(split = ft_split_string(message, "|")))
		return ;
	if (array_length(split) < 2)
	{
		free_array(split);
		return ;
	}
	nickname = split[0];
	if (ft_strlen(message) == (ft_strlen(nickname) + 1))
	{
		free_array(split);
		return ;
	}
	m = ft_strdup(message + ft_strlen(nickname) + 1);
	ft_printf("{red}Private Message{reset} of %s: \"%s\"\n", nickname, m);
	ft_strdel(&m);
	free_array(split);
}

static void	private_message_sended(t_socket_client *client, char *message)
{
	char	*nickname;
	char	*m;
	char	**split;

	(void)client;
	if (!(split = ft_split_string(message, "|")))
		return ;
	if (array_length(split) < 2)
	{
		free_array(split);
		return ;
	}
	nickname = split[0];
	if (ft_strlen(message) == (ft_strlen(nickname) + 1))
	{
		free_array(split);
		return ;
	}
	m = ft_strdup(message + ft_strlen(nickname) + 1);
	ft_printf("{red}Private Message{reset} to %s: \"%s\"\n", nickname, m);
	ft_strdel(&m);
	free_array(split);
}

void		mp_action(t_socket_client *client, char type, char *message)
{
	if (message == NULL)
		return ;
	if (type == 'E')
		error_to_send_private_message(client, message);
	else if (type == 'P')
		new_private_message(client, message);
	else if (type == 'S')
		private_message_sended(client, message);
}
