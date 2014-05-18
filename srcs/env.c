/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/17 21:37:31 by ebaudet           #+#    #+#             */
/*   Updated: 2014/05/18 23:33:47 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		eb_editenv(char **env, char *name, char *value)
{
	int		i;
	char	loop;
	char	*tmp;

	i = 0;
	loop = 'y';
	while (*(env + i) != NULL && loop == 'y')
	{
		if (ft_strncmp(*(env + i), name, ft_strlen(name)) == 0)
		{
			tmp = ft_strjoin(name, "=");
			env[i] = ft_strjoin(tmp, value);
			free(tmp);
			loop = 'n';
		}
		else
			i++;
	}
	if (loop == 'y')
		return (-1);
	return (0);
}

char	*eb_getenv(char **env, char *name)
{
	int		i;
	char	loop;

	i = 0;
	loop = 'y';
	while (*(env + i) != NULL && loop == 'y')
	{
		if (ft_strncmp(*(env + i), name, ft_strlen(name)) == 0)
			loop = 'n';
		else
			i++;
	}
	if (loop == 'y')
		return (NULL);
	return (*(env + i) + ft_strlen(name) + 1);
}
