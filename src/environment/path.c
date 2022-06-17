/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 21:59:04 by aboehm            #+#    #+#             */
/*   Updated: 2022/04/13 22:03:15 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//takes the path from the g_env_table and adds it to a 2d array in the pathlist
char	**init_pathlist(void)
{
	t_env	path;
	char	**pathlst;

	path = search("PATH");
	if (path.key)
		pathlst = ft_split(path.data, ':');
	else
		pathlst = NULL;
	return (pathlst);
}

void	destroy_pathlist(char **path)
{
	if (path)
	{
		free2d_array((void **) path);
		path = NULL;
	}
}
