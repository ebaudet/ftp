/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 13:23:03 by ebaudet           #+#    #+#             */
/*   Updated: 2014/05/18 22:37:16 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "libft.h"
#include "header.h"
#include "serveur.h"

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

void		execute_commande(int r, char *buf, int cs, char **env)
{
	char	**args;

	args = ft_strsplit(buf, ' ');
	if (!ft_strcmp("ls", args[0]))
		execute_ls(r, buf, cs);
	else if (!ft_strcmp("cd", args[0]))
		execute_cd(buf, cs, env);
	else if (!ft_strcmp("pwd", args[0]))
		execute_pwd(cs, eb_getenv(env, "PWD"));
	else if (!ft_strcmp("get", args[0]))
		execute_get(args, cs, env);
	else if (!ft_strcmp("put", args[0]))
		execute_put(args, cs, env);
	else
		send(cs, "ERROR bad command", 12, MSG_OOB);
	send(cs, END, 2, 0);
}

int		serveur_loop(int sock, char *buf, char **env)
{
	int						cs;
	unsigned int			cslen;
	struct sockaddr_in		csin;
	int						r;

	cs = accept(sock, (struct sockaddr *)&csin, &cslen);
	if (fork() == 0)
	{
		printf("le client %d s'est connecté\n", cs);
		while ((r = read(cs, buf, 1023)) > 0)
		{
			buf[r - 1] = '\0';
			ft_putstr("message reçu [");
			ft_putnbr(cs);
			ft_putstr("] : ");
			ft_putendl(buf);
			execute_commande(r, buf, cs, env);
		}
		printf("le client %d s'est déconnecté\n", cs);
		close(cs);
		return (0);
	}
	return (0);
}

int		main(int ac, char **av, char **env)
{
	int						port;
	int						sock;
	char					buf[1024];

	if (ac != 2)
		usage(av[0]);
	eb_editenv(env, "HOME", getcwd(buf, 1024));
	port = ft_atoi(av[1]);
	sock = create_server(port);
	while (42)
		serveur_loop(sock, buf, env);
	close(sock);
	return (0);
}
