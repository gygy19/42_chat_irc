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

int		check_mp_cmd(t_socket_client *client, char *cmd)
{
	char	**split;

	if (ft_strncmp(cmd, "/msg", 6) != 0 || ft_strncmp(cmd, "/w", 6) != 0)
		return (0);
	split = ft_split_string(cmd, " ");
	if (array_length(split) == 1)
		return (0);
	(void)client;
	return (1);
}
