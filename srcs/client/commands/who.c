/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 19:09:48 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/18 19:09:50 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

int		check_who_cmd(t_socket_client *client, char *cmd)
{
	char	**split;

	if (ft_strncmp(cmd, "/who", 6) != 0)
		return (0);
	split = ft_split_string(cmd, " ");
	if (array_length(split) != 1)
		return (0);
	(void)client;
	return (1);
}
