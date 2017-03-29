/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc_server.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 19:41:56 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/16 19:41:57 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_SERVER_H
# define IRC_SERVER_H

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <fcntl.h>
# include <libft.h>
# include <printf.h>
# include <mapft.h>
# include <unistd.h>

# define EPROTONOSUPPORT 93
# define EAFNOSUPPORT    97

# define PROT_INTERNET_IPV4 AF_INET
# define PROT_INTERNET_IPV6 AF_INET6

# define BINARY_SOCK_FLUX SOCK_STREAM

# define DEFAULT_PROTOCOL 0

# define DEBUG_MODE 1

# define MAX_CHANNELS 5

typedef struct			s_channel
{
	int					id;
	char				*name;
	struct s_channel	*right;
	struct s_channel	*left;
	struct s_channel	*(*next)();
	void				(*join)();
	void				(*send)();
	void				(*add_message)();
}						t_channel;

typedef struct			s_client
{
	int					fd;
	struct s_client		*right;
	struct s_client		*left;
	struct s_client		*(*next)();
	int					(*read)();
	int					(*send)();
	char				*(*serialize)(const char *, ...);
	char				*message;
	char				*nickname;
	struct s_channel	*channel;
	struct sockaddr_in	in;
}						t_client;

typedef struct			s_socket_server
{
	int					port;
	int					listenfd;
	int					connfd;
	struct sockaddr_in	serv_addr;
	int					(*data_processor)();
	int					(*send_message_to_all)();
	struct s_client		*(*socket_accept)();
	struct s_client		*(*socket_disconnect)();
	struct s_client		*clients;
	struct s_channel	*channels;
}						t_socket_server;

/*
** Prog server
*/
int						data_processor(t_socket_server *server,\
						t_client *client, char *message);

/*
** Socket_server
*/
int						socket_initialize(t_socket_server *server);
t_client				*socket_accept(t_socket_server *server, int fd,\
						struct sockaddr_in *addr);
t_client				*socket_disconnect(t_socket_server *server,\
						t_client *client);
int						socket_handler(t_socket_server *server);
int						send_message_to_all(t_socket_server *server,\
						char *message);
t_socket_server			*singleton_socket_server(int port);

/*
** Client
*/
t_client				*next_client(t_client *current);
t_client				*add_new_client(t_socket_server *server, int fd);
int						send_message(t_client *client, char *message);
int						received_message(t_socket_server *server,\
						t_client *client);

/*
** Messages
*/
int						channel_action(t_socket_server *server,\
						t_client *client, char type, char *message);
int						who_action(t_socket_server *server, t_client *client);
int						mp_action(t_socket_server *server, t_client *client,\
						char *message);
int						nickname_action(t_socket_server *server,\
						t_client *client, char type, char *nick);

/*
** Channels
*/
int						add_client_to_channel(t_channel *channel,\
						t_client *client);
void					load_channels(t_socket_server *server);
t_channel				*next_channel(t_channel *current);
t_channel				*add_channel(t_socket_server *server, int id,\
						char *name);
void					remove_channel(t_socket_server *server, int channelid);
t_channel				*get_channel(t_socket_server *server, char *name);
char					*get_channel_users(t_socket_server *server,\
						t_channel *channel);
/*
** channel sending
*/
void					send_to_channel_users(t_socket_server *server,\
						t_channel *channel, char *data);
void					left_channel(t_socket_server *server,\
						t_channel *channel, t_client *client);
void					add_message(t_socket_server *server,\
						t_channel *channel, t_client *client, char *message);
void					join_channel(t_socket_server *server,\
						t_channel *channel, t_client *client);

#endif
