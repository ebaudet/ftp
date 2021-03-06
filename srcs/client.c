/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 13:23:09 by ebaudet           #+#    #+#             */
/*   Updated: 2014/05/18 23:31:50 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include "libft.h"
#include "header.h"
#include "client.h"

void	usage(char *str)
{
	ft_putstr("Usage: ");
	ft_putstr(str);
	ft_putstr(" <addr> <port>\n");
	exit(-1);
}

int		create_client(char *addr, int port)
{
	int						sock;
	struct protoent			*proto;
	struct sockaddr_in		sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putstr("Connect error");
		exit(2);
	}
	return (sock);
}

int		client_loop(int sock)
{
	int				s;
	char			buf[1024];
	int				r;
	char			**args;

	ft_putstr("[client]-> ");
	s = read(0, buf, 1023);
	buf[s - 1] = '\0';
	args = ft_strsplit(buf, ' ');
	if (!ft_strcmp(args[0], "quit"))
		return (1);
	write(sock, buf, s);
	if (!ft_strcmp(args[0], "get"))
		return (action_get(sock, args));
	while ((r = recv(sock, buf, sizeof(buf), 0)) > 0)
	{
		buf[r] = '\0';
		if (ft_strcmp(buf, END) == 0 || (ft_strcmp(buf, "") == 0))
			break ;
		write(1, buf, r);
	}
	write(1, "\n", 1);
	return (0);
}

int		main(int ac, char **av)
{
	int			port;
	int			sock;

	if (ac != 3)
		usage(av[0]);
	port = ft_atoi(av[2]);
	sock = create_client(av[1], port);
	while (42)
	{
		if (client_loop(sock) == 1)
			break ;
	}
	close(sock);
	return (0);
}
