/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 21:20:46 by ebaudet           #+#    #+#             */
/*   Updated: 2014/05/17 21:12:19 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <sys/types.h>
#include <dirent.h>
#include "libft.h"

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
	/*char			*arg;*/
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
	/*send(cs, "commande ls", ft_strlen("commande ls") + 1, MSG_OOB);
	if (r > 4)
	{
		arg = ft_strdup(buf + 4);
		send(cs, ", arg = ", ft_strlen(", arg = ") + 1, MSG_OOB);
		send(cs, arg, ft_strlen(arg) + 1, MSG_OOB);
	}*/
}

void		execute_cd(char *buf, int cs)
{
	char	*arg;

	send(cs, "commande cd, arg = ", ft_strlen("commande cd, arg = ") + 1, MSG_OOB);
	arg = ft_strdup(buf + 3);
	send(cs, arg, ft_strlen(arg) + 1, MSG_OOB);
}

void		execute_pwd(int cs, char *pwd)
{
	/*send(cs, "commande pwd", ft_strlen("commande pwd") + 1, MSG_OOB);*/
	send(cs, pwd, ft_strlen(pwd) + 1, MSG_OOB);
}

void		execute_get(char *buf, int cs)
{
	char	*arg;

	send(cs, "commande get, arg = ", ft_strlen("commande get, arg = ") + 1, MSG_OOB);
	arg = ft_strdup(buf + 4);
	send(cs, arg, ft_strlen(arg) + 1, MSG_OOB);
}

void		execute_put(char *buf, int cs)
{
	char	*arg;

	send(cs, "commande put, arg = ", ft_strlen("commande put, arg = ") + 1, MSG_OOB);
	arg = ft_strdup(buf + 4);
	send(cs, arg, ft_strlen(arg) + 1, MSG_OOB);
}
