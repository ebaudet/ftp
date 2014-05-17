/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 20:41:10 by ebaudet           #+#    #+#             */
/*   Updated: 2014/05/17 21:42:30 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

/*
** env.c
*/
char		*eb_getenv(char **env, char *name);
int			eb_editenv(char **env, char *name, char *value);

/*
** execute.c
*/
void		execute_ls(int r, char *buf, int cs);
void		execute_cd(char *buf, int cs);
void		execute_pwd(int cs, char *pwd);
void		execute_get(char *buf, int cs);
void		execute_put(char *buf, int cs);

#endif
