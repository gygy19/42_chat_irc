/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 19:14:40 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/18 19:14:41 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

int		check_leave_cmd(t_socket_client *client, char *cmd)
{
	char	**split;

	if (ft_strncmp(cmd, "/leave", 6) != 0)
		return (0);
	split = ft_split_string(cmd, " ");
	if (array_length(split) != 2)
	{
		ft_printf("Channel doesn't exist\n");
		return (0);
	}
	(void)client;
	return (1);
}
