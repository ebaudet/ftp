/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 13:23:03 by ebaudet           #+#    #+#             */
/*   Updated: 2014/05/15 20:32:42 by ebaudet          ###   ########.fr       */
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

void		exectute_commande(int r, char *buf, int cs)
{
	char		*arg;

	if (!ft_strcmp("ls", buf))
		send(cs, "commande ls", ft_strlen("commande ls") + 1, MSG_OOB);
	else if (r > 4 && !ft_strncmp("cd ", buf, 3))
	{
		send(cs, "commande cd, arg = ", ft_strlen("commande cd, arg = ") + 1, MSG_OOB);
		arg = ft_strdup(buf + 3);
		send(cs, arg, ft_strlen(arg), MSG_OOB);
	}
	else if (!ft_strcmp("pwd", buf))
	{
		send(cs, "commande pwd", ft_strlen("commande pwd") + 1, MSG_OOB);
	}
	else if (r > 5 && !ft_strncmp("get ", buf, 4))
	{
		send(cs, "commande get, arg = ", ft_strlen("commande get, arg = ") + 1, MSG_OOB);
		arg = ft_strdup(buf + 4);
		send(cs, arg, ft_strlen(arg), MSG_OOB);
	}
	else if (r > 5 && !ft_strncmp("put ", buf, 4))
	{
		send(cs, "commande put, arg = ", ft_strlen("commande put, arg = ") + 1, MSG_OOB);
		arg = ft_strdup(buf + 4);
		send(cs, arg, ft_strlen(arg), MSG_OOB);
	}
	else
	{
		send(cs, "bad command", 12, MSG_OOB);
	}
}

int		main(int ac, char **av)
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
				buf[r - 1] = '\0';
				ft_putstr("message reçu [");
				ft_putnbr(cs);
				ft_putstr("] : ");
				ft_putendl(buf);
				exectute_commande(r, buf, cs);
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
