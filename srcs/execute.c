/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 21:20:46 by ebaudet           #+#    #+#             */
/*   Updated: 2014/05/16 22:12:56 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include "libft.h"

void		execute_ls(int r, char *buf, int cs)
{
	char	*arg;

	send(cs, "commande ls", ft_strlen("commande ls") + 1, MSG_OOB);
	if (r > 4)
	{
		arg = ft_strdup(buf + 4);
		send(cs, ", arg = ", ft_strlen(", arg = ") + 1, MSG_OOB);
		send(cs, arg, ft_strlen(arg) + 1, MSG_OOB);
	}
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
