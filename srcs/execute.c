/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 21:20:46 by ebaudet           #+#    #+#             */
/*   Updated: 2014/05/18 23:14:26 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "serveur.h"

void		send_str(int cs, char *str)
{
	int		i;
	char	c;
	size_t	len;

	i = 0;
	while ((len = ft_strlen(str + i)) > 0)
	{
		if (len > 1024)
		{
			c = str[(i + 1) * 1024];
			str[(i + 1) * 1024] = 0;
		}
		send(cs, str + i, 1024, MSG_OOB);
		str[(i + 1) * 1024] = c;
		i += 1024;
	}
}

void		execute_ls(int r, char *buf, int cs)
{
	DIR				*rep;
	struct dirent	*read;

	(void)r;
	(void)buf;
	rep = opendir(".");
	while ((read = readdir(rep)))
	{
		send(cs, read->d_name, ft_strlen(read->d_name) + 1, MSG_OOB);
		send(cs, "\t", 2, MSG_OOB);
	}
	closedir(rep);
}

void		execute_cd(char *buf, int cs, char **env)
{
	char	**arg;
	char	*pwd;

	arg = ft_strsplit(buf, ' ');
	if (!arg[1])
	{
		chdir(eb_getenv(env, "HOME"));
		send(cs, "SUCCESS", 8, MSG_OOB);
		return ;
	}
	if (chdir(arg[1]) != 0)
	{
		send(cs, "ERROR path", 11, MSG_OOB);
		return ;
	}
	pwd = getcwd(buf, 1024);
	if (ft_strncmp(pwd, eb_getenv(env, "HOME"),
		ft_strlen(eb_getenv(env, "HOME"))) == 0)
	{
		send(cs, "SUCCESS", 8, MSG_OOB);
		eb_editenv(env, "PWD", pwd);
		return ;
	}
	chdir(eb_getenv(env, "PWD"));
	send(cs, "ERROR bad access", 17, MSG_OOB);
}

void		execute_pwd(int cs, char *pwd)
{
	send(cs, pwd, ft_strlen(pwd) + 1, MSG_OOB);
}

void		execute_get(char **args, int cs, char **env)
{
	int		fd;
	char	buf[1];
	int		r;

	(void)env;
	if (!args[1])
	{
		send(cs, "ERROR no file", 14, MSG_OOB);
		return ;
	}
	if ((fd = open(args[1], O_RDONLY)) == -1)
	{
		send(cs, "ERROR opening file", 19, MSG_OOB);
		return ;
	}
	send(cs, "FILE_OK", 16, MSG_OOB);
	if ((r = read(cs, buf, 1023)) <= 0 || !ft_strncmp(buf, "ERROR", 5))
	{
		close(fd);
		return ;
	}
	while (read(fd, buf, 1) > 0)
		send(cs, buf, 2, MSG_OOB);
	close(fd);
}

void		execute_put(char **args, int cs, char **env)
{
	(void)env;
	send(cs, "commande put, arg = ", ft_strlen("commande put, arg = ") + 1,
		MSG_OOB);
	send(cs, args[1], ft_strlen(args[1]) + 1, MSG_OOB);
}
