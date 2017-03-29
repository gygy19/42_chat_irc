/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 20:14:52 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/28 20:15:42 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

int			who_action(t_socket_client *client, char *message)
{
	size_t	i;
	char	**split;

	if (client->channel == NULL)
		return (1);
	if (!(split = ft_split_string(message, "|")))
		return (0);
	if (array_length(split) < 1)
	{
		free_array(split);
		return (0);
	}
	i = 1;
	while (i < array_length(split))
	{
		ft_printf("%s\n", split[i]);
		i++;
	}
	ft_printf("%d user(s) online on channel (%s)\n",\
		ft_atoi(split[0]), client->channel->name);
	free_array(split);
	return (0);
}
