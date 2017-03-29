/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 19:10:17 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/18 19:10:19 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

static int	is_valide_ip(char *ip)
{
	char	**split;
	int		i;

	i = 0;
	if (ip == NULL)
		return (0);
	split = ft_split_string(ip, ".");
	if (array_length(split) != 4)
	{
		free_array(split);
		return (0);
	}
	while (i < 4)
	{
		if (ft_strlen(split[i]) > 3 || ft_atoi(split[i]) > 255\
			|| ft_atoi(split[i]) < 0)
			return (0);
		i++;
	}
	free_array(split);
	return (1);
}

static int	check_array_len(char **split, char *final_cmd)
{
	if (array_length(split) != 3)
	{
		ft_printf("/connect <machine> [port]\n");
		ft_strdel(&final_cmd);
		free_array(split);
		return (0);
	}
	return (1);
}

static int	check_valide_ip(char **split, char *final_cmd)
{
	if (!is_valide_ip(split[1]))
	{
		ft_printf("Error not comform ip\n");
		ft_strdel(&final_cmd);
		free_array(split);
		return (0);
	}
	return (1);
}

int			check_connect_cmd(t_socket_client *client, char *cmd)
{
	char	**split;
	char	*final_cmd;

	if (ft_strncmp(cmd, "/connect", 8) != 0)
		return (0);
	final_cmd = ft_replace(ft_strdup(cmd), ":", " ");
	split = ft_split_string(final_cmd, " ");
	if (!check_array_len(split, final_cmd))
		return (1);
	if (!check_valide_ip(split, final_cmd))
		return (1);
	if (!open_socket_connection(client, split[1], ft_atoi(split[2])))
		ft_printf("Error during connection\n");
	ft_strdel(&final_cmd);
	free_array(split);
	return (1);
}
