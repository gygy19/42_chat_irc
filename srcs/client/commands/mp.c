/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 19:10:06 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/18 19:10:08 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

static int	check_len_mp_cmd(char **split)
{
	if (array_length(split) == 1)
	{
		ft_printf("Nickname not specified\n");
		free_array(split);
		return (0);
	}
	return (1);
}

static int	check_you_private_message(t_socket_client *client, char **split)
{
	if (ft_strcmp(split[1], client->nickname) == 0)
	{
		ft_printf("You can not send you private messages\n");
		free_array(split);
		return (0);
	}
	return (1);
}

int			check_mp_cmd(t_socket_client *client, char *cmd)
{
	char	**split;
	char	*message;

	if (ft_strncmp(cmd, "/msg", 4) != 0 && ft_strncmp(cmd, "/w", 2) != 0)
		return (0);
	split = ft_split_string(cmd, " ");
	if (!check_len_mp_cmd(split))
		return (1);
	if (!check_you_private_message(client, split))
		return (1);
	if (ft_strlen(cmd) == (ft_strlen(split[0]) + ft_strlen(split[1]) + 2))
	{
		free_array(split);
		return (1);
	}
	message = ft_strdup(cmd + (ft_strlen(split[0]) + ft_strlen(split[1]) + 2));
	if (message == NULL)
		return (1);
	client->send(client, client->serialize("MP%s|%s", split[1], message));
	free_array(split);
	ft_strdel(&message);
	return (1);
}
