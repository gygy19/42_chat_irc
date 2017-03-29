/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 20:15:31 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/28 20:15:32 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

static void	error_nickname_length(t_socket_client *client, char *nick)
{
	(void)client;
	ft_printf("Votre pseudonyme %s doit avoir une longueur ", nick);
	ft_printf("comprise entre 2 et 10 characters\n");
}

static void	change_nickname_action(t_socket_client *client, char *nick)
{
	if (client->nickname != NULL)
		ft_strdel(&client->nickname);
	client->nickname = ft_strdup(nick);
}

void		nickname_action(t_socket_client *client, char type, char *nick)
{
	if (nick == NULL)
		return ;
	if (type == 'C')
		change_nickname_action(client, nick);
	else if (type == 'L')
		error_nickname_length(client, nick);
}
