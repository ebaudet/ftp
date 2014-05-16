/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 20:41:10 by ebaudet           #+#    #+#             */
/*   Updated: 2014/05/16 22:12:12 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

/*
** serveur.c
*/
char	*eb_getenv(char **env, char *name);


/*
** execute.c
*/
void		execute_ls(int r, char *buf, int cs);
void		execute_cd(char *buf, int cs);
void		execute_pwd(int cs, char *pwd);
void		execute_get(char *buf, int cs);
void		execute_put(char *buf, int cs);

#endif
