/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc_client.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 19:41:40 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/16 19:41:42 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_CLIENT_H
# define IRC_CLIENT_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <termios.h>
#include <stdio.h>
#include <fcntl.h>
#include <libft.h>
#include <printf.h>
#include <mapft.h>
#include <unistd.h>
#include <netdb.h>

# define EPROTONOSUPPORT 93
# define EAFNOSUPPORT    97

# define PROT_INTERNET_IPV4 AF_INET
# define PROT_INTERNET_IPV6 AF_INET6

# define BINARY_SOCK_FLUX SOCK_STREAM

# define DEFAULT_PROTOCOL 0

# define MODE_DEBUG 1

typedef struct			s_events
{
	int					fd;
	void				(*read)();
}						t_events;

typedef struct			s_cmds
{
	char				*cmd;
	long int			time;
}						t_cmds;

typedef struct			s_socket_client
{
	char				*host;
	int					port;
	int					sockfd;
	char				*pseudo;
	struct sockaddr_in	serv_addr;
	struct hostent		*server;
	struct s_events		events[2];
	struct s_cmds		cmds[99];
	int					(*send)();
}						t_socket_client;

/*
** Socket
*/
int						aks_initialize_connection(t_socket_client *client);
int						send_message(t_socket_client *client, char *suffix, char *message);
void					received_message(t_socket_client *client);
int						client_handler(t_socket_client *client);

/*
** Prog client
*/
int						load_console(void);
void					data_processor(t_socket_client *client, char *message);
void					switch_cmds(t_socket_client *client, char *cmd);
void					read_keys(t_socket_client *client);
void					reprint_line(t_socket_client *client);
void					print_prompt(int start, t_socket_client *client);

/*
** commands
*/
int						check_nick_cmd(t_socket_client *client, char *cmd);

#endif
