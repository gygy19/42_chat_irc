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
# define NON_BLOCK_SOCK_FLUX 04000

# define DEFAULT_PROTOCOL 0

# define SOL_TCP 6

# define TCP_KEEPCNT 5
# define TCP_KEEPIDLE 5
# define TCP_KEEPINTVL 1

# define MODE_DEBUG 1

typedef struct			s_events
{
	int					fd;
	void				(*read)();
}						t_events;

typedef struct			s_channel
{
	int					id;
	char				*name;
	int					count_users;
	struct s_channel	*right;
	struct s_channel	*left;
	struct s_channel	*(*next)();
	char				**users;
}						t_channel;

typedef struct			s_cmds
{
	char				*cmd;
	struct s_cmds		*right;
	struct s_cmds		*left;
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
	struct s_cmds		*cmds;
	struct s_cmds		*current_cmd;
	struct s_channel	*channel;
	int					(*send)();
	char				*(*serialize)(const char *, ...);
	char				*message;
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
void					restart_line(void);
void					data_processor(t_socket_client *client, char *message);
void					switch_cmds(t_socket_client *client, char *cmd);
void					read_keys(t_socket_client *client);
void					reprint_line(t_socket_client *client);
void					print_prompt(t_socket_client *client);

/*
** commands
*/
t_cmds					*new_cmds(t_socket_client *client);
int						check_nick_cmd(t_socket_client *client, char *cmd);
int						check_leave_cmd(t_socket_client *client, char *cmd);
int						check_who_cmd(t_socket_client *client, char *cmd);
int						check_mp_cmd(t_socket_client *client, char *cmd);
int						check_connect_cmd(t_socket_client *client, char *cmd);
int						check_join_cmd(t_socket_client *client, char *cmd);
int						check_message_cmd(t_socket_client *client, char *cmd);

/*
** Channels
*/
t_channel				*next_channel(t_channel *current);
t_channel				*set_channel(t_socket_client *client, char *infos);
void					remove_channel(t_socket_client * client, int channelid);
void					print_channels(t_socket_client *client);

#endif
