/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 13:23:03 by ebaudet           #+#    #+#             */
/*   Updated: 2014/05/15 15:34:29 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "libft.h"

void	usage(char *str)
{
	ft_putstr("Usage: ");
	ft_putstr(str);
	ft_putstr(" <port>\n");
	exit(-1);
}

int		create_server(int port)
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
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putstr("Bind error");
		exit(2);
	}
	listen(sock, 42);
	return (sock);
}

int 	main(int ac, char **av)
{
	int						port;
	int						sock;
	int						cs;
	unsigned int			cslen;
	struct sockaddr_in		csin;
	int						r;
	char					buf[1024];

	if (ac != 2)
		usage(av[0]);
	port = ft_atoi(av[1]);
	sock = create_server(port);
	while (42)
	{
		cs = accept(sock, (struct sockaddr *)&csin, &cslen);
		if (fork() == 0)
		{
			ft_putstr("le client ");
			ft_putnbr(cs);
			ft_putendl(" s'est connecté");
			while ((r = read(cs, buf, 1023)) > 0)
			{
				buf[r] = '\0';
				ft_putstr("message reçu [");
				ft_putnbr(cs);
				ft_putstr("] : ");
				ft_putendl(buf);
				send(cs, "message", 8, MSG_OOB);
			}
			ft_putstr("le client ");
			ft_putnbr(cs);
			ft_putendl(" s'est déconnecté");
			close(cs);
			return (0);
		}
	}
	close(cs);
	close(sock);
	return (0);
}
