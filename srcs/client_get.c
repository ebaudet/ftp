/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/18 23:22:44 by ebaudet           #+#    #+#             */
/*   Updated: 2014/05/18 23:32:45 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include "libft.h"
#include "client.h"
#include "header.h"

int		action_get_cut(char **args, int sock, char *buf, int r)
{
	int				fd;

	if ((fd = open(args[1], O_RDWR | O_CREAT | O_APPEND | O_EXCL,
		S_IRUSR | S_IWUSR)) == -1)
	{
		write(sock, "ERROR", 2);
		ft_putendl("ERROR File already existing");
		return (-1);
	}
	write(sock, "OK", 2);
	while ((r = recv(sock, buf, sizeof(buf), 0)) > 0)
	{
		buf[r] = '\0';
		write(fd, buf, r);
		if (ft_strcmp(buf, END) == 0 || (ft_strcmp(buf, "") == 0))
			break ;
	}
	close(fd);
	ft_putendl("SUCCESS reception");
	return (0);
}

int		action_get(int sock, char **args)
{
	char			buf[1024];
	int				r;

	if ((r = recv(sock, buf, sizeof(buf), 0)) > 0)
	{
		if (!ft_strncmp(buf, "FILE_OK", 7))
		{
			return (action_get_cut(args, sock, buf, r));
		}
		write(1, buf, r);
		write(1, "\n", 1);
	}
	return (-2);
}
